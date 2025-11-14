#!/usr/bin/env python3
"""
Symbol Usage Coverage Analyzer for std_module

This script analyzes whether exported symbols in module files (.cppm) are
actually referenced in test files. It provides a coverage metric to ensure
all exported symbols have at least one usage in tests.

Usage:
    ./scripts/symbol_coverage.py <module.cppm> <test_module.cpp>
    ./scripts/symbol_coverage.py --all  # Check all modules

Example:
    ./scripts/symbol_coverage.py src/format.cppm test/test_format.cpp
"""

import re
import sys
from pathlib import Path
from collections import defaultdict
from typing import Set, Dict, Tuple


class Colors:
    """ANSI color codes for terminal output"""
    GREEN = '\033[92m'
    RED = '\033[91m'
    YELLOW = '\033[93m'
    BLUE = '\033[94m'
    BOLD = '\033[1m'
    RESET = '\033[0m'

    @staticmethod
    def disable():
        """Disable colors (for non-TTY output)"""
        Colors.GREEN = ''
        Colors.RED = ''
        Colors.YELLOW = ''
        Colors.BLUE = ''
        Colors.BOLD = ''
        Colors.RESET = ''


def extract_exports(cppm_file: Path) -> Set[str]:
    """
    Extract all exported symbols from a module file.

    Looks for patterns like:
        using std::format;
        using std::format_error;

    Args:
        cppm_file: Path to the .cppm module file

    Returns:
        Set of exported symbol names (without std:: prefix)
    """
    exports = set()

    try:
        with open(cppm_file, 'r', encoding='utf-8') as f:
            for line_num, line in enumerate(f, 1):
                # Match: using std::symbol;
                # Captures symbol name after std::
                match = re.match(r'\s*using\s+std::(\w+(?:::\w+)*)\s*;', line)
                if match:
                    symbol = match.group(1)
                    exports.add(symbol)

    except FileNotFoundError:
        print(f"{Colors.RED}Error: Module file not found: {cppm_file}{Colors.RESET}")
        sys.exit(1)
    except Exception as e:
        print(f"{Colors.RED}Error reading {cppm_file}: {e}{Colors.RESET}")
        sys.exit(1)

    return exports


def find_symbol_usages(test_file: Path, symbols: Set[str]) -> Dict[str, int]:
    """
    Find all usages of symbols in a test file.

    Searches for std::symbol patterns and counts occurrences.

    Args:
        test_file: Path to the test .cpp file
        symbols: Set of symbol names to search for

    Returns:
        Dictionary mapping symbol names to usage counts
    """
    usages = defaultdict(int)

    try:
        with open(test_file, 'r', encoding='utf-8') as f:
            content = f.read()

            # For each exported symbol, find all std::symbol references
            for symbol in symbols:
                # Match std::symbol as a complete word
                # Uses word boundary \b to avoid partial matches
                pattern = rf'\bstd::{re.escape(symbol)}\b'
                matches = re.findall(pattern, content)
                usages[symbol] = len(matches)

    except FileNotFoundError:
        print(f"{Colors.RED}Error: Test file not found: {test_file}{Colors.RESET}")
        sys.exit(1)
    except Exception as e:
        print(f"{Colors.RED}Error reading {test_file}: {e}{Colors.RESET}")
        sys.exit(1)

    return usages


