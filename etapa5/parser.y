%{
    #include "ast.h"
    #include "hash.h"
    #include "tacs.h"

    int yylex(void);
    int yyerror();
    extern int getLineNumber();

    AST *ast_root = NULL;
%}

%union {
    hash_node *symbol;
    AST *ast;
}

%token<symbol> KW_CHAR
%token<symbol> KW_INT
%token<symbol> KW_FLOAT
%token<symbol> KW_CODE

%token KW_IF
%token KW_ELSE
%token KW_WHILE
%token KW_INPUT
%token KW_PRINT
%token KW_RETURN

%token OPERATOR_LE
%token OPERATOR_GE
%token OPERATOR_EQ
%token OPERATOR_DIF

%token<symbol> TK_IDENTIFIER

%token<symbol> LIT_INT
%token<symbol> LIT_REAL
%token<symbol> LIT_CHAR
%token<symbol> LIT_STRING

%token TOKEN_ERROR

%type<ast> global_list
%type<ast> global
%type<ast> functions_list
%type<ast> vector_declaration
%type<ast> vector_initial_values
%type<ast> function_prototype
%type<ast> parameter_list
%type<ast> parameter
%type<ast> function
%type<ast> command
%type<ast> block
%type<ast> commands_chain
%type<ast> flow_control
%type<ast> return_command
%type<ast> print_command
%type<ast> print_value
%type<ast> attribution
%type<ast> simple_command
%type<ast> expr
%type<ast> expr_list
%type<ast> type
%type<ast> single_value

%left '+' '-'
%left '*' '/'
%left '|' '&'
%left '~'
%left '<' '>' OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_DIF 

%left "then"
%left KW_ELSE

%%

program: global_list functions_list {ast_print($1, 0);ast_print($2, 0);ast_decomp($1);ast_decomp($2);}
    ;

// GLOBAL VARIABLES

global_list: global global_list         {$$ = ast_create(AST_GLOBAL_LIST, 0, $1, $2, 0, 0);}
    | function_prototype global_list    {$$ = ast_create(AST_GLOBAL_LIST, 0, $1, $2, 0, 0);}
    |   {$$ = 0;}
    ;

global: type TK_IDENTIFIER '=' single_value ';'  {$$ = ast_create(AST_GLOBAL_VARIABLE, $2, $1, $4, 0, 0); tac_print(tac_create(TAC_GLOBAL_VARIABLE,$2,0,0));}
    | vector_declaration                         
    ;

vector_declaration: type TK_IDENTIFIER '[' LIT_INT ']' vector_initial_values ';' {
        AST* lit_node = ast_create(AST_SYMBOL, $4, 0, 0, 0, 0);

        $$ = ast_create(
            AST_VECTOR_DECLARATION,
            $2,
            $1,
            lit_node,
            $6,
            0
        );
    }

vector_initial_values: single_value vector_initial_values {
        $$ = ast_create(AST_VECTOR_INTIIAL_VALUES, 0, $1, $2, 0, 0);
    }
    | { $$ = 0; }
    ;

// FUNCTION PROTOTYPES

function_prototype: type TK_IDENTIFIER '(' parameter_list ')' ';'   { $$ = ast_create(AST_FUNCTION_PROTOTYPE, $2, $1, $4, 0, 0); }
    ;

parameter_list: parameter ',' parameter_list    { $$ = ast_create(AST_PARAMETER_LIST, 0, $1, $3, 0, 0); }
    | parameter { $$ = ast_create(AST_PARAMETER_LIST, 0, $1, 0, 0, 0); }
    | { $$=0; }
    ;

parameter: type TK_IDENTIFIER   { $$ = ast_create(AST_PARAMETER, $2, $1, 0, 0, 0); }
    ;

// FUNCTIONS

functions_list: function functions_list { $$ = ast_create(AST_FUNCTION_LIST, 0, $1, $2, 0, 0); }
    |   { $$ = 0; }
    ;

function: KW_CODE TK_IDENTIFIER command { $$ = ast_create(AST_FUNCTION, $2, $3, 0, 0, 0); }
    ;
   
command: flow_control 
    | expr ';'
    | simple_command ';'
    | block
    ;

block: '{' commands_chain '}' { $$ = ast_create(AST_BLOCK, 0, $2, 0, 0, 0); }
    ;

commands_chain: command commands_chain { $$ = ast_create(AST_COMMANDS_CHAIN, 0, $1, $2, 0, 0); }
    |   { $$ = 0; }
    ;

// FLOW CONTROL

