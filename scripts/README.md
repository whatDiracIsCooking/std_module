# std_module Scripts

This directory contains utility scripts for the std_module project.

## Symbol Coverage Analysis

### Overview

`symbol_coverage.py` analyzes whether all symbols exported by module files (`.cppm`) are actually referenced in their corresponding test files. This helps ensure comprehensive test coverage.

### Why Symbol Coverage?

Traditional code coverage tools (gcov/lcov) measure **executed lines**, but in this project:
- Module files consist mostly of `using std::symbol;` declarations
- These declarations don't generate executable code
- They're compile-time constructs, so gcov reports ~0% coverage (false negative)

**Symbol coverage** measures whether each exported symbol is **used in tests**, which is what actually matters for a wrapper library.

### Usage

Symbol coverage runs **automatically** with the test suite:

```bash
# Build and run all tests (includes symbol coverage)
cmake --build build
ctest --test-dir build --output-on-failure
```

#### Skipping Symbol Coverage

To run tests without symbol coverage:

```bash
# Exclude symbol coverage from test run
ctest --test-dir build --exclude-regex symbol-coverage
```

#### Manual Invocation

```bash
# Run symbol coverage directly (bypasses CTest)
./scripts/symbol_coverage.py --all

# Analyze specific module
./scripts/symbol_coverage.py src/format.cppm test/test_format.cpp

# Via CMake custom target
cmake --build build --target symbol-coverage-target
```

### Example Output

```
📊 Symbol Usage Coverage: format
======================================================================
  ✓ format                              (21 references)
  ✓ format_to                           (3 references)
  ✓ format_error                        (2 references)
  ✗ format_args                         NOT TESTED
  ✗ basic_format_arg                    NOT TESTED
======================================================================
Coverage: 14/25 symbols (56.0%)

⚠️  Untested symbols:
   - basic_format_arg
   - format_args
```

### Interpretation

- **✓ Green checkmark**: Symbol is referenced in tests
- **✗ Red X**: Symbol is not referenced at all
- **Reference count**: Number of times `std::symbol` appears in test file

### Limitations

This is a **text-based** analysis tool:

**Pros:**
- ✅ Fast (no compilation required)
- ✅ Simple to understand
- ✅ Catches obviously missing symbols
- ✅ Works with any text editor

**Cons:**
- ❌ Doesn't measure **quality** of testing (1 reference = "covered")
- ❌ Text-based matching (could match in comments, though unlikely to cause issues)
- ❌ Doesn't detect if you test `std::format` but not all its overloads

**Recommendation:** Use this as a **smoke test** to catch obviously untested exports. Manual review ensures test quality.

### CI Integration

Symbol coverage runs automatically as part of the test suite. The test exits with:
- **Code 0**: All symbols covered (100%)
- **Code 1**: Some symbols untested (< 100%)

In CI, symbol coverage will run with your regular tests:

```yaml
# .github/workflows/ci.yml
- name: Build and test
  run: |
    cmake -B build -G Ninja
    cmake --build build
    ctest --test-dir build --output-on-failure
    # Symbol coverage runs automatically as test #6
```

To make CI pass despite incomplete coverage, exclude the test:

```yaml
# If you want CI to pass with <100% coverage
- name: Run tests (skip coverage check)
  run: ctest --test-dir build --exclude-regex symbol-coverage
```

### Current Coverage (as of last check)

| Module | Coverage | Status |
|--------|----------|--------|
| bitset | 100.0% | ✅ Perfect |
| string_view | 85.7% | 🟡 Good |
| vector | 75.0% | 🟡 Good |
| algorithm | 58.9% | 🟠 Needs work |
| format | 56.0% | 🟠 Needs work |
| **Overall** | **60.9%** | 🟠 |

Many untested symbols are low-level types (like `basic_format_arg`, `format_args`) that are implicitly used but not directly referenced. Consider whether these need explicit tests.

### Improving Coverage

To improve coverage for a module:

1. Run symbol coverage to see untested symbols:
   ```bash
   ./scripts/symbol_coverage.py src/format.cppm test/test_format.cpp
   ```

2. For each untested symbol, decide:
   - **User-facing API**: Add explicit test
   - **Internal type**: May be tested implicitly (e.g., `format_args` is used by `std::format`)
   - **Rare/deprecated**: Document why it's not tested

3. Add tests to `test/test_{module}.cpp`

4. Re-run coverage to verify

### Future: AST-Based Analysis

A more sophisticated version using Clang's AST could:
- Distinguish actual usage from comments
- Track template instantiations
- Measure overload coverage

For now, the text-based approach is a good balance of simplicity and utility.

## Other Scripts

(Placeholder for future scripts)
