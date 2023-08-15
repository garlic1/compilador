%{
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
void yyerror (char const *s);
int get_line_number();
extern void *arvore;

%}

%code requires { #include "ast.h" }

%union {
    data *valor_lexico;
    asd_tree *arvore;
}

%type<arvore> program
%type<arvore> ldecl
%type<arvore> listID
%type<arvore> fun
%type<arvore> paramFun
%type<arvore> listParamFun
%type<arvore> bloco
%type<arvore> escopo
%type<arvore> lcmd
%type<arvore> cmd
%type<arvore> listID_ATTR
%type<arvore> expr
%type<arvore> value
%type<arvore> paramFunBloco
%type<arvore> listExpr
%type<arvore> cmd_fluxo


%type<valor_lexico> literal


%token<valor_lexico> TK_PR_INT
%token<valor_lexico> TK_PR_FLOAT
%token<valor_lexico> TK_PR_BOOL
%token<valor_lexico> TK_PR_IF
%token<valor_lexico> TK_PR_ELSE
%token<valor_lexico> TK_PR_WHILE
%token<valor_lexico> TK_PR_RETURN

%token<valor_lexico> TK_OC_LE
%token<valor_lexico> TK_OC_GE
%token<valor_lexico> TK_OC_EQ
%token<valor_lexico> TK_OC_NE
%token<valor_lexico> TK_OC_AND
%token<valor_lexico> TK_OC_OR
%token<valor_lexico> TK_OC_MAP

%token<valor_lexico> TK_IDENTIFICADOR
%token<valor_lexico> TK_LIT_INT
%token<valor_lexico> TK_LIT_FLOAT
%token<valor_lexico> TK_LIT_FALSE
%token<valor_lexico> TK_LIT_TRUE

%token<valor_lexico> '='
%token<valor_lexico> '-'
%token<valor_lexico> '!'
%token<valor_lexico> '*'
%token<valor_lexico> '/'
%token<valor_lexico> '%'
%token<valor_lexico> '+'
%token<valor_lexico> '<'
%token<valor_lexico> '>'


%token TK_ERRO

%start program

%%

// um programa é composto por variaveis globais e funçoes, ambos podendo ser vazios
program: ldecl          { arvore = $$;}
        |               { arvore = NULL;};

ldecl: global_var ldecl { $$ = $2; }
     | fun ldecl        { $$ = $1; asd_add_child($$, $2); }
     | global_var       { $$ = NULL; }
     | fun              { $$ = $1; };

tipo: TK_PR_INT
    | TK_PR_FLOAT
    | TK_PR_BOOL;

literal: TK_LIT_TRUE    { $$ = $1; }
        |TK_LIT_FALSE   { $$ = $1; }
        |TK_LIT_INT     { $$ = $1; }
        |TK_LIT_FLOAT   { $$ = $1; };

global_var: tipo listID ';' ;

listID: TK_IDENTIFICADOR ',' listID
        | TK_IDENTIFICADOR;

fun: TK_IDENTIFICADOR '(' paramFun ')' TK_OC_MAP tipo bloco { $$ = asd_new($1); /*asd_add_child($$, $3);*/ asd_add_child($$, $7); };

paramFun: listParamFun { $$ = $1; }
        | { $$ = NULL; };

listParamFun: tipo TK_IDENTIFICADOR ',' listParamFun { $$ = asd_new($2); asd_add_child($$, $4); }
            | tipo TK_IDENTIFICADOR { $$ = asd_new($2); };

bloco: '{' lcmd '}' { $$ = $2; };

escopo: bloco ';' { $$ = $1; };

lcmd: cmd ';' lcmd          { if($1 == NULL){$$ = $3;}else{$$ = $1; asd_add_child_end($$, $3);}}
    | cmd_fluxo lcmd        { $$ =  $1; asd_add_child_end($$, $2);}
    | cmd_fluxo ';' lcmd    { $$ =  $1; asd_add_child_end($$, $3);}
    | escopo lcmd           { $$ =  $1; asd_add_child_end($$, $2);}
    | {$$ = NULL;};

cmd: tipo listID_ATTR { $$ = $2;}
    | TK_IDENTIFICADOR '=' expr { $$ = asd_new($2); asd_add_child($$, asd_new($1)); asd_add_child($$, $3);}
    | TK_IDENTIFICADOR '(' paramFunBloco ')' { $$ =  asd_new_call($1); asd_add_child($$, $3);}
    | TK_PR_RETURN expr  { $$ = asd_new($1); asd_add_child($$, $2);}; 

cmd_fluxo: TK_PR_IF '(' expr ')' bloco                      { $$ = asd_new($1); asd_add_child($$, $3); asd_add_child($$, $5); }
         | TK_PR_IF '(' expr ')' bloco TK_PR_ELSE bloco     { $$ = asd_new($1); asd_add_child($$, $3); asd_add_child($$, $5); asd_tree *son = asd_new($6); asd_add_child($$, son); asd_add_child(son, $7);}
         | TK_PR_WHILE '(' expr ')' bloco                   { $$ = asd_new($1); asd_add_child($$, $3); asd_add_child($$, $5);};

listID_ATTR: TK_IDENTIFICADOR TK_OC_LE literal ',' listID_ATTR { $$ = asd_new($2); asd_add_child($$, asd_new($1)); asd_add_child($$, asd_new($3)); asd_add_child($$, $5); }
           |TK_IDENTIFICADOR TK_OC_LE literal                  { $$ = asd_new($2); asd_add_child($$, asd_new($1)); asd_add_child($$, asd_new($3)); }
           |TK_IDENTIFICADOR ',' listID_ATTR                   { $$ = $3; }
           |TK_IDENTIFICADOR                                   { $$ = NULL; };

paramFunBloco: listExpr { $$ = $1; }
             | { $$ = NULL; };

listExpr: expr ',' listExpr { $$ = $1; asd_add_child($$, $3); }
        | expr { $$ = $1; };

expr: '(' expr ')'              { $$ = $2; }
    | '-' expr                  { $$ = asd_new($1); asd_add_child($$, $2); }
    | '!' expr                  { $$ = asd_new($1); asd_add_child($$, $2); }
    | value '*' expr            { $$ = asd_new($2); asd_add_child($$, $1); asd_add_child($$, $3); }
    | value '/' expr            { $$ = asd_new($2); asd_add_child($$, $1); asd_add_child($$, $3); }
    | value '%' expr            { $$ = asd_new($2); asd_add_child($$, $1); asd_add_child($$, $3); }
    | value '+' expr            { $$ = asd_new($2); asd_add_child($$, $1); asd_add_child($$, $3); }
    | value '-' expr            { $$ = asd_new($2); asd_add_child($$, $1); asd_add_child($$, $3); }
    | value '<' expr            { $$ = asd_new($2); asd_add_child($$, $1); asd_add_child($$, $3); }
    | value '>' expr            { $$ = asd_new($2); asd_add_child($$, $1); asd_add_child($$, $3); }
    | value TK_OC_LE expr       { $$ = asd_new($2); asd_add_child($$, $1); asd_add_child($$, $3); }
    | value TK_OC_GE expr       { $$ = asd_new($2); asd_add_child($$, $1); asd_add_child($$, $3); }
    | value TK_OC_EQ expr       { $$ = asd_new($2); asd_add_child($$, $1); asd_add_child($$, $3); }
    | value TK_OC_NE expr       { $$ = asd_new($2); asd_add_child($$, $1); asd_add_child($$, $3); }
    | value TK_OC_AND expr      { $$ = asd_new($2); asd_add_child($$, $1); asd_add_child($$, $3); }
    | value TK_OC_OR expr       { $$ = asd_new($2); asd_add_child($$, $1); asd_add_child($$, $3); }
    | value                     { $$ =  $1;};       

value: TK_IDENTIFICADOR { $$ =  asd_new($1);}
    | TK_IDENTIFICADOR '(' paramFunBloco ')' { $$ =  asd_new_call($1); asd_add_child($$, $3);}
    | literal { $$ =  asd_new($1);};


%%

void yyerror(char const *s)
{
  arvore = NULL; 
  fprintf(stderr, "%s at line: %d\n",s, get_line_number());  
}