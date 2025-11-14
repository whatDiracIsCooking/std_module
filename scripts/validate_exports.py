#!/usr/bin/env python3
"""
Symbol Coverage Validator using Clang AST Dump

This script validates C++20 module exports by comparing:
1. Clang's AST dump (authoritative - what the compiler sees)
2. Regex extraction (fast method used by symbol_coverage.py)

Usage:
    ./scripts/validate_exports.py                    # Validate all modules
    ./scripts/validate_exports.py src/format.cppm    # Validate one module
    ./scripts/validate_exports.py --list-only        # Just list exports

This provides authoritative validation that our regex-based export extraction
is correct by comparing against what Clang actually sees in the AST.
"""

import argparse
import re
import subprocess
import sys
from pathlib import Path
from typing import List, Set, Tuple, Optional
from dataclasses import dataclass


@dataclass
class ExportInfo:
    """Information about an exported symbol from AST"""
    name: str
    kind: str  # 'FunctionTemplate', 'Function', 'ClassTemplate', etc.
    line: int

    def __str__(self):
        return f"{self.name:30s} ({self.kind})"


class Colors:
    """ANSI color codes"""
    GREEN = '\033[92m'
    RED = '\033[91m'
    YELLOW = '\033[93m'
    BLUE = '\033[94m'
    BOLD = '\033[1m'
    RESET = '\033[0m'

    @staticmethod
    def disable():
        Colors.GREEN = Colors.RED = Colors.YELLOW = ''
        Colors.BLUE = Colors.BOLD = Colors.RESET = ''


def get_clang_ast_dump(module_file: Path, clang_path: str = "clang++") -> Optional[str]:
    """
    Run clang -ast-dump and return the output.

    Returns None if clang fails or times out.
    """
    cmd = [
        clang_path,
        "-std=c++20",
        "-Xclang", "-ast-dump",
        "-fsyntax-only",
        str(module_file)
    ]

    try:
        result = subprocess.run(
            cmd,
            capture_output=True,
            text=True,
            timeout=30
        )

        # Clang may return non-zero for warnings, but still produce AST
        if result.returncode not in [0, 1]:
            print(f"{Colors.RED}Error: clang returned {result.returncode}{Colors.RESET}")
            if result.stderr:
                print(f"Stderr: {result.stderr[:500]}")
            return None

        return result.stdout

    except subprocess.TimeoutExpired:
        print(f"{Colors.RED}Error: clang command timed out{Colors.RESET}")
        return None
    except FileNotFoundError:
        print(f"{Colors.RED}Error: {clang_path} not found{Colors.RESET}")
        return None


def parse_ast_exports(ast_dump: str, module_file: Path) -> List[ExportInfo]:
    """
    Parse Clang AST dump to extract exported symbols.

    Looks for pattern:
        `-ExportDecl ... in std_module.format
          `-NamespaceDecl ... std
            |-UsingDecl ... <line:15:1> ... std::format
            |-UsingShadowDecl ... implicit FunctionTemplate ... 'format'
    """
    exports = []
    lines = ast_dump.split('\n')

    in_export_decl = False
    in_namespace_std = False
    current_using_decl = None

    module_name = module_file.stem

    for i, line in enumerate(lines):
        # Find ExportDecl for our module
        if 'ExportDecl' in line and module_name in line:
            in_export_decl = True
            continue

        # Exit ExportDecl when we hit another top-level node
        if in_export_decl and line.startswith('`-') and 'ExportDecl' not in line:
            in_export_decl = False
            continue

        if not in_export_decl:
            continue

        # Find std namespace (can be 'std' or nested like 'filesystem', 'ranges', etc.)
        if 'NamespaceDecl' in line and (' std' in line or 'filesystem' in line or 'ranges' in line):
            in_namespace_std = True
            continue

        if not in_namespace_std:
            continue

        # Find UsingDecl: |-UsingDecl ... <line:15:1> ... std::format
        # Also handle nested namespaces: std::filesystem::path
        using_match = re.search(r'UsingDecl.*?line:(\d+).*?\s+std::(?:\w+::)?(\w+)\s*$', line)
        if using_match:
            line_num = int(using_match.group(1))
            symbol_name = using_match.group(2)
            current_using_decl = symbol_name
            continue

        # Find UsingShadowDecl to get the symbol kind
        # |-UsingShadowDecl ... implicit FunctionTemplate ... 'format'
        if current_using_decl and 'UsingShadowDecl' in line and 'implicit' in line:
            shadow_match = re.search(r'implicit\s+(\w+)\s+.*?\'(\w+)\'', line)
            if shadow_match:
                kind = shadow_match.group(1)
                symbol_name = shadow_match.group(2)

                if symbol_name == current_using_decl:
                    # Find the line number from the UsingDecl
                    for j in range(i-1, max(0, i-10), -1):
                        if 'UsingDecl' in lines[j] and current_using_decl in lines[j]:
                            line_match = re.search(r'line:(\d+)', lines[j])
                            if line_match:
                                line_num = int(line_match.group(1))
                                exports.append(ExportInfo(
                                    name=symbol_name,
                                    kind=kind,
                                    line=line_num
                                ))
                                break

                    current_using_decl = None

    # Deduplicate by name (same symbol can have multiple overloads)
    seen = set()
    unique_exports = []
    for exp in exports:
        if exp.name not in seen:
            seen.add(exp.name)
            unique_exports.append(exp)

    return sorted(unique_exports, key=lambda x: x.name)


