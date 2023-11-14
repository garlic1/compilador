%token KW_CHAR
%token KW_INT
%token KW_FLOAT
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

%token TK_IDENTIFIER

%token LIT_INT
%token LIT_REAL
%token LIT_CHAR
%token LIT_STRING

%left '+' '-'
%left '*' '/'
%left '|' '&'
%left '~'
%left '<' '>' OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_DIF 

%%

program: declaration_list;

declaration_list: global_variable declaration_list
    | function_prototype declaration_list
    | function_implementation declaration_list
    |
    ;

global_variable: type TK_IDENTIFIER '=' single_value ';'
    | vector_declaration
    ;

vector_declaration: type TK_IDENTIFIER '[' LIT_INT ']' ';'
    | type TK_IDENTIFIER '[' LIT_INT ']' '=' '[' vector_initial_values ']' ';'

vector_initial_values: LIT_INT int_recursion
    | LIT_CHAR char_recursion
    | LIT_REAL real_recursion
    | single_value
    ;

single_value: LIT_INT
    | LIT_CHAR
    | LIT_REAL
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

type: KW_CHAR
    | KW_INT
    | KW_FLOAT
    ;

function_prototype: type TK_IDENTIFIER '(' parameter_list ')' ';'
    ;

function_implementation: KW_CODE TK_IDENTIFIER block
    ;

parameter_list: parameter ',' parameter_list
    | parameter
    |
    ;

parameter: type TK_IDENTIFIER;

block: '{' commands_chain '}'
    ;

commands_chain: simple_command commands_chain
    | arithmetic_expression commands_chain
    | flux_control commands_chain
    ;

flux_control: KW_IF '(' expr ')' commands_chain
    | KW_IF '(' expr ')' commands_chain KW_ELSE commands_chain
    | KW_WHILE '(' expr ')' commands_chain
    ;

arithmetic_expression: expr ';'
    ;

simple_command: attribution ';'
    | print_command ';'
    | return_command ';'
    |
    ;

print_command: KW_PRINT print_value
    ;

print_value: LIT_STRING
    | expr
    ;


return_command: KW_RETURN expr
    ;

attribution: TK_IDENTIFIER '=' expr
    | TK_IDENTIFIER '[' expr ']' '=' expr
    ;

expr: TK_IDENTIFIER
    | TK_IDENTIFIER '[' expr ']'
    | single_value
    | '(' expr ')'
    | expr '+' expr 
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

%%

int yyerror() {
    int line_number = getLineNumber();
    printf("Syntax error at line %d.", line_number);
    exit(3);
}