def analyze_coverage(module_file: Path, test_file: Path, verbose: bool = True) -> Tuple[int, int, Set[str]]:
    """
    Analyze symbol coverage for a module/test pair.

    Args:
        module_file: Path to .cppm module file
        test_file: Path to test .cpp file
        verbose: Whether to print detailed output

    Returns:
        Tuple of (used_count, total_count, unused_symbols)
    """
    module_name = module_file.stem

    # Extract exported symbols
    exports = extract_exports(module_file)

    if not exports:
        if verbose:
            print(f"{Colors.YELLOW}Warning: No exported symbols found in {module_file}{Colors.RESET}")
        return 0, 0, set()

    # Find symbol usages in test file
    usages = find_symbol_usages(test_file, exports)

    # Calculate coverage
    used_symbols = set()
    unused_symbols = set()

    if verbose:
        print(f"\n{Colors.BOLD}{Colors.BLUE}📊 Symbol Usage Coverage: {module_name}{Colors.RESET}")
        print("=" * 70)

    # Sort symbols for consistent output
    for symbol in sorted(exports):
        count = usages.get(symbol, 0)

        if count > 0:
            used_symbols.add(symbol)
            if verbose:
                usage_str = f"({count} reference{'s' if count != 1 else ''})"
                print(f"  {Colors.GREEN}✓{Colors.RESET} {symbol:35s} {usage_str}")
        else:
            unused_symbols.add(symbol)
            if verbose:
                print(f"  {Colors.RED}✗{Colors.RESET} {symbol:35s} {Colors.RED}NOT TESTED{Colors.RESET}")

    # Print summary
    total = len(exports)
    used = len(used_symbols)
    coverage_pct = (used / total * 100) if total > 0 else 0

    if verbose:
        print("=" * 70)

        # Color code the coverage percentage
        if coverage_pct == 100:
            color = Colors.GREEN
        elif coverage_pct >= 80:
            color = Colors.YELLOW
        else:
            color = Colors.RED

        print(f"Coverage: {color}{used}/{total} symbols ({coverage_pct:.1f}%){Colors.RESET}")

        if unused_symbols:
            print(f"\n{Colors.YELLOW}⚠️  Untested symbols:{Colors.RESET}")
            for symbol in sorted(unused_symbols):
                print(f"   - {symbol}")
        else:
            print(f"\n{Colors.GREEN}✓ All exported symbols are referenced in tests!{Colors.RESET}")

    return used, total, unused_symbols


def analyze_all_modules(repo_root: Path) -> bool:
    """
    Analyze coverage for all available modules.

    Args:
        repo_root: Path to repository root

    Returns:
        True if all modules have 100% coverage, False otherwise
    """
    src_dir = repo_root / "src"
    test_dir = repo_root / "test"

    # Find all .cppm files
    module_files = [f for f in src_dir.glob("*.cppm")]

    if not module_files:
        print(f"{Colors.RED}Error: No module files found in {src_dir}{Colors.RESET}")
        return False

    total_used = 0
    total_symbols = 0
    all_perfect = True

    print(f"{Colors.BOLD}Analyzing all modules...{Colors.RESET}\n")

    for module_file in sorted(module_files):
        test_file = test_dir / f"test_{module_file.stem}.cpp"

        if not test_file.exists():
            print(f"{Colors.YELLOW}⚠️  No test file found for {module_file.stem} (expected {test_file}){Colors.RESET}")
            continue

        used, total, unused = analyze_coverage(module_file, test_file, verbose=True)
        total_used += used
        total_symbols += total

        if unused:
            all_perfect = False

        print()  # Blank line between modules

    # Print overall summary
    overall_pct = (total_used / total_symbols * 100) if total_symbols > 0 else 0

    print("=" * 70)
    print(f"{Colors.BOLD}Overall Coverage:{Colors.RESET}")

    if overall_pct == 100:
        color = Colors.GREEN
    elif overall_pct >= 80:
        color = Colors.YELLOW
    else:
        color = Colors.RED

    print(f"  {color}{total_used}/{total_symbols} symbols ({overall_pct:.1f}%){Colors.RESET}")
    print("=" * 70)

    return all_perfect


def main():
    """Main entry point"""
    # Disable colors if output is not a TTY
    if not sys.stdout.isatty():
        Colors.disable()

    # Parse arguments
    if len(sys.argv) == 2 and sys.argv[1] == "--all":
        # Analyze all modules
        repo_root = Path(__file__).parent.parent
        analyze_all_modules(repo_root)
        # Always exit successfully - this is an informational report
        sys.exit(0)

    elif len(sys.argv) == 3:
        # Analyze specific module
        module_file = Path(sys.argv[1])
        test_file = Path(sys.argv[2])

        analyze_coverage(module_file, test_file, verbose=True)

        # Always exit successfully - this is an informational report
        sys.exit(0)

    else:
        # Print usage
        print("Usage:")
        print(f"  {sys.argv[0]} <module.cppm> <test_module.cpp>")
        print(f"  {sys.argv[0]} --all")
        print()
        print("Examples:")
        print(f"  {sys.argv[0]} src/format.cppm test/test_format.cpp")
        print(f"  {sys.argv[0]} --all")
        sys.exit(1)


if __name__ == "__main__":
    main()
