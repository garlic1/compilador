%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
void yyerror (char const *s);
int get_line_number();

%}

%token TK_PR_INT
%token TK_PR_FLOAT
%token TK_PR_BOOL
%token TK_PR_IF
%token TK_PR_ELSE
%token TK_PR_WHILE
%token TK_PR_RETURN
%token TK_OC_LE
%token TK_OC_GE
%token TK_OC_EQ
%token TK_OC_NE
%token TK_OC_AND
%token TK_OC_OR
%token TK_OC_MAP
%token TK_IDENTIFICADOR
%token TK_LIT_INT
%token TK_LIT_FLOAT
%token TK_LIT_FALSE
%token TK_LIT_TRUE
%token TK_ERRO

%left TK_OC_OR
%left TK_OC_AND
%left TK_OC_EQ TK_OC_NE
%left '<' '>' TK_OC_LE TK_OC_GE
%left '+'
%left '*' '/' '%'
%left '-' '!'

%start program

%%

// um programa é composto por variaveis globais e funçoes, ambos podendo ser vazios
program: ldecl;        

ldecl: global_var ldecl
     | fun ldecl
     |;

type: TK_PR_INT
    | TK_PR_FLOAT
    | TK_PR_BOOL;

literal: TK_LIT_TRUE
        |TK_LIT_FALSE
        |TK_LIT_INT
        |TK_LIT_FLOAT;

global_var: type listID ';';

listID: TK_IDENTIFICADOR ',' listID
        | TK_IDENTIFICADOR;

fun: TK_IDENTIFICADOR '(' listParam ')' TK_OC_MAP type bloco;

listParam: type TK_IDENTIFICADOR ',' listParam
          | type TK_IDENTIFICADOR
          |;

bloco: '{' lcmd '}';

escopo: bloco ';';

lcmd: cmd ';' lcmd
    | cmd_fluxo lcmd
    | cmd_fluxo ';' lcmd
    | escopo lcmd
    |;

cmd: type listID_ATTR
    | TK_IDENTIFICADOR '=' expr
    | TK_IDENTIFICADOR '(' listExpr ')'
    | TK_PR_RETURN expr; 

cmd_fluxo: TK_PR_IF '(' expr ')' bloco
        | TK_PR_IF '(' expr ')' bloco TK_PR_ELSE bloco
        | TK_PR_WHILE '(' expr ')' bloco;

listID_ATTR: TK_IDENTIFICADOR TK_OC_LE literal ',' listID_ATTR
            |TK_IDENTIFICADOR TK_OC_LE literal
            |TK_IDENTIFICADOR ',' listID_ATTR
            |TK_IDENTIFICADOR;

listExpr: expr ',' listExpr
        | expr
        |;

expr: '(' expr ')'
    | '-' expr
    | '!' expr
    | expr '*' expr
    | expr '/' expr    
    | expr '%' expr
    | expr '+' expr
    | expr '-' expr
    | expr '<' expr
    | expr '>' expr
    | expr TK_OC_LE expr
    | expr TK_OC_GE expr
    | expr TK_OC_EQ expr
    | expr TK_OC_NE expr
    | expr TK_OC_AND expr
    | expr TK_OC_OR expr
    | TK_IDENTIFICADOR
    | TK_IDENTIFICADOR '(' listExpr ')'
    | literal;


%%

void yyerror(char const *s)
{
  fprintf(stderr, "%s at line: %d\n",s, get_line_number());  
}