def extract_regex_exports(module_file: Path) -> Set[str]:
    """
    Extract exports using regex (the fast method).

    This is what symbol_coverage.py currently uses.
    Handles both:
        using std::symbol;
        using std::namespace::symbol;
    """
    exports = set()
    try:
        with open(module_file, 'r', encoding='utf-8') as f:
            for line in f:
                # Match: using std::symbol; or using std::namespace::symbol;
                # Capture the last identifier after ::
                match = re.match(r'\s*using\s+std::(?:\w+::)*(\w+)\s*;', line)
                if match:
                    exports.add(match.group(1))
    except Exception as e:
        print(f"{Colors.RED}Error reading {module_file}: {e}{Colors.RESET}")

    return exports


def validate_module(module_file: Path, list_only: bool = False) -> bool:
    """
    Validate exports for a single module.

    Returns True if validation passes (or list_only mode).
    """
    print(f"\n{Colors.BOLD}{Colors.BLUE}{'='*70}{Colors.RESET}")
    print(f"{Colors.BOLD}Module: {module_file.name}{Colors.RESET}")
    print(f"{Colors.BLUE}{'='*70}{Colors.RESET}")

    # Get Clang AST exports
    ast_dump = get_clang_ast_dump(module_file)
    if not ast_dump:
        print(f"{Colors.RED}✗ Failed to get AST dump{Colors.RESET}")
        return False

    clang_exports = parse_ast_exports(ast_dump, module_file)

    if not clang_exports:
        print(f"{Colors.YELLOW}⚠ No exports found in AST dump{Colors.RESET}")
        print(f"  This could mean:")
        print(f"    - Module has no exports")
        print(f"    - AST parsing failed")
        print(f"    - Module structure differs from expected")
        return False

    clang_names = {exp.name for exp in clang_exports}

    if list_only:
        # Just list what Clang sees
        print(f"\n{Colors.GREEN}Clang AST found {len(clang_exports)} exports:{Colors.RESET}")
        for exp in clang_exports:
            print(f"  {exp}")
        return True

    # Get regex exports for comparison
    regex_exports = extract_regex_exports(module_file)

    # Compare
    print(f"\nClang AST: {len(clang_names)} exports")
    print(f"Regex:     {len(regex_exports)} exports")

    both = clang_names & regex_exports
    only_clang = clang_names - regex_exports
    only_regex = regex_exports - clang_names

    # Print results
    if clang_names == regex_exports:
        print(f"\n{Colors.GREEN}✓ VALIDATION PASSED{Colors.RESET}")
        print(f"  Regex extraction matches Clang AST 100% ({len(both)} symbols)")
        return True
    else:
        match_pct = len(both) / max(len(clang_names), len(regex_exports)) * 100
        print(f"\n{Colors.YELLOW}⚠ MISMATCH (match rate: {match_pct:.1f}%){Colors.RESET}")
        print(f"  {len(both)} symbols in both")

        if only_clang:
            print(f"\n{Colors.YELLOW}Only in Clang AST (not in regex):{Colors.RESET}")
            for name in sorted(only_clang):
                print(f"    {name}")

        if only_regex:
            print(f"\n{Colors.YELLOW}Only in regex (not in Clang AST):{Colors.RESET}")
            for name in sorted(only_regex):
                print(f"    {name}")

        return False


