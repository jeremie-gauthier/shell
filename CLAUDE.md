# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

This is a POSIX shell implementation in C (42sh) featuring lexical analysis, parsing, AST construction, and command interpretation with parameter expansion support.

## Build Commands

**Default build (debug mode with sanitizers):**
```bash
make              # Build with -g and -fsanitize=address,undefined
make -j4          # Parallel build (faster)
./42sh            # Run the shell
```

**Production build (optimized, no debug symbols):**
```bash
make production   # Clean build with -O2, no sanitizers
```

**Development tools:**
```bash
make lldb         # Build and launch in lldb debugger
make leaks        # Run with memory leak detection
make analyze      # Run Clang static analyzer
make test         # Build test suite (./42sh_test to run)
```

**Clean build artifacts:**
```bash
make clean        # Remove object files and dependency files
make fclean       # Remove all build artifacts including binaries
make re           # Clean rebuild (fclean + all)
```

**Notes:**
- Default build includes debug symbols and address/undefined behavior sanitizers
- Automatic dependency tracking: modifying headers triggers recompilation of affected files only
- Build output shows colored progress: `[42/104] CC src/main.c`

## Architecture

The shell follows a classic interpreter pipeline: **Input → Lexer → Parser → AST → Interpreter → Execution**

### Core Pipeline

1. **Lexer** (`src/lexer/`, `includes/lexer.h`)
   - Tokenizes input into terminals (words, operators, expansions)
   - Handles parameter expansions (`$VAR`, `${VAR:-default}`, etc.) and tilde expansions (`~`, `~/path`)
   - Main entry: `get_next_token()` advances through input and returns tokens
   - Terminal parsers in `src/lexer/terminals/`: `word()`, `parse_expansion()`, `parse_param_expansion()`, `parse_tilde_expansion()`

2. **Parser** (`src/parser/`, `includes/parser.h`)
   - Recursive descent parser that builds an AST from tokens
   - Grammar defined in `docs/grammar.bnf` (simplified POSIX subset)
   - Parser rules in `src/parser/rules/`: `parse_cmd()`, `parse_expr()`
   - Uses `eat()` to consume expected token types

3. **AST** (`src/ast/`, `includes/ast.h`)
   - Binary tree structure with token nodes
   - Each node has `left`, `right` children and a `token` payload
   - Supports prefix traversal via `ast_apply_prefix()`

4. **Interpreter** (`src/interpreter/`, `includes/interpreter.h`)
   - Walks the AST and executes commands
   - Substitutes parameter expansions before execution via `subst_param_exps()` and `subst_cmd_words()`
   - Visitor pattern: `command_visitor.c` extracts command metadata from tokens
   - Entry point: `interpreter()` in `src/interpreter/interpreter.c`

5. **Process Execution** (`src/process/`, `includes/process.h`)
   - Command resolution: searches PATH, handles builtins, file paths
   - `find_command()` locates executable and determines command type (BuiltIn, Path, File)
   - `run_command()` dispatches to builtin handlers or spawns processes via `run_process()`

### Token System

All tokens use a discriminated union (`t_token` in `includes/token.h`):

- **Word tokens** (`t_word_token`): Text with optional parameter expansions (stored as vector)
- **Expansion tokens** (`t_expansion_token`): Parameter/tilde expansions with location, parameter name, substitution text, and expansion type
- **Command tokens** (`t_command_token`): Command name (word) + arguments (vector of words)
- **Pipeline tokens** (`t_pipeline_token`): Array of commands (not yet fully implemented)

Token types: `Word`, `Command`, `CommandSeparator`, `End`, `UnknownToken`

### Parameter Expansion

Supports 10 POSIX parameter expansion types (defined in `enum e_param_exp_type`):

- Simple: `$VAR` or `${VAR}`
- Default values: `${VAR:-word}`, `${VAR:=word}`, `${VAR:+word}`
- Error handling: `${VAR:?word}`
- String operations: `${#VAR}`, `${VAR#pattern}`, `${VAR##pattern}`, `${VAR%pattern}`, `${VAR%%pattern}`

Substitution functions in `src/expansions/parameter/` (e.g., `param_simple_subst()`, `param_alt_subst()`)

### Custom Libraries (`lib/`)

Internal utility libraries (prefixed with `lib_` in includes):

- **lib_str**: String manipulation (strdup, strlen, strcmp, split, join, etc.)
- **lib_vec**: Dynamic vector/array (`t_vec` type, see `includes/lib_vec.h`)
- **lib_ht**: Hash table (`t_ht` type for shell cache, see `includes/lib_ht.h`)
- **lib_mem**: Memory utilities (memcpy, memset, bzero)
- **lib_io**: I/O utilities including `get_next_line()` and `readline()`
- **lib_arr**: Array utilities
- **lib_char**: Character utilities

### Shell State

Global shell state (`t_shell` in `includes/shell.h`):

```c
typedef struct s_shell {
    char **env;                      // Environment variables
    t_cache cache;                   // Binary path cache (hash table)
    enum e_shell_status status;      // RUNNING or STOPPED
    unsigned char last_exit_status;  // Exit code of last command
} t_shell;
```

Lifecycle: `sh_create()` → `sh_run()` → `sh_free()`

Main loop in `src/shell/sh_run.c`: read input → lex → parse → interpret → display prompt

### Builtins (`src/builtins/`, `includes/builtin.h`)

Implemented: `exit`, `echo`, `env`, `setenv`, `unsetenv`, `cd`

Each builtin follows signature: `int builtin_*(t_shell *shell, const t_cmd *command)`

### Signal Handling (`src/signals/`)

- `sig_init()`: Initialize signal state
- `sigint()`: Handle Ctrl+C (SIGINT) gracefully

Global signal state in `t_sig g_sig`

## Development Notes

### Compilation

- Compiler: `clang`
- Default flags: `-Wall -Wextra -Werror -Wconversion -g -fsanitize=address,undefined`
- Production flags: `-Wall -Wextra -Werror -Wconversion -O2`
- Automatic dependency tracking enabled (`-MMD -MP`)
- All headers in `includes/` directory (specified via `-I$(HEADER_DIR)`)

### Debugging

**VSCode Integration:**
- `.vscode/launch.json` configured with two debugger options:
  1. "C/C++: clang déboguer le projet" - Launch debugger with built binary
  2. "Attach to 42sh" - Attach to running process (build with `make`, run `./42sh` in terminal, then attach)
- Use `make lldb` to build and launch lldb from command line

**Memory Debugging:**
- Default build includes AddressSanitizer and UndefinedBehaviorSanitizer
- `make leaks` runs with macOS leak detection
- `make analyze` performs Clang static analysis (detects dead stores, memory leaks, null dereferences)

### Testing

Test framework: CuTest (`tests/CuTest.h`)

Test files in `tests/` directory. Test suite entry: `tests/AllTests.c`

Note: Test suite currently has compilation errors due to deprecated functions in CuTest framework.

### File Organization

Source files organized in modular Makefiles:
- `Makefile.sources.mk`: Main source files by component
- `Makefile.lib.mk`: Library source files
- `Makefile.tests.mk`: Test source files
- `Makefile.headers.mk`: Header dependencies

### Grammar Reference

See `docs/grammar.bnf` for the formal grammar specification (simplified POSIX shell subset)

Current implementation: commands and command separators (`;`)

Planned: pipelines (`|`), redirections (`<`, `>`, `>>`)
