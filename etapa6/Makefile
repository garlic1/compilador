#
# UFRGS - Compiladores B - Marcelo Johann - 2009/2 - Etapa 1
#
# Makefile for single compiler call
# All source files must be included from code embedded in scanner.l
# In our case, you probably need #include "hash.c" at the beginning
# and #include "main.c" in the last part of the scanner.l
#

etapa6: main.o parser.tab.o lex.yy.o hash.o ast.o tacs.o generateAsm.o
	gcc -o etapa6 main.o lex.yy.o parser.tab.o hash.o ast.o tacs.o generateAsm.o

main.o: main.c
	gcc -c main.c

hash.o: hash.c
	gcc -c hash.c

ast.o: ast.c
	gcc -c ast.c

tacs.o: tacs.c
	gcc -c tacs.c

generateAsm.o: generateAsm.c
	gcc -c generateAsm.c

parser.tab.o lex.yy.o : parser.tab.c lex.yy.c
	gcc -c parser.tab.c lex.yy.c

lex.yy.c: scanner.l
		  flex scanner.l

parser.tab.c: parser.y
	bison -d parser.y

clean:
	rm lex.yy.c etapa6 parser.tab.c parser.tab.h *.o

remake: clean etapa6

build: clean
		tar cvzf etapa6.tgz .
