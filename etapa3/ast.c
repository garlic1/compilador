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
        case AST_SYMBOL:
            fprintf(stderr, "AST_SYMBOL"); 
            break;
        case AST_SUM:
            fprintf(stderr, "AST_ADD"); 
            break;
        case AST_SUB:
            fprintf(stderr, "AST_SUB"); 
            break;
        case AST_GLOBAL_LIST:
            fprintf(stderr, "AST_GLOBAL_LIST");
            break;
        case AST_GLOBAL_VARIABLE:
            fprintf(stderr, "AST_GLOBAL_VARIABLE");
            break;
        case AST_ACCESS_VECTOR:
            fprintf(stderr, "AST_ACCESS_VECTOR");
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
        case AST_ACCESS_FUNCTION:
            fprintf(stderr, "AST_ACCESS_FUNCTION");
            break;
        case AST_INPUT:
            fprintf(stderr, "AST_INPUT");
            break;
        case AST_INT:
            fprintf(stderr, "AST_INT");
            break;
        case AST_CHAR:
            fprintf(stderr, "AST_CHAR");
            break;
        case AST_FLOAT:
            fprintf(stderr, "AST_FLOAT");
            break;
        case AST_BLOCK:
            fprintf(stderr, "AST_BLOCK");
            break;
        case AST_COMMANDS_CHAIN:
            fprintf(stderr, "AST_COMMANDS_CHAIN");
            break;
        case AST_FUNCTION_LIST:
            fprintf(stderr, "AST_FUNCTION_LIST");
            break;
        case AST_VECTOR_DECLARATION:
            fprintf(stderr, "AST_VECTOR_DECLARATION");
            break;
        case AST_EXPR_LIST:
            fprintf(stderr, "AST_EXPR_LIST");
            break;
        case AST_FUNCTION_PROTOTYPE:
            fprintf(stderr, "AST_FUNCTION_PROTOTYPE");
            break;
        case AST_PARAMETER_LIST:
            fprintf(stderr, "AST_PARAMETER_LIST");
            break;
        case AST_PARAMETER:
            fprintf(stderr, "AST_PARAMETER");
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
        case AST_ATTR:
            fprintf(stderr, "AST_ATTR");
            break;
        case AST_ATTR_VECTOR:
            fprintf(stderr, "AST_ATTR_VECTOR");
            break;
        case AST_RETURN:
            fprintf(stderr, "AST_RETURN");
            break;
        case AST_PRINT:
            fprintf(stderr, "AST_PRINT");
            break;
        case AST_PRINT_VALUE:
            fprintf(stderr, "AST_PRINT_VALUE");
            break;
        default:
            fprintf(stderr, "AST_UNKNOWN"); 
            break;
    }
    fprintf(stderr, ")\n");

     if(node->symbol!=0)
        fprintf(stderr, ",%s \n", node->symbol->value);

    for(int i=0; i<MAX_CHILDREN; i++)
        ast_print(node->children[i], level + 1);
}

// fazer mais simples primeiro -> soma, subtraçao etc
// complicados -> vetor, attr, recursoes, 
void ast_decomp (AST *node) {
    if (!node) {
        return;
    } 

	switch (node -> type) {
        case AST_GLOBAL_LIST:
            fprintf(stderr, "data = {\n");
            ast_decomp(node->children[0]);
            fprintf(stderr, "}\n");
            break;
        case AST_GLOBAL_VARIABLE:
            ast_decomp(node->children[0]);
            if (node->children[1]) {
                ast_decomp(node->children[1]);
            }
		case AST_SYMBOL:
			fprintf(stderr,"%s",node->symbol->value);
			break;
		case AST_SUM:
			ast_decomp(node->children[0]);
			fprintf(stderr, " + ");
			ast_decomp(node->children[1]);
			break;
        case AST_INT: 
            fprintf(stderr, "int");
            break;
        default:
            break;
    }
}