def validate_all_modules(src_dir: Path, list_only: bool = False) -> Tuple[int, int, int]:
    """
    Validate all modules in src directory.

    Returns (passed, failed, skipped) counts.
    """
    module_files = sorted([f for f in src_dir.glob("*.cppm") if f.stem != "std"])

    if not module_files:
        print(f"{Colors.RED}No module files found in {src_dir}{Colors.RESET}")
        return 0, 0, 0

    print(f"{Colors.BOLD}Validating {len(module_files)} modules...{Colors.RESET}")

    passed = 0
    failed = 0
    skipped = 0
    results = []

    for module_file in module_files:
        try:
            result = validate_module(module_file, list_only)
            if result:
                passed += 1
                status = "✓"
                color = Colors.GREEN
            else:
                failed += 1
                status = "✗"
                color = Colors.RED

            results.append((module_file.name, status, color))

        except Exception as e:
            print(f"{Colors.RED}Error validating {module_file.name}: {e}{Colors.RESET}")
            skipped += 1
            results.append((module_file.name, "⊘", Colors.YELLOW))

    # Print summary
    print(f"\n{Colors.BOLD}{Colors.BLUE}{'='*70}{Colors.RESET}")
    print(f"{Colors.BOLD}VALIDATION SUMMARY{Colors.RESET}")
    print(f"{Colors.BLUE}{'='*70}{Colors.RESET}")

    for name, status, color in results:
        print(f"  {color}{status}{Colors.RESET} {name}")

    print(f"\n{Colors.GREEN}Passed:  {passed}{Colors.RESET}")
    if failed > 0:
        print(f"{Colors.RED}Failed:  {failed}{Colors.RESET}")
    if skipped > 0:
        print(f"{Colors.YELLOW}Skipped: {skipped}{Colors.RESET}")

    print(f"{Colors.BLUE}{'='*70}{Colors.RESET}")

    if failed == 0 and passed > 0:
        print(f"{Colors.GREEN}{Colors.BOLD}✓ All modules validated successfully!{Colors.RESET}")
        print(f"  Regex extraction matches Clang AST for all modules.")
    elif failed > 0:
        print(f"{Colors.RED}{Colors.BOLD}✗ Some modules failed validation{Colors.RESET}")
        print(f"  Check the output above for details.")

    return passed, failed, skipped


def main():
    """Main entry point"""
    parser = argparse.ArgumentParser(
        description="Validate C++20 module exports using Clang AST dump",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
Examples:
  %(prog)s                        # Validate all modules
  %(prog)s src/format.cppm        # Validate one module
  %(prog)s --list-only            # List exports without validation
  %(prog)s --no-color             # Disable color output

This tool provides authoritative validation by comparing regex extraction
(used by symbol_coverage.py) against Clang's actual AST view.
"""
    )

    parser.add_argument(
        'module',
        nargs='?',
        type=Path,
        help='Module file to validate (default: all modules in src/)'
    )

    parser.add_argument(
        '--list-only',
        action='store_true',
        help='Just list exports from Clang AST (no validation)'
    )

    parser.add_argument(
        '--no-color',
        action='store_true',
        help='Disable colored output'
    )

    parser.add_argument(
        '--clang',
        default='clang++',
        help='Path to clang++ executable (default: clang++)'
    )

    args = parser.parse_args()

    # Disable colors if requested or not a TTY
    if args.no_color or not sys.stdout.isatty():
        Colors.disable()

    # Banner
    print(f"{Colors.BOLD}{Colors.BLUE}{'='*70}{Colors.RESET}")
    print(f"{Colors.BOLD}C++20 Module Export Validator (Clang AST){Colors.RESET}")
    print(f"{Colors.BLUE}{'='*70}{Colors.RESET}")

    # Check if clang is available
    try:
        subprocess.run(
            [args.clang, "--version"],
            capture_output=True,
            check=True,
            timeout=5
        )
    except (subprocess.CalledProcessError, FileNotFoundError, subprocess.TimeoutExpired):
        print(f"{Colors.RED}Error: {args.clang} not found or not working{Colors.RESET}")
        print(f"Make sure Clang is installed and accessible.")
        return 1

    # Determine repo root
    script_dir = Path(__file__).parent
    repo_root = script_dir.parent
    src_dir = repo_root / "src"

    if not src_dir.exists():
        print(f"{Colors.RED}Error: src/ directory not found at {src_dir}{Colors.RESET}")
        return 1

    # Validate single module or all modules
    if args.module:
        # Validate specific module
        if not args.module.exists():
            print(f"{Colors.RED}Error: Module file not found: {args.module}{Colors.RESET}")
            return 1

        success = validate_module(args.module, args.list_only)
        return 0 if success else 1

    else:
        # Validate all modules
        passed, failed, skipped = validate_all_modules(src_dir, args.list_only)

        if args.list_only:
            return 0

        return 0 if failed == 0 else 1


if __name__ == "__main__":
    sys.exit(main())
