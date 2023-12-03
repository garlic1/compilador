%{
    #include "ast.h"
    #include "hash.h"

    int yylex(void);
    int yyerror();
    extern int getLineNumber();
%}

%union {
    hash_node *symbol;
    AST *ast;
}

%token<symbol> KW_CHAR
%token<symbol> KW_INT
%token<symbol> KW_FLOAT
%token KW_CODE

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

// %type<ast> program
// %type<ast> global_list
// %type<ast> functions_list
// %type<ast> vector_declaration
// %type<ast> vector_initial_values
// %type<ast> int_recursion
// %type<ast> char_recursion
// %type<ast> real_recursion
// %type<ast> function_prototype
// %type<ast> parameter_list
// %type<ast> parameter
// %type<ast> function
// %type<ast> command
// %type<ast> block
// %type<ast> commands_chain
// %type<ast> flow_control
// %type<ast> simple_command
// %type<ast> return_command
// %type<ast> print_command
// %type<ast> print_value
// %type<ast> attribution
%type<ast> expr
// %type<ast> expr_list

%left '+' '-'
%left '*' '/'
%left '|' '&'
%left '~'
%left '<' '>' OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_DIF 

%left "then"
%left KW_ELSE

%%

program: global_list functions_list
    ;

// GLOBAL VARIABLES

global_list: global global_list
    | function_prototype global_list
    |
    ;

global: type TK_IDENTIFIER '=' single_value ';'
    | vector_declaration
    ;

vector_declaration: type TK_IDENTIFIER '[' LIT_INT ']' ';'
    | type TK_IDENTIFIER '[' LIT_INT ']' '=' '[' vector_initial_values ']' ';'

vector_initial_values: LIT_INT int_recursion
    | LIT_CHAR char_recursion
    | LIT_REAL real_recursion
    | single_value
    ;

int_recursion: LIT_INT int_recursion
    | LIT_INT
    ;

char_recursion: LIT_CHAR char_recursion
    | LIT_CHAR
    ;

real_recursion: LIT_REAL real_recursion
    | LIT_REAL
    ;

// FUNCTION PROTOTYPES

function_prototype: type TK_IDENTIFIER '(' parameter_list ')' ';'
    ;

parameter_list: parameter ',' parameter_list
    | parameter
    |
    ;

parameter: type TK_IDENTIFIER
    ;

// FUNCTIONS

functions_list: function functions_list
    |
    ;

function: KW_CODE TK_IDENTIFIER command
    ;
   
command: flow_control
    | expr
    | simple_command
    | block
    |
    ;

block: '{' commands_chain '}'
    ;

commands_chain: command ';' commands_chain
    |
    ;

// FLOW CONTROL

flow_control: KW_IF '(' expr ')' command    %prec "then"
    | KW_IF '(' expr ')' command KW_ELSE command
    | KW_WHILE '(' expr ')' command
    ;

// SIMPLE COMMANDS

simple_command: attribution
    | print_command
    | return_command
    ;

return_command: KW_RETURN expr
    ;

print_command: KW_PRINT print_value
    ;

print_value: LIT_STRING
    | expr
    ;

attribution: TK_IDENTIFIER '=' expr
    | TK_IDENTIFIER '[' expr ']' '=' expr
    ;

// EXPRESSIONS

expr: TK_IDENTIFIER     
    | TK_IDENTIFIER '[' expr ']' 
    | single_value
    | '(' expr ')'
    | expr '+' expr { fprintf(stderr, "Recebi %s %s\n ", $1, $3); }
    | expr '-' expr 
    | expr '*' expr 
    | expr '/' expr 
    | expr '<' expr 
    | expr '>' expr 
    | expr OPERATOR_LE expr 
    | expr OPERATOR_GE expr 
    | expr OPERATOR_EQ expr 
    | expr OPERATOR_DIF expr 
    | expr '&' expr 
    | expr '|' expr 
    | '~' expr 
    | TK_IDENTIFIER '(' expr_list ')'
    | KW_INPUT
    ;

expr_list: expr ',' expr_list
    | expr
    ;

// TYPES AND LITS

type: KW_CHAR
    | KW_INT
    | KW_FLOAT
    ;

single_value: LIT_INT
    | LIT_CHAR
    | LIT_REAL
    ;

%%

int yyerror() {
    int line_number = getLineNumber();
    printf("Syntax error at line %d.\n", line_number);
    exit(3);
}