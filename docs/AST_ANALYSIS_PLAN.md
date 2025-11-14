# AST-Based Symbol Coverage Analysis - Implementation Plan

## Executive Summary

This document outlines the plan to upgrade `scripts/symbol_coverage.py` from regex-based text matching to Abstract Syntax Tree (AST) based analysis using libclang. This will provide accurate, semantically-aware coverage analysis that distinguishes real code from comments and tracks template instantiations.

---

## 1. Goals and Motivation

### Current Limitations

The existing text-based analyzer has several issues:

1. **False Positives from Comments**
   ```cpp
   // TODO: Test std::format with wide strings
   // ^ This matches "std::format" even though it's not used
   ```

2. **No Template Instantiation Tracking**
   ```cpp
   std::format("{}", 42);           // Uses format<int>
   std::format("{}", 3.14);         // Uses format<double>
   // ^ Both count as 1 reference, but they're different instantiations
   ```

3. **No Overload Resolution**
   ```cpp
   std::format("{}");               // Overload 1
   std::format("{}", 42);           // Overload 2
   std::format("{} {}", 1, 2);      // Overload 3
   // ^ All count as "format" being tested, but only specific overloads
   ```

4. **No Operator Usage Detection**
   ```cpp
   std::vector<int> v1, v2;
   v1 == v2;  // Uses operator==, but text search for "operator==" may miss it
   ```

5. **Cannot Distinguish Declaration from Usage**
   ```cpp
   std::format_error e;  // Declaration only, not tested
   throw std::format_error("test");  // Actually used
   ```

### Benefits of AST-Based Analysis

- ✅ **Semantic accuracy**: Only counts actual code, ignores comments/strings
- ✅ **Template tracking**: Knows which template instantiations occur
- ✅ **Overload awareness**: Can distinguish between different overloads
- ✅ **Usage depth**: Distinguishes declaration, reference, call, construction
- ✅ **Operator detection**: Properly identifies operator usage
- ✅ **Type-aware**: Understands inheritance, implicit conversions, ADL

---

## 2. Technical Approach

### Tool Selection: libclang Python Bindings

**Choice: `libclang` (Python bindings)**

**Pros:**
- ✅ Official LLVM/Clang API
- ✅ Python bindings readily available (`pip install libclang`)
- ✅ Handles C++20 modules (with recent Clang versions)
- ✅ Full AST access
- ✅ No need to write C++ tool

**Alternatives Considered:**

| Tool | Pros | Cons | Decision |
|------|------|------|----------|
| **libclang (Python)** | Easy integration, Python ecosystem, full AST | Needs libclang.so installed | ✅ **SELECTED** |
| Clang Libtooling (C++) | Most powerful, fastest | Requires C++ code, complex | ❌ Too heavy |
| Tree-sitter | Fast, incremental | Limited semantic info | ❌ Not semantic enough |
| CppHeaderParser | Pure Python | Cannot handle C++20 modules | ❌ Too limited |

### Architecture Overview

```
┌─────────────────────────────────────────────────────────────┐
│                   symbol_coverage.py                        │
│                   (Entry point / CLI)                       │
└────────────────────────┬────────────────────────────────────┘
                         │
         ┌───────────────┴───────────────┐
         │                               │
         ▼                               ▼
┌────────────────────┐          ┌────────────────────┐
│  Regex Analyzer    │          │   AST Analyzer     │
│  (Legacy/Fallback) │          │   (New Primary)    │
└────────────────────┘          └─────────┬──────────┘
                                          │
                    ┌─────────────────────┼─────────────────────┐
                    │                     │                     │
                    ▼                     ▼                     ▼
           ┌────────────────┐    ┌────────────────┐   ┌────────────────┐
           │ Module Parser  │    │  Test Parser   │   │ Usage Analyzer │
           │ (Extract       │    │ (Find symbol   │   │ (Correlation & │
           │  exports)      │    │  references)   │   │  reporting)    │
           └────────────────┘    └────────────────┘   └────────────────┘
```

---

## 3. Implementation Design

### Phase 1: Core AST Infrastructure

**Goal:** Set up libclang and basic AST traversal

#### Components:

