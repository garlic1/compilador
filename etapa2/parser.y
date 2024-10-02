%{
    #include "hash.h"

    int yylex(void);
    int yyerror();
    extern int getLineNumber();
%}


%token KW_CHAR
%token KW_INT
%token KW_FLOAT
%token KW_BOOL

%token KW_IF
%token KW_ELSE
%token KW_WHILE
%token KW_READ
%token KW_PRINT
%token KW_RETURN

%token OPERATOR_LE
%token OPERATOR_GE
%token OPERATOR_EQ
%token OPERATOR_DIF

%token TK_IDENTIFIER

%token LIT_INT
%token LIT_CHAR
%token LIT_REAL
%token LIT_FALSE
%token LIT_TRUE
%token LIT_STRING

%token TOKEN_ERROR

%left '+' '-'
%left '*' '/'
%left '|' '&'
%left '~'
%left '<' '>' OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_DIF 

%left "then"
%left KW_ELSE

%%

    program: global_declaration_list
        ;

    global_declaration_list: global_declaration global_declaration_list
        |
        ;
    
    global_declaration: variable_declaration
        | function_declaration
        | array_declaration
        ;

    function_declaration: type TK_IDENTIFIER '(' function_parameters ')' block
        ;
    
    function_parameters: type TK_IDENTIFIER ',' function_parameters
        | type TK_IDENTIFIER
        |
        ;

    variable_declaration: type TK_IDENTIFIER ':' literal ';'
        ;
    
    array_declaration: type TK_IDENTIFIER '[' LIT_INT ']' ';'
        | type TK_IDENTIFIER '[' LIT_INT ']' ':' array_initial_values ';'
        ;
    
    array_initial_values: literal array_initial_values
        | literal
        ;

    command: flow_control 
        | expression ';'
        | simple_command ';'
        | block
        ;

    simple_command: KW_PRINT type expression                // print expression
        | KW_PRINT LIT_STRING                               // print string
        | KW_READ type TK_IDENTIFIER                        // read
        | KW_RETURN expression                              // return
        | TK_IDENTIFIER '=' expression                      // variable attribution
        | TK_IDENTIFIER '[' expression ']' '=' expression   // array attribution
        |                                                   // empty command
        ;
    
    block: '{' commands_list '}'
        ;
    
    commands_list: command commands_list
        |
        ;
    
    expression: TK_IDENTIFIER
        | TK_IDENTIFIER '[' expression ']'
        | literal
        | '(' expression ')'
        | expression '+' expression
        | expression '-' expression
        | expression '*' expression
        | expression '/' expression
        | expression '<' expression
        | expression '>' expression
        | expression OPERATOR_LE expression
        | expression OPERATOR_GE expression
        | expression OPERATOR_EQ expression
        | expression OPERATOR_DIF expression
        | expression '&' expression
        | expression '|' expression
        | '~' expression
        | TK_IDENTIFIER '(' arguments_list ')'
        ;
    
    arguments_list: expression ',' arguments_list
        | expression
        |
        ;

    flow_control: KW_IF '(' expression ')' command %prec "then"
        | KW_IF '(' expression ')' command KW_ELSE command
        | KW_WHILE '(' expression ')' command
        ;

    type: KW_CHAR
        | KW_BOOL
        | KW_FLOAT
        | KW_INT
        ;
    
    literal: LIT_FALSE
        | LIT_TRUE
        | LIT_INT
        | LIT_REAL
        | LIT_CHAR
        ;


%%

int yyerror() {
    int line_number = getLineNumber();
    printf("Syntax error at line %d.\n", line_number);
    exit(3);
}