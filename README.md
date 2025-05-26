# C-Crafters: Mini C/C++ Compiler
## Overview
C-Crafters is a comprehensive mini compiler for a subset of C/C++ language, built using LEX (Lexical Analyzer) and YACC (Yet Another Compiler Compiler). This project demonstrates the fundamental phases of compilation including lexical analysis, syntax analysis, semantic analysis, intermediate code generation, code optimization, and assembly code generation.

## Features
- Lexical Analysis : Tokenizes source code into meaningful lexemes
- Syntax Analysis : Validates program structure using grammar rules
- Semantic Analysis : Builds and manages symbol tables
- Abstract Syntax Tree (AST) Generation : Creates hierarchical representation of program structure
- Intermediate Code Generation (ICG) : Produces three-address code
- Code Optimization : Implements constant folding and dead code elimination

### Supported C/C++ Features
- Data types: int, float, char, void
- Control structures: for loops, while loops, if-else conditionals
- Arithmetic and logical operations
- Variable declarations and assignments

## Project Structure
```
├── AST/                         # Abstract Syntax Tree generation
│   ├── ast.l                   # Lexical analyzer for AST
│   ├── ast.y                   # YACC grammar for AST generation
│   └── input.cpp               # Sample input file
├── CodeOpt/                    # Code optimization techniques
│   ├── main.py                 # Implements constant folding and dead code elimination
│   ├── input.txt               # Intermediate code input
│   └── output.txt              # Optimized code output
├── ICG/                        # Intermediate Code Generation
│   ├── Yacc.y                  # YACC grammar for ICG
│   ├── lex.l                   # Lexical analyzer for ICG
│   └── input.cpp               # Sample input file
├── LexicalAnalyser/            # Lexical analysis implementation
│   ├── lexicalanalyzer.cpp     # Tokenizes input source code
│   └── lexicalinput.txt        # Sample input file
├── SymbolTable/                # Symbol table implementation
│   ├── sym.l                   # Lexical analyzer for symbol table
│   ├── sym.y                   # YACC grammar for symbol table
│   └── input.cpp               # Sample input file
└── Assembly/                   # Assembly code generation and handling
    ├── main.py        # Python script to generate assembly code
    ├── input.txt               # Intermediate code input
    └── output.txt              # Generated assembly code output
```

## Compilation Phases
### 1. Lexical Analysis
The lexical analyzer breaks down source code into tokens such as keywords, identifiers, operators, and literals. It ignores whitespace and comments.

Example output:

```
Keywords: int, if, else, while, for
Identifiers: a, b, c, main
Math Operators: +, -, *, /, =
Logical Operators: <, >
Numerical Values: 1, 2, 3.14
Others: (, ), {, }, ;
```
### 2. Syntax Analysis
The parser validates the structure of the program according to the grammar rules of the language and builds a parse tree.

### 3. Semantic Analysis & Symbol Table
The compiler creates and maintains a symbol table to track variables, their types, scopes, and other attributes. This helps in type checking and scope resolution.

### 4. Abstract Syntax Tree (AST)
The AST provides a hierarchical representation of the program structure, making it easier to analyze and transform the code.

### 5. Intermediate Code Generation
The compiler generates three-address code as an intermediate representation, which is closer to machine code but still machine-independent.

Example output:

```
T0 = i + 1
i = T0
T1 = b < 7
if T1 goto L0
```
### 6. Code Optimization
The optimization phase improves the intermediate code by applying techniques such as:

- Constant Folding : Evaluates constant expressions at compile time
- Dead Code Elimination : Removes code that doesn't affect the program output

### 7. Code Generation
The final phase generates machine code from the optimized intermediate code.


## Installation & Usage
### Prerequisites
- GCC compiler
- Flex (Fast Lexical Analyzer)
- Bison (GNU Parser Generator, replacement for YACC)
- Python 3.x (for code optimization)

### Building the Compiler
1. Lexical Analyzer
```
cd LexicalAnalyser
g++ lexicalanalyzer.cpp -o lexical
./lexical
```
2. Symbol Table
```
cd SymbolTable
flex sym.l
bison -dy sym.y
gcc lex.yy.c y.tab.c -o symbol_table
./symbol_table input.cpp
```
3. Abstract Syntax Tree
```
cd AST
flex ast.l
bison -dy ast.y
gcc lex.yy.c y.tab.c -o ast
./ast input.cpp
```
4. Intermediate Code Generation
```
cd ICG
./run.sh
```
5. Code Optimization
```
cd CodeOpt
python3 main.py
```
## Example Workflow
1. Write a C/C++ program in input.cpp
2. Run the lexical analyzer to tokenize the code
3. Generate the symbol table to track variables and their properties
4. Create an abstract syntax tree to represent the program structure
5. Generate intermediate code
6. Apply optimizations to the intermediate code

## Limitations
- Supports only a subset of C/C++ language features
- Limited error handling and recovery
- No machine code generation (stops at optimized intermediate code)

## Future Enhancements
- Support for more C/C++ features (structs, classes, pointers)
- Enhanced error reporting and recovery
- More optimization techniques
- Backend for machine code generation

## Contributors
- Aryan Shorya
- Diya Gupta
- Naman Gupta
- Riya Vihan

## Acknowledgment
This project was developed as part of a compiler design course/project.