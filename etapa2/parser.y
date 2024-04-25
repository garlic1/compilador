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

    program:;

%%

int yyerror() {
    int line_number = getLineNumber();
    printf("Syntax error at line %d.\n", line_number);
    exit(3);
}