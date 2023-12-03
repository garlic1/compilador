#include "ast.h"

AST* ast_create(int type, hash_node* symbol, AST* child_0, AST* child_1, AST* child_2, AST* child_3) {
    AST* node = (AST*) calloc(1, sizeof(AST));

    node -> type = type;
    node -> symbol = symbol;
    node -> children[0] = child_0;
    node -> children[1] = child_1;
    node -> children[2] = child_2;
    node -> children[3] = child_3;

    return node;
}

void ast_print(AST* node, int level) {

    if (node == NULL) {
        return;
    }

    for (int i = 0; i < level; i++) {
        fprintf(stderr, "\t");
    }
    fprintf(stderr, "ast(");
    switch (node -> type) {
        // case AST_SYMBOL:
        //     fprintf(stderr, "AST_SYMBOL"); 
        //     break;
        // case AST_ADD:
        //     fprintf(stderr, "AST_ADD"); 
        //     break;
        // case AST_SUB:
        //     fprintf(stderr, "AST_SUB"); 
        //     break;
        // default:
        //     fprintf(stderr, "AST_UNKNOWN"); 
        //     break;
    }
    fprintf(stderr, ")\n");
}