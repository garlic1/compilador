#ifndef AST_HEADER
#define AST_HEADER

#include "hash.h"

#define MAX_CHILDREN 4

#define AST_GLOBAL_DECLARATION_LIST 1
#define AST_GLOBAL_DECLARATION 2
#define AST_VARIABLE_DECLARATION 3 
#define AST_FUNCTION_DECLARATION 4
#define AST_ARRAY_DECLARATION 5
#define AST_FUNCTION_PARAMETERS 6
#define AST_ARRAY_INITIAL_VALUES 7
#define AST_COMMAND 8
#define AST_FLOW_CONTROL 9
#define AST_EXPRESSION 10
#define AST_BLOCK 11

#define AST_PRINT_EXPRESSION 12
#define AST_PRINT_TYPE_STRING 13
#define AST_PRINT_STRING 14
#define AST_READ 15 
#define AST_RETURN 16
#define AST_VARIABLE_ATTRIBUTION 17
#define AST_ARRAY_ATTRIBUTION 18

#define AST_COMMANDS_LIST 19
#define AST_ARGUMENTS_LIST 20
#define AST_TYPE 21
#define AST_LITERAL 22

#define AST_SUM 23
#define AST_SUB 24
#define AST_MUL 25
#define AST_DIV 26
#define AST_LT 27
#define AST_GT 28
#define AST_LE 29
#define AST_GE 30
#define AST_EQ 31
#define AST_DIF 32
#define AST_AND 33 
#define AST_OR 34
#define AST_NOT 35
#define AST_FUNCTION_CALL 36

#define AST_INT 37
#define AST_BOOL 38
#define AST_CHAR 39
#define AST_FLOAT 40

#define AST_IF 41
#define AST_IF_ELSE 42
#define AST_WHILE 43

#define AST_SYMBOL 44
#define AST_ARRAY_ACCESS 45


typedef struct ast_node {
    int type;
    hash_node* symbol;
    struct ast_node* children[MAX_CHILDREN];
} AST;

AST* ast_create(int type, hash_node* symbol, AST* child_0, AST* child_1, AST* child_2, AST* child_3);
void ast_decomp(AST* node);
void ast_print(AST* tree, int level);

#endif