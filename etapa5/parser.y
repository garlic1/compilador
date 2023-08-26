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
    ast_tree *arvore;
}

%type<arvore> program
%type<arvore> ldecl
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

%type<valor_lexico> bin_operator
%type<valor_lexico> un_operator

%token TK_ERRO

%start program

%%

// um programa é composto por variaveis globais e funçoes, ambos podendo ser vazios
program: ldecl                                                      { arvore = $$;}
        |                                                           { arvore = NULL;};

ldecl: global_var ldecl                                             { $$ = $2; }
     | fun ldecl                                                    { $$ = $1; ast_add_child($$, $2); }
     | global_var                                                   { $$ = NULL; }
     | fun                                                          { $$ = $1; };

tipo: TK_PR_INT
    | TK_PR_FLOAT
    | TK_PR_BOOL;

literal: TK_LIT_TRUE                                                { $$ = $1; }
        |TK_LIT_FALSE                                               { $$ = $1; }
        |TK_LIT_INT                                                 { $$ = $1; }
        |TK_LIT_FLOAT                                               { $$ = $1; };

global_var: tipo listID ';' ;

listID: TK_IDENTIFICADOR ',' listID
        | TK_IDENTIFICADOR;

fun: TK_IDENTIFICADOR '(' paramFun ')' TK_OC_MAP tipo bloco         { $$ = ast_new($1); /*ast_add_child($$, $3);*/ ast_add_child($$, $7); };

paramFun: listParamFun                                              { $$ = $1; }
        |                                                           { $$ = NULL; };

listParamFun: tipo TK_IDENTIFICADOR ',' listParamFun                { $$ = ast_new($2); ast_add_child($$, $4); }
            | tipo TK_IDENTIFICADOR                                 { $$ = ast_new($2); };

bloco: '{' lcmd '}'                                                 { $$ = $2; };

escopo: bloco ';'                                                   { $$ = $1; };

lcmd: cmd ';' lcmd                                                  { if($1 == NULL){$$ = $3;}else{$$ = $1; ast_add_child_end($$, $3);}}
    | cmd_fluxo lcmd                                                { $$ =  $1; ast_add_child_end($$, $2);}
    | cmd_fluxo ';' lcmd                                            { $$ =  $1; ast_add_child_end($$, $3);}
    | escopo lcmd                                                   { if($1 == NULL){$$ = $2;}else{$$ = $1; ast_add_child_end($$, $2);}}
    |                                                               {$$ = NULL;};

cmd: tipo listID_ATTR                                               { $$ = $2;}
    | TK_IDENTIFICADOR '=' expr                                     { $$ = ast_new($2); ast_add_child($$, ast_new($1)); ast_add_child($$, ast_adjust_expr($3));}
    | TK_IDENTIFICADOR '(' paramFunBloco ')'                        { $$ =  ast_new_call($1); ast_add_child($$, $3);}
    | TK_PR_RETURN expr                                             { $$ = ast_new($1); ast_add_child($$, ast_adjust_expr($2));}; 

cmd_fluxo: TK_PR_IF '(' expr ')' bloco                              { $$ = ast_new($1); ast_add_child($$, ast_adjust_expr($3)); ast_add_child($$, $5); }
         | TK_PR_IF '(' expr ')' bloco TK_PR_ELSE bloco             { $$ = ast_new($1); ast_add_child($$, ast_adjust_expr($3)); ast_add_child($$, $5); ast_add_child($$, $7); } //ast_tree *son = ast_new($6); ast_add_child($$, son); ast_add_child(son, $7);}
         | TK_PR_WHILE '(' expr ')' bloco                           { $$ = ast_new($1); ast_add_child($$, ast_adjust_expr($3)); ast_add_child($$, $5);};

