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

typedef struct ast_node {
    int type;
    hash_node* symbol;
    struct ast_node* children[MAX_CHILDREN];
} AST;

AST* ast_create(int type, hash_node* symbol, AST* child_0, AST* child_1, AST* child_2, AST* child_3);
void ast_decomp(AST* node);
void ast_print(AST* tree, int level);

#endif