# Compiler 
#### Stack: C, Flex, Bison, RegExp, x86 Assembly

A functioning compiler. 

Takes an entry from a hypothetical programming language, similar to C, and compiles it to AT&T assembly for Linux machines.

## How to run

- Make sure you are in a Linux environment.
- Choose an implementation step (called "etapa" in portuguese) and navigate to the folder.
- Test files are provided inside each folder.
- Run the Makefile

### Usage:
- etapa1: ./etapa1 test.txt
- etapa2: ./etapa2 test.txt
- etapa3: ./etapa3 source.txt out.txt
- etapa5: ./etapa5 source.txt out.txt
- etapa6: ./etapa6 source.txt out.txt

## Details:

### Etapa 1:
In the first step of the compiler implementation, we run a lexical analysis through the file and throw an error if there are any lex errors. We also initialize variables in a global Hash table, implemented from scratch in C.

This step was coded using the [Flex lexical analyser](https://en.wikipedia.org/wiki/Flex_(lexical_analyser_generator)) using Regex syntax.

### Etapa 2:
The second step of implementing the compiler is running a syntactic analysis (parsing).

This step was coded using the [GNU Bison](https://www.gnu.org/software/bison/manual/bison.html) parser generator.

### Etapa 3:
After running the syntactic analysis, we build the Abstract Syntax Tree (AST), which determines the order of the operations.

With the AST correctly built, we can rebuild the entry code by decompiling the tree.

### Etapa 4 (optional, not implemented):
This would be the semantic verification step, which would imply testing the functioning of the syntactic structures found in the AST.

### Etapa 5:
This step translates the AST structure into readable, intermediate code, called "TACs". Each TAC more or less represents a Assembly instruction.

### Etapa 6:
This is the final step of compiling the code. It consists of translating each TAC to an Assembly instruction, as well as memory and pointer management. 

The program takes the entry code and outputs a `out.s` file with the corresponding Assembly instructions. Only a few instructions were implemented in this step.

### Etapa 7 (optional, not implemented):
This step would consist on [compile-time optimizations](https://en.wikipedia.org/wiki/Optimizing_compiler) and error recovery.