listID_ATTR: TK_IDENTIFICADOR TK_OC_LE literal ',' listID_ATTR      { $$ = ast_new($2); ast_add_child($$, ast_new($1)); ast_add_child($$, ast_new($3)); ast_add_child($$, $5); }
           |TK_IDENTIFICADOR TK_OC_LE literal                       { $$ = ast_new($2); ast_add_child($$, ast_new($1)); ast_add_child($$, ast_new($3)); }
           |TK_IDENTIFICADOR ',' listID_ATTR                        { $$ = $3; }
           |TK_IDENTIFICADOR                                        { $$ = NULL; };

paramFunBloco: listExpr                                             { $$ = $1; }
             |                                                      { $$ = NULL; };

listExpr: expr ',' listExpr                                         { $$ = ast_adjust_expr($1); ast_add_child_first($$, $3); }
        | expr                                                      { $$ = ast_adjust_expr($1); };

expr: un_operator expr                                              { $$ = ast_new($1); ast_add_child($$, $2); }    
    | value bin_operator expr                                       { $$ = ast_new($2); ast_add_child($$, $1); ast_add_child($$, $3); }    
    | value                                                         { $$ =  $1;};

bin_operator: '*'                                                   { $$ = $1; $1->precedencia = (int*)malloc(sizeof(int)); *($1->precedencia) = 2; }   //'*' 
            | '/'                                                   { $$ = $1; $1->precedencia = (int*)malloc(sizeof(int)); *($1->precedencia) = 2; }   //'/'
            | '%'                                                   { $$ = $1; $1->precedencia = (int*)malloc(sizeof(int)); *($1->precedencia) = 2; }   //'%'
            | '+'                                                   { $$ = $1; $1->precedencia = (int*)malloc(sizeof(int)); *($1->precedencia) = 3; }   //'+'
            | '-'                                                   { $$ = $1; $1->precedencia = (int*)malloc(sizeof(int)); *($1->precedencia) = 3; }   //'-'
            | '<'                                                   { $$ = $1; $1->precedencia = (int*)malloc(sizeof(int)); *($1->precedencia) = 4; }   //'<'
            | '>'                                                   { $$ = $1; $1->precedencia = (int*)malloc(sizeof(int)); *($1->precedencia) = 4; }   //'>'
            | TK_OC_LE                                              { $$ = $1; $1->precedencia = (int*)malloc(sizeof(int)); *($1->precedencia) = 4; }   //TK_OC_LE
            | TK_OC_GE                                              { $$ = $1; $1->precedencia = (int*)malloc(sizeof(int)); *($1->precedencia) = 4; }   //TK_OC_GE
            | TK_OC_EQ                                              { $$ = $1; $1->precedencia = (int*)malloc(sizeof(int)); *($1->precedencia) = 5; }   //TK_OC_EQ
            | TK_OC_NE                                              { $$ = $1; $1->precedencia = (int*)malloc(sizeof(int)); *($1->precedencia) = 5; }   //TK_OC_NE
            | TK_OC_AND                                             { $$ = $1; $1->precedencia = (int*)malloc(sizeof(int)); *($1->precedencia) = 6; }   //TK_OC_AND
            | TK_OC_OR                                              { $$ = $1; $1->precedencia = (int*)malloc(sizeof(int)); *($1->precedencia) = 7; };  //TK_OC_OR  


un_operator: '-'                                                    { $$ = $1; $1->precedencia = (int*)malloc(sizeof(int)); *($1->precedencia) = 1; }  //'-'
            | '!'                                                   { $$ = $1; $1->precedencia = (int*)malloc(sizeof(int)); *($1->precedencia) = 1; }; //'!'


value: TK_IDENTIFICADOR                                             { $$ = ast_new($1);}
    | TK_IDENTIFICADOR '(' paramFunBloco ')'                        { $$ =  ast_new_call($1); ast_add_child($$, $3);}
    | literal                                                       { $$ =  ast_new($1);}
    | '(' expr ')'                                                  { $$ = ast_new_parenteses(); ast_add_child($$,$2); };


%%

void yyerror(char const *s)
{
  arvore = NULL; 
  fprintf(stderr, "%s at line: %d\n",s, get_line_number());  
}