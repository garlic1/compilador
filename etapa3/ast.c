#include "ast.h"

extern FILE *out;

AST* ast_create(int type, hash_node* symbol, AST* child_0, AST* child_1, AST* child_2, AST* child_3) {
    AST* node = (AST*) calloc(1, sizeof(AST));
    node->type = type;
    node->symbol = symbol;
    node->children[0] = child_0;
    node->children[1] = child_1;
    node->children[2] = child_2;
    node->children[3] = child_3;
    return node;
}

void ast_print(AST* node, int level) {
    if (node == 0) {
        return;
    }

    for (int i = 0; i < level; i++) {
        fprintf(stderr, "\t");
    }
    fprintf(stderr, "ast(");
    switch (node -> type) {
        case AST_GLOBAL_DECLARATION_LIST:
            fprintf(stderr, "AST_GLOBAL_DECLARATION_LIST");
            break;
        case AST_GLOBAL_DECLARATION:
            fprintf(stderr, "AST_GLOBAL_DECLARATION");
            break;
        case AST_VARIABLE_DECLARATION:
            fprintf(stderr, "AST_VARIABLE_DECLARATION");
            break;
        case AST_FUNCTION_DECLARATION:
            fprintf(stderr, "AST_FUNCTION_DECLARATION");
            break;
        case AST_ARRAY_DECLARATION:
            fprintf(stderr, "AST_ARRAY_DECLARATION");
            break;
        case AST_FUNCTION_PARAMETERS:
            fprintf(stderr, "AST_FUNCTION_PARAMETERS");
            break;
        case AST_ARRAY_INITIAL_VALUES:
            fprintf(stderr, "AST_ARRAY_INITIAL_VALUES");
            break;
        case AST_COMMAND:
            fprintf(stderr, "AST_COMMAND");
            break;
        case AST_FLOW_CONTROL:
            fprintf(stderr, "AST_FLOW_CONTROL");
            break;
        case AST_EXPRESSION:
            fprintf(stderr, "AST_EXPRESSION");
            break;
        case AST_BLOCK:
            fprintf(stderr, "AST_BLOCK");
            break;
        case AST_PRINT_EXPRESSION:
            fprintf(stderr, "AST_PRINT_EXPRESSION");
            break;
        case AST_PRINT_TYPE_STRING:
            fprintf(stderr, "AST_PRINT_TYPE_STRING");
            break;
        case AST_PRINT_STRING:
            fprintf(stderr, "AST_PRINT_STRING");
            break;
        case AST_READ:
            fprintf(stderr, "AST_READ");
            break;
        case AST_RETURN:
            fprintf(stderr, "AST_RETURN");
            break;
        case AST_VARIABLE_ATTRIBUTION:
            fprintf(stderr, "AST_VARIABLE_ATTRIBUTION");
            break;
        case AST_ARRAY_ATTRIBUTION:
            fprintf(stderr, "AST_ARRAY_ATTRIBUTION");
            break;
        case AST_COMMANDS_LIST:
            fprintf(stderr, "AST_COMMANDS_LIST");
            break;
        case AST_ARGUMENTS_LIST:
            fprintf(stderr, "AST_ARGUMENTS_LIST");
            break;
        case AST_TYPE:
            fprintf(stderr, "AST_TYPE");
            break;
        case AST_LITERAL:
            fprintf(stderr, "AST_LITERAL");
            break;
        case AST_SUM:
            fprintf(stderr, "AST_SUM");
            break;
        case AST_SUB:
            fprintf(stderr, "AST_SUB");
            break;
        case AST_MUL:
            fprintf(stderr, "AST_MUL");
            break;
        case AST_DIV:
            fprintf(stderr, "AST_DIV");
            break;
        case AST_LT:
            fprintf(stderr, "AST_LT");
            break;
        case AST_GT:
            fprintf(stderr, "AST_GT");
            break;
        case AST_LE:
            fprintf(stderr, "AST_LE");
            break;
        case AST_GE:
            fprintf(stderr, "AST_GE");
            break;
        case AST_EQ:
            fprintf(stderr, "AST_EQ");
            break;
        case AST_DIF:
            fprintf(stderr, "AST_DIF");
            break;
        case AST_AND:
            fprintf(stderr, "AST_AND");
            break;
        case AST_OR:
            fprintf(stderr, "AST_OR");
            break;
        case AST_NOT:
            fprintf(stderr, "AST_NOT");
            break;
        case AST_FUNCTION_CALL:
            fprintf(stderr, "AST_FUNCTION_CALL");
            break;
        case AST_INT:
            fprintf(stderr, "AST_INT");
            break;
        case AST_BOOL:
            fprintf(stderr, "AST_BOOL");
            break;
        case AST_CHAR:
            fprintf(stderr, "AST_CHAR");
            break;
        case AST_FLOAT:
            fprintf(stderr, "AST_FLOAT");
            break;
        case AST_IF:
            fprintf(stderr, "AST_IF");
            break;
        case AST_IF_ELSE:
            fprintf(stderr, "AST_IF_ELSE");
            break;
        case AST_WHILE:
            fprintf(stderr, "AST_WHILE");
            break;
        case AST_SYMBOL:
            fprintf(stderr, "AST_SYMBOL");
            break;
        case AST_ARRAY_ACCESS:
            fprintf(stderr, "AST_ARRAY_ACCESS");
            break;
        default:
            fprintf(stderr, "AST_UNKNOWN");
            break;
    }

    if (node->symbol!=0)
        fprintf(stderr, ",%s", node->symbol->value);
    else 
        fprintf(stderr, ",0");
    
    fprintf(stderr, ")\n");
    

    for(int i=0; i<MAX_CHILDREN; i++)
        ast_print(node->children[i], level + 1);
}

void ast_decomp (AST *node) {
    return;
}