flow_control: KW_IF '(' expr ')' command ';'   %prec "then" { $$ = ast_create(AST_IF, 0, $3, $5, 0, 0); }
    | KW_IF '(' expr ')' command KW_ELSE command { $$ = ast_create(AST_IF_ELSE, 0, $3, $5, $7, 0); }
    | KW_WHILE '(' expr ')' command { $$ = ast_create(AST_WHILE, 0, $3, $5, 0, 0); }
    ;

// SIMPLE COMMANDS

simple_command: attribution { $$=$1; }
    | print_command { $$=$1; }
    | return_command { $$=$1; }
    ;

// revisar return
return_command: KW_RETURN expr { $$ = ast_create(AST_RETURN, 0, $2, 0, 0, 0); }
    ;

print_command: KW_PRINT print_value { $$ = ast_create(AST_PRINT, 0, $2, 0, 0, 0); }
    ;

print_value: LIT_STRING { $$ = ast_create(AST_PRINT_VALUE, $1, 0, 0, 0, 0); }  
    | expr              { $$ = ast_create(AST_PRINT_VALUE, 0, $1, 0, 0, 0); }
    ;

attribution: TK_IDENTIFIER '=' expr { $$ = ast_create(AST_ATTR, $1, $3, 0, 0, 0); }
    | TK_IDENTIFIER '[' expr ']' '=' expr { $$ = ast_create(AST_ATTR_VECTOR, $1, $3, $6, 0, 0); }
    ;

// EXPRESSIONS

expr: TK_IDENTIFIER {$$ = ast_create(AST_SYMBOL, $1, 0, 0, 0, 0); tac_print(tac_create(TAC_SYMBOL,$1,0,0));} 
    | TK_IDENTIFIER '[' expr ']'  {$$ = ast_create(AST_ACCESS_VECTOR, $1, $3, 0, 0, 0);}
    | single_value {$$ = $1;}
    | '(' expr ')' {$$ = $2;}
    | expr '+' expr {$$ = ast_create(AST_SUM, 0, $1, $3, 0, 0);}
    | expr '-' expr  {$$ = ast_create(AST_SUB, 0, $1, $3, 0, 0);}
    | expr '*' expr  {$$ = ast_create(AST_MUL, 0, $1, $3, 0, 0);}
    | expr '/' expr {$$ = ast_create(AST_DIV, 0, $1, $3, 0, 0);}
    | expr '<' expr {$$ = ast_create(AST_LT, 0, $1, $3, 0, 0);}
    | expr '>' expr {$$ = ast_create(AST_GT, 0, $1, $3, 0, 0);}
    | expr OPERATOR_LE expr {$$ = ast_create(AST_LE, 0, $1, $3, 0, 0);}
    | expr OPERATOR_GE expr {$$ = ast_create(AST_GE, 0, $1, $3, 0, 0);}
    | expr OPERATOR_EQ expr {$$ = ast_create(AST_EQ, 0, $1, $3, 0, 0);}
    | expr OPERATOR_DIF expr {$$ = ast_create(AST_DIF, 0, $1, $3, 0, 0);}
    | expr '&' expr {$$ = ast_create(AST_AND, 0, $1, $3, 0, 0);}
    | expr '|' expr {$$ = ast_create(AST_OR, 0, $1, $3, 0, 0);}
    | '~' expr {$$ = ast_create(AST_NOT, 0, $2, 0, 0, 0);}
    | TK_IDENTIFIER '(' expr_list ')' {$$ = ast_create(AST_ACCESS_FUNCTION, $1, $3, 0, 0, 0);}
    | KW_INPUT '(' type ')' {$$ = ast_create(AST_INPUT, 0, $3, 0, 0, 0);}
    ;

expr_list: expr ',' expr_list   { $$ = ast_create(AST_EXPR_LIST, 0, $1, $3, 0, 0); }
    | expr { $$ = ast_create(AST_EXPR_LIST, 0, $1, 0, 0, 0); }
    ;

// TYPES AND LITS

type: KW_INT   {$$ = ast_create(AST_INT, 0, 0, 0, 0, 0);}
    | KW_CHAR  {$$ = ast_create(AST_CHAR, 0, 0, 0, 0, 0);}
    | KW_FLOAT {$$ = ast_create(AST_FLOAT, 0, 0, 0, 0, 0);}
    ;

single_value: LIT_INT {$$ = ast_create(AST_SYMBOL, $1, 0, 0, 0, 0); }
    | LIT_CHAR {$$ = ast_create(AST_SYMBOL, $1, 0, 0, 0, 0);}
    | LIT_REAL {$$ = ast_create(AST_SYMBOL, $1, 0, 0, 0, 0);}
    ;

%%

int yyerror() {
    int line_number = getLineNumber();
    printf("Syntax error at line %d.\n", line_number);
    exit(3);
}