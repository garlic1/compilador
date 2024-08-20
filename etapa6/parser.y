%{
    #include "ast.h"
    #include "hash.h"
    #include "tacs.h"

    int yylex(void);
    int yyerror();
    extern int getLineNumber();

    AST *ast_root = 0;
%}

%union {
    hash_node *symbol;
    AST *ast;
}

%token<symbol> KW_CHAR
%token<symbol> KW_INT
%token<symbol> KW_FLOAT
%token<symbol> KW_BOOL

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

%token<symbol> TK_IDENTIFIER

%token<symbol> LIT_INT
%token<symbol> LIT_CHAR
%token<symbol> LIT_REAL
%token<symbol> LIT_FALSE
%token<symbol> LIT_TRUE
%token<symbol> LIT_STRING

%token TOKEN_ERROR

%type<ast> global_declaration_list
%type<ast> global_declaration
%type<ast> variable_declaration
%type<ast> function_declaration
%type<ast> array_declaration
%type<ast> function_parameters
%type<ast> array_initial_values
%type<ast> command
%type<ast> flow_control
%type<ast> expression
%type<ast> simple_command
%type<ast> block
%type<ast> commands_list
%type<ast> arguments_list
%type<ast> type
%type<ast> literal

%left '+' '-'
%left '*' '/'
%left '|' '&'
%left '~'
%left '<' '>' OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_DIF 

%left "then"
%left KW_ELSE

