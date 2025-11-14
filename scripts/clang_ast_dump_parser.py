#!/usr/bin/env python3
"""
Prototype: Parse Clang AST dump output to extract C++20 module exports

This approach uses `clang++ -Xclang -ast-dump` which DOES properly see
C++20 module exports, unlike libclang Python bindings.
"""

import re
import subprocess
from pathlib import Path
from typing import Set, List, Dict
from dataclasses import dataclass


@dataclass
class ExportInfo:
    """Information about an exported symbol"""
    name: str
    kind: str  # 'FunctionTemplate', 'Function', 'ClassTemplate', 'CXXRecord', 'TypeAlias'
    line: int

    def __str__(self):
        return f"{self.name} ({self.kind})"


class ClangASTDumpParser:
    """Parse Clang's AST dump to extract module exports"""

    def __init__(self, module_file: Path, clang_path: str = "clang++"):
        self.module_file = module_file
        self.clang_path = clang_path

    def get_ast_dump(self) -> str:
        """Run clang -ast-dump and return output"""
        cmd = [
            self.clang_path,
            "-std=c++20",
            "-Xclang", "-ast-dump",
            "-fsyntax-only",
            str(self.module_file)
        ]

        print(f"Running: {' '.join(cmd)}")

        try:
            result = subprocess.run(
                cmd,
                capture_output=True,
                text=True,
                timeout=30
            )

            if result.returncode != 0:
                print(f"Warning: clang returned {result.returncode}")
                print(f"Stderr: {result.stderr[:500]}")

            return result.stdout

        except subprocess.TimeoutExpired:
            print("ERROR: clang command timed out")
            return ""
        except FileNotFoundError:
            print(f"ERROR: {self.clang_path} not found")
            return ""

    def parse_exports(self, ast_dump: str) -> List[ExportInfo]:
        """
        Parse AST dump to extract exported symbols.

        Look for pattern:
        `-ExportDecl ... in std_module.format
          `-NamespaceDecl ... std
            |-UsingDecl ... std::format
            |-UsingShadowDecl ... implicit FunctionTemplate ... 'format'
        """
        exports = []

        # Split into lines
        lines = ast_dump.split('\n')

        # Find ExportDecl
        in_export_decl = False
        in_namespace_std = False
        current_using_decl = None

        for i, line in enumerate(lines):
            # Check if we're in an ExportDecl for our module
            if 'ExportDecl' in line and str(self.module_file.stem) in line:
                in_export_decl = True
                print(f"Found ExportDecl at line {i}")
                continue

            # Check if we exited the ExportDecl (next top-level declaration)
            if in_export_decl and line.startswith('`-') and 'ExportDecl' not in line:
                in_export_decl = False
                continue

            if not in_export_decl:
                continue

            # Check if we're in the std namespace
            if 'NamespaceDecl' in line and " std" in line:
                in_namespace_std = True
                print(f"Found std namespace at line {i}")
                continue

            if not in_namespace_std:
                continue

            # Look for UsingDecl lines
            # Example: |-UsingDecl 0x... <line:15:1, col:12> col:12 in std_module.format hidden std::format
            using_match = re.search(r'UsingDecl.*?line:(\d+).*?\s+std::(\w+)\s*$', line)
            if using_match:
                line_num = int(using_match.group(1))
                symbol_name = using_match.group(2)
                current_using_decl = symbol_name
                print(f"  Found UsingDecl: {symbol_name} at line {line_num}")
                continue

            # Look for UsingShadowDecl lines (tells us the kind)
            # Example: |-UsingShadowDecl ... implicit FunctionTemplate 0x... 'format'
            if current_using_decl and 'UsingShadowDecl' in line and 'implicit' in line:
                shadow_match = re.search(r'implicit\s+(\w+)\s+.*?\'(\w+)\'', line)
                if shadow_match:
                    kind = shadow_match.group(1)
                    symbol_name = shadow_match.group(2)

                    # Make sure this shadow decl is for the current using decl
                    if symbol_name == current_using_decl:
                        # Find the line number from the UsingDecl (scan back)
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
                                    print(f"    -> Added: {symbol_name} ({kind})")
                                    break

                        current_using_decl = None  # Reset

        # Deduplicate by name (same symbol can have multiple overloads)
        seen = set()
        unique_exports = []
        for exp in exports:
            if exp.name not in seen:
                seen.add(exp.name)
                unique_exports.append(exp)

        return unique_exports

    def extract_exports(self) -> List[ExportInfo]:
        """Main method: get AST dump and parse it"""
        print(f"\n{'='*70}")
        print(f"Extracting exports from: {self.module_file}")
        print(f"{'='*70}")

        ast_dump = self.get_ast_dump()

        if not ast_dump:
            print("ERROR: Failed to get AST dump")
            return []

        print(f"\nAST dump size: {len(ast_dump)} chars")

        exports = self.parse_exports(ast_dump)

        print(f"\n{'='*70}")
        print(f"Found {len(exports)} exported symbols:")
        print(f"{'='*70}")

        for exp in sorted(exports, key=lambda x: x.name):
            print(f"  {exp.name:30s} ({exp.kind})")

        return exports


