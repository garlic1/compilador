
#include "hash.h"

#define MAX_CHILDREN 4

typedef struct ast_node {
    int type;
    hash_node* symbol;
    struct ast_node* children[MAX_CHILDREN];
} AST;

AST* ast_create(int type, hash_node* symbol, AST* child_0, AST* child_1, AST* child_2, AST* child_3);
AST* ast_print(AST* tree, int level);