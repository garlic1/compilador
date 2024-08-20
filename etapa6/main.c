#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "generateAsm.h"

extern FILE *yyin;
FILE *out;
extern int yyparse();
void initMe();
int getLineNumber();
int isRunning();
extern int yylex();
extern char* yytext;

int main (int argc, char **argv) {
    if (argc < 3) {
        printf("Usage: ./etapa6 source.txt out.txt\n");
        exit(1);
    }

    yyin = fopen(argv[1], "r");
    if (!yyin) {
        printf("Error while opening yyin file \n");
        exit(2);
    }

    out = fopen(argv[2], "w");
    if (!out) {
        printf("Error while opening out file \n");
        exit(3);
    }
    
    initMe();
    yyparse();
    print_table();

    exit(0);
}