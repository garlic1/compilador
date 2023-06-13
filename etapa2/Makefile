etapa2: parser.tab.o lex.yy.o
	gcc -o etapa2 lex.yy.o parser.tab.o -lfl

parser.tab.o lex.yy.o : parser.tab.c lex.yy.c
	gcc -c parser.tab.c lex.yy.c

lex.yy.c: scanner.l
		  flex scanner.l

parser.tab.c: parser.y
	bison -d parser.y

clean:
	rm etapa2 parser.tab.c lex.yy.c parser.tab.h *.o

build: clean
		tar cvzf etapa2.tgz .