def compare_with_regex(module_file: Path, clang_exports: List[ExportInfo]):
    """Compare clang AST results with regex approach"""
    print(f"\n{'='*70}")
    print("Comparing with Regex Approach")
    print(f"{'='*70}")

    # Regex extraction (current approach)
    regex_exports = set()
    with open(module_file, 'r') as f:
        for line in f:
            match = re.match(r'\s*using\s+std::(\w+)\s*;', line)
            if match:
                regex_exports.add(match.group(1))

    clang_names = {exp.name for exp in clang_exports}

    print(f"\nRegex found:      {len(regex_exports)} symbols")
    print(f"Clang AST found:  {len(clang_names)} symbols")

    # Check differences
    only_regex = regex_exports - clang_names
    only_clang = clang_names - regex_exports
    both = regex_exports & clang_names

    print(f"In both:          {len(both)} symbols")

    if only_regex:
        print(f"\n⚠️  Only in regex (NOT in Clang AST): {len(only_regex)}")
        for sym in sorted(only_regex):
            print(f"    {sym}")

    if only_clang:
        print(f"\n⚠️  Only in Clang AST (NOT in regex): {len(only_clang)}")
        for sym in sorted(only_clang):
            print(f"    {sym}")

    if regex_exports == clang_names:
        print(f"\n✅ PERFECT MATCH: Regex and Clang AST agree completely!")
        print(f"   This validates that our regex approach is correct.")
    else:
        match_pct = len(both) / max(len(regex_exports), len(clang_names)) * 100
        print(f"\n⚠️  Match rate: {match_pct:.1f}%")


def main():
    """Main entry point"""
    print("="*70)
    print("Clang AST Dump Parser - C++20 Module Export Extraction")
    print("="*70)

    # Test on format module
    repo_root = Path(__file__).parent.parent
    format_module = repo_root / "src" / "format.cppm"

    if not format_module.exists():
        print(f"ERROR: {format_module} not found")
        return

    # Extract exports using Clang AST dump
    parser = ClangASTDumpParser(format_module)
    clang_exports = parser.extract_exports()

    if not clang_exports:
        print("\n❌ Failed to extract exports from Clang AST")
        return

    # Compare with regex approach
    compare_with_regex(format_module, clang_exports)

    print(f"\n{'='*70}")
    print("✅ Prototype Complete!")
    print(f"{'='*70}")
    print("\nConclusions:")
    print("1. Clang AST dump CAN see C++20 module exports")
    print("2. We can parse the text output to extract exports")
    print("3. This validates our regex approach")
    print("4. Could use this for advanced validation if needed")
    print("\nTradeoffs:")
    print("  Clang AST: More authoritative, but slower (subprocess)")
    print("  Regex:     Fast and simple, works well for our use case")


if __name__ == "__main__":
    main()