1. **`ASTModuleParser`** - Parse `.cppm` files
   ```python
   class ASTModuleParser:
       def __init__(self, cppm_file: Path, clang_args: List[str]):
           self.translation_unit = parse_file(cppm_file, clang_args)

       def extract_exports(self) -> List[ExportedSymbol]:
           """
           Walk AST to find export declarations.
           Returns structured info about each exported symbol.
           """
   ```

2. **`ASTTestParser`** - Parse test `.cpp` files
   ```python
   class ASTTestParser:
       def __init__(self, test_file: Path, clang_args: List[str]):
           self.translation_unit = parse_file(test_file, clang_args)

       def find_symbol_usages(self, symbols: List[str]) -> Dict[str, List[Usage]]:
           """
           Walk AST to find where symbols are used.
           Returns usage details (call, construction, reference, etc.)
           """
   ```

3. **`ExportedSymbol`** - Data class for exported entities
   ```python
   @dataclass
   class ExportedSymbol:
       name: str
       kind: str  # 'function', 'class', 'type_alias', 'variable', etc.
       overloads: List[str]  # For functions: parameter types
       location: SourceLocation
       is_template: bool
       template_params: List[str]
   ```

4. **`Usage`** - Data class for symbol references
   ```python
   @dataclass
   class Usage:
       symbol: str
       kind: str  # 'call', 'construct', 'reference', 'declaration'
       location: SourceLocation
       template_args: List[str]  # For template instantiations
       context: str  # Surrounding code snippet
   ```

#### Key Algorithms:

**Export Extraction:**
```python
def extract_exports(cursor):
    """
    Recursively walk AST looking for export declarations.
    Handle: export namespace std { using std::format; }
    """
    if cursor.kind == CursorKind.NAMESPACE_DECL:
        if has_export_attribute(cursor):
            for child in cursor.get_children():
                if child.kind == CursorKind.USING_DECLARATION:
                    yield parse_using_declaration(child)
```

**Usage Finding:**
```python
def find_usages(cursor, target_symbols):
    """
    Recursively walk AST looking for references to target symbols.
    Handle: std::format(...), throw std::format_error(...), etc.
    """
    if cursor.kind == CursorKind.CALL_EXPR:
        callee = get_callee_name(cursor)
        if callee in target_symbols:
            yield Usage(symbol=callee, kind='call', ...)

    elif cursor.kind == CursorKind.DECL_REF_EXPR:
        ref = get_referenced_decl(cursor)
        if ref.spelling in target_symbols:
            yield Usage(symbol=ref.spelling, kind='reference', ...)

    # Recurse to children
    for child in cursor.get_children():
        yield from find_usages(child, target_symbols)
```

#### Testing:

- Unit tests with minimal C++ snippets
- Test parsing a simple module with 5 exports
- Test finding usages in a simple test file
- Verify comment exclusion works

---

### Phase 2: Advanced Analysis Features

**Goal:** Implement template tracking and overload detection

#### Components:

1. **Template Instantiation Tracker**
   ```python
   def track_template_instantiation(call_expr):
       """
       For template function calls, extract template arguments.
       Example: std::format<int>("{}", 42)
       Returns: ('format', ['int'])
       """
   ```

2. **Overload Resolver**
   ```python
   def resolve_overload(call_expr, available_overloads):
       """
       Match call expression to specific function overload.
       Uses parameter types and count.
       """
   ```

3. **Operator Usage Detector**
   ```python
   def find_operator_usage(cursor):
       """
       Detect operator calls: v1 == v2 -> operator==
       Handle both member and free function operators.
       """
   ```

#### Enhanced Reporting:

```
📊 Symbol Usage Coverage: format (AST Analysis)
======================================================================
Function Overloads:
  ✓ format(string_view)                 (3 calls)
  ✓ format(string_view, Args&&...)      (15 calls)
  ✗ format(locale, string_view)          NOT TESTED

Template Instantiations:
  ✓ format<int>                          (5 instantiations)
  ✓ format<double>                       (3 instantiations)
  ✓ format<string>                       (7 instantiations)

Types:
  ✓ format_error                         (2 constructions, 1 catch)
  ✗ format_args                          NOT USED

======================================================================
Coverage: 18/22 entities (81.8%)
```

---

### Phase 3: Integration and Polish

**Goal:** Integrate with existing workflow, add fallback

#### Components:

