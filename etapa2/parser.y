%{
int yylex(void);
void yyerror (char const *s);
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

%%

// um programa é composto por variaveis globais e funçoes, ambos podendo ser vazios
program: global_variables functions
    ;

global_variables: global_variable global_variables
    | /* empty */
    ;

global_variable: variable_types TK_IDENTIFICADOR ';'
    ;

// funcoes
functions: function functions
    | /* empty */
    ;

function: function_head function_body
    ;

function_head: TK_IDENTIFICADOR '(' parameter_list ')' TK_OC_MAP variable_types
    ;

parameter_list: parameter ',' parameter_list
    | parameter
    | /* empty */
    ;

parameter: variable_types TK_IDENTIFICADOR
    ;

function_body: cmd_block
    ;

// um bloco de comandos é composto por comandos separados por ponto e virgula
cmd_block: '{' cmd ';' cmd_block '}'
    | /* empty */
    ;

// comando pode ser declaraçao de variavel, comando de atribuiçao, chamada de funçao, comando de retorno ou comando de controle de fluxo
cmd: variable_declaration
    | attribution_cmd
    | function_call
    | return_cmd
    | flow_control_cmd
    ;


// tipos
variable_types: TK_PR_INT
    | TK_PR_FLOAT
    | TK_PR_BOOL
    ;


%%
