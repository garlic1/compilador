etapa4: parser.tab.o lex.yy.o main.o ast.o table.o stack.o semantics.o
	gcc -o etapa4 lex.yy.o parser.tab.o main.o ast.o -lfl

parser.tab.o lex.yy.o main.o ast.o table.o stack.o semantics.o: parser.tab.c lex.yy.c main.c ast.c table.c stack.c semantics.c
	gcc -c parser.tab.c lex.yy.c main.c ast.c table.c stack.c semantics.c

lex.yy.c: scanner.l
		  flex scanner.l

parser.tab.c: parser.y
	bison -d parser.y

clean:
	rm etapa4 parser.tab.c lex.yy.c parser.tab.h *.o

build: clean
		tar cvzf etapa4.tgz .