1. **Analyzer Strategy Pattern**
   ```python
   class CoverageAnalyzer(ABC):
       @abstractmethod
       def analyze(self, module_file, test_file) -> CoverageReport:
           pass

   class ASTAnalyzer(CoverageAnalyzer):
       def analyze(self, module_file, test_file) -> CoverageReport:
           # AST-based analysis

   class RegexAnalyzer(CoverageAnalyzer):
       def analyze(self, module_file, test_file) -> CoverageReport:
           # Legacy text-based analysis

   def get_analyzer(prefer_ast=True) -> CoverageAnalyzer:
       if prefer_ast and libclang_available():
           return ASTAnalyzer()
       return RegexAnalyzer()
   ```

2. **Automatic Fallback**
   - Try AST analysis first
   - If libclang not available, fall back to regex
   - Print warning about using legacy mode

3. **Configuration File**
   ```yaml
   # .symbol-coverage.yml
   analyzer: ast  # or 'regex' or 'auto'

   clang:
     executable: /usr/bin/clang++
     flags:
       - -std=c++20
       - -I/usr/include/c++/11

   reporting:
     show_template_instantiations: true
     show_overloads: true
     show_usage_context: false  # Can be verbose
     group_by_category: true
   ```

---

## 4. Implementation Phases

### Phase 1: Foundation (Week 1)
- [ ] Research libclang Python bindings API
- [ ] Create `ast_analyzer.py` module
- [ ] Implement basic AST traversal for exports
- [ ] Implement basic AST traversal for usages
- [ ] Write unit tests for core functionality
- [ ] Test on 3 simple modules (format, vector, exception)

**Deliverable:** Working AST analyzer for basic cases

---

### Phase 2: Advanced Features (Week 2)
- [ ] Implement template instantiation tracking
- [ ] Implement overload resolution
- [ ] Implement operator detection
- [ ] Handle edge cases (operators, nested templates, ADL)
- [ ] Enhanced reporting with categories
- [ ] Test on complex modules (algorithm, functional, iterator)

**Deliverable:** Full-featured AST analyzer

---

### Phase 3: Integration (Week 3)
- [ ] Refactor existing code to use strategy pattern
- [ ] Implement automatic fallback logic
- [ ] Add configuration file support
- [ ] Update CLI to support `--analyzer` flag
- [ ] Update documentation
- [ ] Run on all 48 modules and compare results

**Deliverable:** Production-ready integrated solution

---

### Phase 4: Polish and Documentation (Week 4)
- [ ] Performance optimization (caching ASTs)
- [ ] Better error messages
- [ ] Comprehensive test suite
- [ ] Update scripts/README.md
- [ ] Update CLAUDE.md with AST usage
- [ ] Add examples and troubleshooting guide

**Deliverable:** Complete, documented, production-ready tool

---

## 5. Technical Challenges and Solutions

### Challenge 1: C++20 Module Parsing

**Problem:** Clang may not parse `.cppm` files correctly without proper flags

**Solution:**
```python
clang_args = [
    '-std=c++20',
    '-x', 'c++',  # Force C++ mode
    '-fmodules-ts',  # Enable modules TS
    '-I/usr/include/c++/11',  # Include paths
    '-I/path/to/project/src',
]
```

### Challenge 2: Export Declaration AST Structure

**Problem:** `export namespace std { using std::format; }` has complex AST structure

**Solution:**
- Walk AST looking for `NAMESPACE_DECL` with export attribute
- Within that, find `USING_DECLARATION` nodes
- Extract the entity being imported

### Challenge 3: Template Instantiation Tracking

**Problem:** Template arguments may not be explicit in AST

**Solution:**
- Use `cursor.get_template_argument_kind()` and `cursor.get_template_argument_type()`
- Handle implicit instantiations by looking at actual argument types
- Track both explicit (`format<int>(...)`) and implicit (`format(..., 42)`)

### Challenge 4: Operator Overload Detection

**Problem:** Operators can be member functions, free functions, or built-in

**Solution:**
```python
if cursor.kind == CursorKind.CALL_EXPR:
    callee = cursor.referenced
    if callee and callee.spelling.startswith('operator'):
        # It's an operator overload
        operator_name = callee.spelling  # e.g., "operator=="
```

### Challenge 5: libclang Not Available

**Problem:** Users may not have libclang installed

