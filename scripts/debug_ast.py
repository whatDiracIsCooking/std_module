#!/usr/bin/env python3
"""
Debug script to dump AST structure of C++ files.
Helps understand how libclang represents different C++ constructs.
"""

import sys
from pathlib import Path

try:
    import clang.cindex as clang
    from clang.cindex import CursorKind
except ImportError:
    print("ERROR: libclang not installed")
    print("Install with: pip install libclang")
    sys.exit(1)


def dump_ast(cursor, depth=0, max_depth=15):
    """Recursively dump AST structure"""
    if depth > max_depth:
        return

    indent = "  " * depth

    # Get location info
    location = ""
    if cursor.location.file:
        location = f" @ {cursor.location.file}:{cursor.location.line}"

    # Get additional info
    info = []
    if cursor.spelling:
        info.append(f"spelling='{cursor.spelling}'")
    if cursor.displayname:
        info.append(f"display='{cursor.displayname}'")
    if cursor.kind == CursorKind.USING_DECLARATION:
        info.append(f"type='{cursor.type.spelling}'")

    info_str = " | " + ", ".join(info) if info else ""

    print(f"{indent}{cursor.kind}{info_str}{location}")

    # Recurse
    for child in cursor.get_children():
        dump_ast(child, depth + 1, max_depth)


def main():
    if len(sys.argv) < 2:
        print("Usage: python debug_ast.py <file.cpp> [max_depth]")
        sys.exit(1)

    file_path = Path(sys.argv[1])
    max_depth = int(sys.argv[2]) if len(sys.argv) > 2 else 15

    if not file_path.exists():
        print(f"Error: File not found: {file_path}")
        sys.exit(1)

    # Configure libclang
    try:
        clang.Config.set_library_file('/usr/lib/x86_64-linux-gnu/libclang-18.so.1')
    except:
        pass

    # Parse file
    index = clang.Index.create()
    tu = index.parse(
        str(file_path),
        args=['-std=c++20', '-x', 'c++'],
        options=clang.TranslationUnit.PARSE_DETAILED_PROCESSING_RECORD
    )

    print(f"AST for {file_path}:")
    print("="*70)
    dump_ast(tu.cursor, max_depth=max_depth)


if __name__ == "__main__":
    main()