%%

    program: global_declaration_list {ast_print($1, 0); ast_decomp($1); tac_print_backwards(generate_code($1));}
        ;

    global_declaration_list: global_declaration global_declaration_list {$$ = ast_create(AST_GLOBAL_DECLARATION_LIST, 0, $1, $2, 0, 0);}
        |   {$$ = 0;}
        ;
    
    global_declaration: variable_declaration    {$$ = $1;}
        | function_declaration                  {$$ = $1;}
        | array_declaration                     {$$ = $1;}
        ;

    function_declaration: type TK_IDENTIFIER '(' function_parameters ')' block {$$ = ast_create(AST_FUNCTION_DECLARATION, $2, $1, $4, $6, 0);}
        ;
    
    function_parameters: type TK_IDENTIFIER ',' function_parameters {$$ = ast_create(AST_FUNCTION_PARAMETERS, $2, $1, $4, 0, 0);}
        | type TK_IDENTIFIER                                        {$$ = ast_create(AST_FUNCTION_PARAMETERS, $2, $1, 0, 0, 0);}
        |                                                           {$$ = 0;}
        ;

    variable_declaration: type TK_IDENTIFIER ':' literal ';'        {$$ = ast_create(AST_VARIABLE_DECLARATION, $2, $1, $4, 0, 0);}
        ;
    
    array_declaration: type TK_IDENTIFIER '[' LIT_INT ']' ';'                {AST* literal_node = ast_create(AST_SYMBOL, $4, 0, 0, 0, 0); $$ = ast_create(AST_ARRAY_DECLARATION, $2, $1, literal_node, 0, 0);}
        | type TK_IDENTIFIER '[' LIT_INT ']' ':' array_initial_values ';'    {AST* literal_node = ast_create(AST_SYMBOL, $4, 0, 0, 0, 0);$$ = ast_create(AST_ARRAY_DECLARATION, $2, $1, literal_node, $7, 0);}
        ;
    
    array_initial_values: literal array_initial_values              {$$ = ast_create(AST_ARRAY_INITIAL_VALUES, 0, $1, $2, 0, 0);}
        | literal                                                   {$$ = ast_create(AST_ARRAY_INITIAL_VALUES, 0, $1, 0, 0, 0);}
        ;

    command: flow_control 
        | expression ';'
        | simple_command ';'
        | block
        ;

    simple_command: KW_PRINT type expression                {$$ = ast_create(AST_PRINT_EXPRESSION, 0, $2, $3, 0, 0);}
        | KW_PRINT LIT_STRING                               {AST* string_node = ast_create(AST_SYMBOL, $2, 0, 0, 0, 0); $$ = ast_create(AST_PRINT_STRING, 0, string_node, 0, 0, 0);}
        | KW_READ type TK_IDENTIFIER                        {$$ = ast_create(AST_READ, $3, $2, 0, 0, 0);}
        | KW_RETURN expression                              {$$ = ast_create(AST_RETURN, 0, $2, 0, 0, 0);}
        | TK_IDENTIFIER '=' expression                      {$$ = ast_create(AST_VARIABLE_ATTRIBUTION, $1, $3, 0, 0, 0);}
        | TK_IDENTIFIER '[' expression ']' '=' expression   {$$ = ast_create(AST_ARRAY_ATTRIBUTION, $1, $3, $6, 0, 0);}
        |                                                   {$$ = 0;}
        ;
    
    block: '{' commands_list '}'            {$$ = ast_create(AST_BLOCK, 0, $2, 0, 0, 0);}
        ;
    
    commands_list: command commands_list    {$$ = ast_create(AST_COMMANDS_LIST, 0, $1, $2, 0, 0);}
        |                                   {$$ = 0;}
        ;
    
    expression: TK_IDENTIFIER                   {$$ = ast_create(AST_SYMBOL, $1, 0, 0, 0, 0);}
        | TK_IDENTIFIER '[' expression ']'      {$$ = ast_create(AST_ARRAY_ACCESS, $1, $3, 0, 0, 0);}
        | literal                               {$$ = $1;}
        | '(' expression ')'                    {$$ = $2;}
        | expression '+' expression             {$$ = ast_create(AST_SUM, 0, $1, $3, 0, 0);}
        | expression '-' expression             {$$ = ast_create(AST_SUB, 0, $1, $3, 0, 0);}
        | expression '*' expression             {$$ = ast_create(AST_MUL, 0, $1, $3, 0, 0);}
        | expression '/' expression             {$$ = ast_create(AST_DIV, 0, $1, $3, 0, 0);}
        | expression '<' expression             {$$ = ast_create(AST_LT, 0, $1, $3, 0, 0);}
        | expression '>' expression             {$$ = ast_create(AST_GT, 0, $1, $3, 0, 0);}
        | expression OPERATOR_LE expression     {$$ = ast_create(AST_LE, 0, $1, $3, 0, 0);}
        | expression OPERATOR_GE expression     {$$ = ast_create(AST_GE, 0, $1, $3, 0, 0);}
        | expression OPERATOR_EQ expression     {$$ = ast_create(AST_EQ, 0, $1, $3, 0, 0);}
        | expression OPERATOR_DIF expression    {$$ = ast_create(AST_DIF, 0, $1, $3, 0, 0);}
        | expression '&' expression             {$$ = ast_create(AST_AND, 0, $1, $3, 0, 0);}
        | expression '|' expression             {$$ = ast_create(AST_OR, 0, $1, $3, 0, 0);}
        | '~' expression                        {$$ = ast_create(AST_NOT, 0, $2, 0, 0, 0);}
        | TK_IDENTIFIER '(' arguments_list ')'  {$$ = ast_create(AST_FUNCTION_CALL, $1, $3, 0, 0, 0);}
        ;
    
    arguments_list: expression ',' arguments_list   {$$ = ast_create(AST_ARGUMENTS_LIST, 0, $1, $3, 0, 0);}
        | expression                                {$$ = ast_create(AST_ARGUMENTS_LIST, 0, $1, 0, 0, 0);}
        |                                           {$$ = 0;}
        ;

    flow_control: KW_IF '(' expression ')' command %prec "then"     {$$ = ast_create(AST_IF, 0, $3, $5, 0, 0);}
        | KW_IF '(' expression ')' command KW_ELSE command          {$$ = ast_create(AST_IF_ELSE, 0, $3, $5, $7, 0);}
        | KW_WHILE '(' expression ')' command                       {$$ = ast_create(AST_WHILE, 0, $3, $5, 0, 0);}
        ;

    type: KW_CHAR   {$$ = ast_create(AST_CHAR, 0, 0, 0, 0, 0);}
        | KW_BOOL   {$$ = ast_create(AST_BOOL, 0, 0, 0, 0, 0);}
        | KW_FLOAT  {$$ = ast_create(AST_FLOAT, 0, 0, 0, 0, 0);}
        | KW_INT    {$$ = ast_create(AST_INT, 0, 0, 0, 0, 0);}
        ;
    
    literal: LIT_FALSE  {$$ = ast_create(AST_SYMBOL, $1, 0, 0, 0, 0);}
        | LIT_TRUE      {$$ = ast_create(AST_SYMBOL, $1, 0, 0, 0, 0);}
        | LIT_INT       {$$ = ast_create(AST_SYMBOL, $1, 0, 0, 0, 0);}
        | LIT_REAL      {$$ = ast_create(AST_SYMBOL, $1, 0, 0, 0, 0);}
        | LIT_CHAR      {$$ = ast_create(AST_SYMBOL, $1, 0, 0, 0, 0);}
        ;


%%

int yyerror() {
    int line_number = getLineNumber();
    printf("Syntax error at line %d.\n", line_number);
    exit(3);
}