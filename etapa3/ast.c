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

AST* ast_print(AST* tree, int level) {

}