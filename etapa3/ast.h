#ifndef AST_HEADER
#define AST_HEADER

#include "hash.h"

#define MAX_CHILDREN 4

#define AST_SYMBOL 1
#define AST_GLOBAL_LIST 2
#define AST_GLOBAL_VARIABLE 3
#define AST_ACCESS_VECTOR 4
#define AST_SUM 5
#define AST_SUB 6
#define AST_MUL 7
#define AST_DIV 8
#define AST_LT 9
#define AST_GT 10
#define AST_LE 11
#define AST_GE 12
#define AST_EQ 13
#define AST_DIF 14
#define AST_AND 15 
#define AST_OR 16
#define AST_NOT 17
#define AST_ACCESS_FUNCTION 18
#define AST_INPUT 19
#define AST_INT 20
#define AST_CHAR 21
#define AST_FLOAT 22

#define AST_BLOCK 23
#define AST_COMMANDS_CHAIN 24
#define AST_FUNCTION_LIST 25
#define AST_VECTOR_DECLARATION 26
#define AST_EXPR_LIST 27
#define AST_FUNCTION_PROTOTYPE 28
#define AST_PARAMETER_LIST 29
#define AST_PARAMETER 30

#define AST_IF 31
#define AST_IF_ELSE 32
#define AST_WHILE 33

#define AST_ATTR 34
#define AST_ATTR_VECTOR 35

#define AST_RETURN 36
#define AST_PRINT 37
#define AST_PRINT_VALUE 38
#define AST_VECTOR_INTIIAL_VALUES 39
#define AST_FUNCTION 40

typedef struct ast_node {
    int type;
    hash_node* symbol;
    struct ast_node* children[MAX_CHILDREN];
} AST;

AST* ast_create(int type, hash_node* symbol, AST* child_0, AST* child_1, AST* child_2, AST* child_3);
void ast_decomp(AST* node);
void ast_print(AST* tree, int level);

#endif