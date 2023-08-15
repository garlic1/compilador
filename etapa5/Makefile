etapa5: parser.tab.o lex.yy.o main.o ast.o
	gcc -o etapa5 lex.yy.o parser.tab.o main.o ast.o -lfl

parser.tab.o lex.yy.o main.o ast.o : parser.tab.c lex.yy.c main.c ast.c
	gcc -c parser.tab.c lex.yy.c main.c ast.c

lex.yy.c: scanner.l
		  flex scanner.l

parser.tab.c: parser.y
	bison -d parser.y

clean:
	rm etapa5 parser.tab.c lex.yy.c parser.tab.h *.o

build: clean
		tar cvzf etapa5.tgz .