etapa1: lex.yy.c
		gcc -o etapa1 main.c lex.yy.c

lex.yy.c: scanner.l
		  flex scanner.l

clean:
		rm lex.yy.c etapa1

build: clean
		tar cvzf etapa1.tgz .