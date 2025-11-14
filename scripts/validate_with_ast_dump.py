#!/usr/bin/env python3
"""
Test Clang AST dump parser on multiple modules to validate regex approach
"""

from pathlib import Path
from clang_ast_dump_parser import ClangASTDumpParser
import re


def quick_regex_extract(module_file: Path) -> set:
    """Quick regex extraction"""
    exports = set()
    with open(module_file, 'r') as f:
        for line in f:
            match = re.match(r'\s*using\s+std::(\w+)\s*;', line)
            if match:
                exports.add(match.group(1))
    return exports


def test_module(module_file: Path) -> bool:
    """Test a single module"""
    print(f"\n{'='*70}")
    print(f"Testing: {module_file.name}")
    print(f"{'='*70}")

    # Get Clang AST exports
    parser = ClangASTDumpParser(module_file)
    clang_exports = parser.extract_exports()

    if not clang_exports:
        print("  ❌ Failed to extract from Clang AST")
        return False

    clang_names = {exp.name for exp in clang_exports}

    # Get regex exports
    regex_exports = quick_regex_extract(module_file)

    # Compare
    print(f"\n  Regex: {len(regex_exports)} exports")
    print(f"  Clang: {len(clang_names)} exports")

    if regex_exports == clang_names:
        print(f"  ✅ MATCH - Regex approach validated!")
        return True
    else:
        only_regex = regex_exports - clang_names
        only_clang = clang_names - regex_exports

        if only_regex:
            print(f"  ⚠️  Only in regex: {only_regex}")
        if only_clang:
            print(f"  ⚠️  Only in Clang: {only_clang}")

        return False


def main():
    """Test on multiple modules"""
    print("="*70)
    print("Validation Test: Clang AST vs Regex for Multiple Modules")
    print("="*70)

    repo_root = Path(__file__).parent.parent
    src_dir = repo_root / "src"

    # Test on a few key modules
    test_modules = [
        "format.cppm",
        "vector.cppm",
        "iostream.cppm",
        "algorithm.cppm",
        "string_view.cppm"
    ]

    results = {}

    for module_name in test_modules:
        module_path = src_dir / module_name
        if module_path.exists():
            results[module_name] = test_module(module_path)
        else:
            print(f"\n⚠️  {module_name} not found, skipping")
            results[module_name] = None

    # Summary
    print(f"\n{'='*70}")
    print("VALIDATION SUMMARY")
    print(f"{'='*70}")

    passed = sum(1 for r in results.values() if r is True)
    failed = sum(1 for r in results.values() if r is False)
    skipped = sum(1 for r in results.values() if r is None)

    for module_name, result in results.items():
        if result is True:
            print(f"  ✅ {module_name:30s} - Validated")
        elif result is False:
            print(f"  ❌ {module_name:30s} - Mismatch")
        else:
            print(f"  ⊘  {module_name:30s} - Skipped")

    print(f"\n  Passed:  {passed}")
    print(f"  Failed:  {failed}")
    print(f"  Skipped: {skipped}")

    if failed == 0 and passed > 0:
        print(f"\n{'='*70}")
        print("✅ CONCLUSION: Regex approach is validated across all tested modules!")
        print("   The regex method correctly extracts what Clang's compiler sees.")
        print(f"{'='*70}")
    elif failed > 0:
        print(f"\n⚠️  Some modules show discrepancies - investigation needed")


if __name__ == "__main__":
    main()