**Solution:**
- Automatic fallback to regex analyzer
- Clear error message with installation instructions
- Document both methods in README

---

## 6. Testing Strategy

### Unit Tests

**Test File Structure:**
```
test/symbol_coverage/
├── test_ast_module_parser.py
├── test_ast_test_parser.py
├── test_usage_analyzer.py
├── test_integration.py
└── fixtures/
    ├── simple_module.cppm
    ├── template_module.cppm
    ├── operator_module.cppm
    ├── test_simple.cpp
    ├── test_template.cpp
    └── test_operator.cpp
```

**Test Categories:**

1. **Export Parsing Tests**
   - Simple `using` declarations
   - Template exports
   - Type alias exports
   - Namespace exports
   - Operator exports

2. **Usage Detection Tests**
   - Function calls
   - Constructor calls
   - Template instantiations
   - Operator usage
   - Type references

3. **Edge Case Tests**
   - Comments containing symbol names
   - String literals containing symbol names
   - Nested templates
   - Overloaded operators
   - ADL operator calls

4. **Integration Tests**
   - Full module analysis
   - Compare AST vs Regex results
   - Performance benchmarks

### Validation

**Acceptance Criteria:**

1. ✅ Correctly ignores comments (no false positives)
2. ✅ Tracks at least 3 template instantiations for `format`
3. ✅ Distinguishes `operator<<` usage from text search failures
4. ✅ Runs on all 48 existing modules without errors
5. ✅ Falls back gracefully when libclang unavailable
6. ✅ Performance: < 5 seconds for all modules (on reference hardware)

---

## 7. Migration Path

### Backward Compatibility

**Goal:** No breaking changes to CLI or output format

**Strategy:**
```bash
# Default: Try AST, fallback to regex
./scripts/symbol_coverage.py --all

# Force AST (error if unavailable)
./scripts/symbol_coverage.py --all --analyzer=ast

# Force regex (legacy mode)
./scripts/symbol_coverage.py --all --analyzer=regex

# Show which analyzer is used
./scripts/symbol_coverage.py --all --verbose
```

### Deprecation Timeline

- **Phase 1 (Now):** Both analyzers available, AST preferred
- **Phase 2 (3 months):** Regex analyzer deprecated, warning shown
- **Phase 3 (6 months):** Regex analyzer removed (or moved to legacy)

---

## 8. Documentation Updates

### Files to Update:

1. **`scripts/README.md`**
   - Replace "Future: AST-Based Analysis" section with "AST-Based Analysis"
   - Add installation instructions for libclang
   - Update examples to show new output format
   - Document `--analyzer` flag

2. **`CLAUDE.md`**
   - Update "Symbol Coverage Analysis" section
   - Add troubleshooting for libclang issues
   - Update examples with template tracking output

3. **New: `docs/AST_ANALYSIS.md`**
   - Deep dive into AST analysis internals
   - Guide for extending the analyzer
   - Technical reference for developers

---

## 9. Performance Considerations

### Optimization Strategies:

1. **AST Caching**
   ```python
   # Cache parsed ASTs to avoid re-parsing
   ast_cache = {}

   def get_ast(file_path, clang_args):
       cache_key = (file_path, tuple(clang_args))
       if cache_key not in ast_cache:
           ast_cache[cache_key] = parse_file(file_path, clang_args)
       return ast_cache[cache_key]
   ```

2. **Parallel Processing**
   ```python
   # Analyze modules in parallel
   with multiprocessing.Pool() as pool:
       results = pool.starmap(analyze_module, module_test_pairs)
   ```

3. **Lazy Analysis**
   - Only parse files when needed
   - Skip test file parsing if module has no exports

### Performance Targets:

| Metric | Target | Stretch Goal |
|--------|--------|--------------|
| Single module | < 500ms | < 200ms |
| All 48 modules | < 5s | < 2s |
| Memory usage | < 500MB | < 250MB |

---

## 10. Dependencies and Requirements

### Runtime Dependencies:

```
# requirements.txt
libclang>=16.0.0  # Python bindings for libclang
pyyaml>=6.0       # For configuration file parsing
```

### System Requirements:

- **libclang.so** installed (system package)
  - Ubuntu/Debian: `apt-get install libclang-16-dev`
  - Fedora: `dnf install clang-devel`
  - macOS: `brew install llvm`

