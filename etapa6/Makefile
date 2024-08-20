#
# UFRGS - Compiladores B - Marcelo Johann - 2009/2 - Etapa 1
#
# Makefile for three compiler calls
# Read the comments on Makefile2. All of them apply here too.
# But now the hash table is compiled in a separate gcc call
# Therefore, there must be a header of it to be included in scanner.l
#

etapa5: main.o parser.tab.o lex.yy.o hash.o ast.o tacs.o
	gcc -o etapa5 main.o parser.tab.o lex.yy.o hash.o ast.o tacs.o

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
	flex --header-file=lex.yy.h scanner.l 

parser.tab.c: parser.y
	bison -d parser.y

clean:
	rm *.o lex.yy.c parser.tab.c parser.tab.h etapa5

remake: clean etapa5

build: clean
		tar cvzf etapa5.tgz .