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

fun: TK_IDENTIFICADOR '(' paramFun ')' TK_OC_MAP type bloco;

paramFun: listParamFun
        |;

listParamFun: type TK_IDENTIFICADOR ',' listParamFun
            | type TK_IDENTIFICADOR;

bloco: '{' lcmd '}';

escopo: bloco ';';

lcmd: cmd ';' lcmd
    | cmd_fluxo lcmd
    | cmd_fluxo ';' lcmd
    | escopo lcmd
    |;

cmd: type listID_ATTR
    | TK_IDENTIFICADOR '=' expr
    | TK_IDENTIFICADOR '(' paramFunBloco ')'
    | TK_PR_RETURN expr; 

cmd_fluxo: TK_PR_IF '(' expr ')' bloco
         | TK_PR_IF '(' expr ')' bloco TK_PR_ELSE bloco
         | TK_PR_WHILE '(' expr ')' bloco;

listID_ATTR: TK_IDENTIFICADOR TK_OC_LE literal ',' listID_ATTR
           |TK_IDENTIFICADOR TK_OC_LE literal
           |TK_IDENTIFICADOR ',' listID_ATTR
           |TK_IDENTIFICADOR;

paramFunBloco: listExpr
             |;

listExpr: expr ',' listExpr
        | expr;

expr: '(' expr ')'
    | '-' expr
    | '!' expr
    | value '*' expr
    | value '/' expr    
    | value '%' expr
    | value '+' expr
    | value '-' expr
    | value '<' expr
    | value '>' expr
    | value TK_OC_LE expr
    | value TK_OC_GE expr
    | value TK_OC_EQ expr
    | value TK_OC_NE expr
    | value TK_OC_AND expr
    | value TK_OC_OR expr
    | value;
    

value: TK_IDENTIFICADOR
    | TK_IDENTIFICADOR '(' paramFunBloco ')'
    | literal;


%%

void yyerror(char const *s)
{
  fprintf(stderr, "%s at line: %d\n",s, get_line_number());  
}