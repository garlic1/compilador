#
# UFRGS - Compiladores B - Marcelo Johann - 2009/2 - Etapa 1
#
# Makefile for single compiler call
# All source files must be included from code embedded in scanner.l
# In our case, you probably need #include "hash.c" at the beginning
# and #include "main.c" in the last part of the scanner.l
#

etapa5: main.o parser.tab.o lex.yy.o hash.o ast.o tacs.o
	gcc -o etapa5 main.o lex.yy.o parser.tab.o hash.o ast.o tacs.o

main.o: main.c
	gcc -c main.c

hash.o: hash.c
	gcc -c hash.c

ast.o: ast.c
	gcc -c ast.c

tacs.o: tacs.c
	gcc -c tacs.c

parser.tab.o lex.yy.o : parser.tab.c lex.yy.c
	gcc -c parser.tab.c lex.yy.c

lex.yy.c: scanner.l
		  flex scanner.l

parser.tab.c: parser.y
	bison -d parser.y

clean:
	rm lex.yy.c etapa5 parser.tab.c parser.tab.h *.o

remake: clean etapa5

build: clean
		tar cvzf etapa5.tgz .