- **Clang 16+** (for C++20 module support)

### Development Dependencies:

```
pytest>=7.0
pytest-cov>=4.0
mypy>=1.0  # Type checking
black>=23.0  # Code formatting
```

---

## 11. Success Metrics

### Quantitative Goals:

- ✅ **Accuracy:** 0 false positives from comments
- ✅ **Detail:** Track ≥ 3 template instantiations per templated function
- ✅ **Coverage:** Works on 100% of existing 48 modules
- ✅ **Performance:** Analyzes all modules in < 5 seconds
- ✅ **Reliability:** Fallback works when libclang unavailable

### Qualitative Goals:

- ✅ Users can understand overload coverage
- ✅ Template usage is visible in reports
- ✅ Tool is self-documenting (good error messages)
- ✅ Easy to extend for new analysis types

---

## 12. Future Enhancements (Post-MVP)

### Possible Features:

1. **Call Graph Analysis**
   - Show which tests call which functions
   - Identify indirect usage

2. **Semantic Diff**
   - Compare exported API between versions
   - Detect breaking changes

3. **Usage Heatmap**
   - Visualize which parts of API are heavily used
   - Identify under-tested areas

4. **Integration with IDEs**
   - VS Code extension showing coverage inline
   - Jump to test from export declaration

5. **Machine Learning Suggestions**
   - Suggest missing tests based on similar modules
   - Recommend test patterns

---

## 13. Risks and Mitigations

| Risk | Impact | Probability | Mitigation |
|------|--------|-------------|------------|
| libclang API changes | High | Low | Pin version, test with multiple Clang versions |
| C++20 modules not supported | High | Medium | Test early, document limitations, keep regex fallback |
| Performance too slow | Medium | Low | Profile early, optimize hot paths, add caching |
| Complex to maintain | Medium | Medium | Good tests, clear documentation, modular design |
| Users don't have libclang | Low | High | Automatic fallback, clear installation docs |

---

## 14. Timeline and Milestones

```
Week 1: Foundation
├─ Day 1-2: Research and prototype basic AST traversal
├─ Day 3-4: Implement export extraction
├─ Day 5: Implement basic usage detection
└─ Day 6-7: Unit tests and validation

Week 2: Advanced Features
├─ Day 8-9: Template instantiation tracking
├─ Day 10-11: Overload resolution
├─ Day 12: Operator detection
└─ Day 13-14: Complex module testing

Week 3: Integration
├─ Day 15-16: Refactor to strategy pattern
├─ Day 17: Fallback logic and configuration
├─ Day 18-19: CLI integration
└─ Day 20-21: Full module suite testing

Week 4: Polish
├─ Day 22-23: Performance optimization
├─ Day 24-25: Documentation
├─ Day 26: User testing and feedback
└─ Day 27-28: Final fixes and release
```

---

## 15. References and Resources

### Documentation:

- [libclang Python Bindings](https://libclang.readthedocs.io/)
- [Clang AST Introduction](https://clang.llvm.org/docs/IntroductionToTheClangAST.html)
- [C++20 Modules in Clang](https://clang.llvm.org/docs/Modules.html)

### Similar Tools:

- [Clazy](https://github.com/KDE/clazy) - Clang plugin for Qt code
- [clang-tidy](https://clang.llvm.org/extra/clang-tidy/) - Linter using Clang AST
- [include-what-you-use](https://github.com/include-what-you-use/include-what-you-use)

### Code Examples:

- [Python libclang examples](https://github.com/llvm/llvm-project/tree/main/clang/bindings/python/examples)
- [AST traversal patterns](https://eli.thegreenplace.net/2011/07/03/parsing-c-in-python-with-clang)

---

## Conclusion

AST-based analysis will transform symbol coverage from a simple text-matching tool into a powerful, semantically-aware analyzer. The phased approach ensures we can deliver value incrementally while maintaining backward compatibility.

**Next Steps:**
1. Review and approve this plan
2. Set up development environment with libclang
3. Begin Phase 1 implementation
4. Iterate based on findings

**Questions for Discussion:**
- Should we support multiple libclang versions, or require Clang 16+?
- Do we want to generate JSON output for CI integration?
- Should operator coverage be a separate metric from function coverage?
