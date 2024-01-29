#include "tacs.h"

tac_node* tac_create(int type, hash_node* res, hash_node* op1, hash_node* op2) {
    tac_node* node = (tac_node*)calloc(1, sizeof(tac_node));

    node->type = type;
    node->res = res;
    node->op1 = op1;
    node->op2 = op2;
    node->prev = NULL;
    node->next = NULL;

    return node;
}

void tac_print(tac_node* tac) {

    if (tac == NULL) {
        return;
    }

    if (tac->type == TAC_SYMBOL) {
        return;
    }

    fprintf(stderr, "TAC(");
    switch(tac->type) {
        case TAC_SYMBOL: 
            fprintf(stderr, "TAC_SYMBOL"); 
            break;

        case TAC_GLOBAL_LIST:
            fprintf(stderr, "TAC_GLOBAL_LIST");
            break;

        case TAC_GLOBAL_VARIABLE:
            fprintf(stderr, "TAC_GLOBAL_VARIABLE");
            break;

        case TAC_ACCESS_VECTOR:
            fprintf(stderr, "TAC_ACCESS_VECTOR");
            break;

        case TAC_SUM:
            fprintf(stderr, "TAC_SUM");
            break;

        case TAC_SUB:
            fprintf(stderr, "TAC_SUB");
            break;

        case TAC_MUL:
            fprintf(stderr, "TAC_MUL");
            break;

        case TAC_DIV:
            fprintf(stderr, "TAC_DIV");
            break;

        case TAC_LT:
            fprintf(stderr, "TAC_LT");
            break;

        case TAC_GT:
            fprintf(stderr, "TAC_GT");
            break;

        case TAC_LE:
            fprintf(stderr, "TAC_LE");
            break;

        case TAC_GE:
            fprintf(stderr, "TAC_GE");
            break;

        case TAC_EQ:
            fprintf(stderr, "TAC_EQ");
            break;

        case TAC_DIF:
            fprintf(stderr, "TAC_DIF");
            break;

        case TAC_AND:
            fprintf(stderr, "TAC_AND");
            break;

        case TAC_OR:
            fprintf(stderr, "TAC_OR");
            break;

        case TAC_NOT:
            fprintf(stderr, "TAC_NOT");
            break;

        case TAC_ACCESS_FUNCTION:
            fprintf(stderr, "TAC_ACCESS_FUNCTION");
            break;

        case TAC_INPUT:
            fprintf(stderr, "TAC_INPUT");
            break;

        case TAC_INT:
            fprintf(stderr, "TAC_INT");
            break;

        case TAC_CHAR:
            fprintf(stderr, "TAC_CHAR");
            break;

        case TAC_FLOAT:
            fprintf(stderr, "TAC_FLOAT");
            break;

        case TAC_BLOCK:
            fprintf(stderr, "TAC_BLOCK");
            break;

        case TAC_COMMANDS_CHAIN:
            fprintf(stderr, "TAC_COMMANDS_CHAIN");
            break;

        case TAC_FUNCTION_LIST:
            fprintf(stderr, "TAC_FUNCTION_LIST");
            break;

        case TAC_VECTOR_DECLARATION:
            fprintf(stderr, "TAC_VECTOR_DECLARATION");
            break;

        case TAC_EXPR_LIST:
            fprintf(stderr, "TAC_EXPR_LIST");
            break;

        case TAC_FUNCTION_PROTOTYPE:
            fprintf(stderr, "TAC_FUNCTION_PROTOTYPE");
            break;

        case TAC_PARAMETER_LIST:
            fprintf(stderr, "TAC_PARAMETER_LIST");
            break;

        case TAC_PARAMETER:
            fprintf(stderr, "TAC_PARAMETER");
            break;

        case TAC_IF:
            fprintf(stderr, "TAC_IF");
            break;

        case TAC_IF_ELSE:
            fprintf(stderr, "TAC_IF_ELSE");
            break;

        case TAC_WHILE:
            fprintf(stderr, "TAC_WHILE");
            break;

        case TAC_ATTR:
            fprintf(stderr, "TAC_ATTR");
            break;

        case TAC_ATTR_VECTOR:
            fprintf(stderr, "TAC_ATTR_VECTOR");
            break;

        case TAC_RETURN:
            fprintf(stderr, "TAC_RETURN");
            break;

        case TAC_PRINT:
            fprintf(stderr, "TAC_PRINT");
            break;

        case TAC_PRINT_VALUE:
            fprintf(stderr, "TAC_PRINT_VALUE");
            break;

        case TAC_VECTOR_INTIIAL_VALUES:
            fprintf(stderr, "TAC_VECTOR_INTIIAL_VALUES");
            break;

        case TAC_FUNCTION:
            fprintf(stderr, "TAC_FUNCTION");
            break;

        default:
            fprintf(stderr, "TAC_UNKNOWN");
            break;
    }
    fprintf(stderr,",%s", (tac->res) ? tac->res->value : "");
    fprintf(stderr,",%s", (tac->op1) ? tac->op1->value : "");
    fprintf(stderr,",%s", (tac->op2) ? tac->op2->value : "");
    fprintf(stderr,");\n");
}

void tac_print_backwards(tac_node* tac) {
    if (tac == NULL) {
        return;
    }

    tac_print_backwards(tac->prev);
    tac_print(tac);
}

tac_node* generate_code(AST* node) {
    if (node == NULL) {
        return NULL;
    }

    tac_node *result = 0;
    tac_node *code[MAX_CHILDREN];

    for (int i=0; i<MAX_CHILDREN; i++) {
        code[i]=generate_code(node->children[i]);
    }

    switch (node->type) {
        case AST_GLOBAL_VARIABLE: 
            result = tac_create(TAC_GLOBAL_VARIABLE, node->symbol, 0, 0); 
            break;
        case AST_SYMBOL:
            result = tac_create(TAC_SYMBOL, node->symbol, 0, 0);
            break;
        case AST_SUM:
            result = tac_join(
                tac_join(code[0],code[1]),
                tac_create(TAC_SUM,create_temp(),code[0]?code[0]->res:0,code[1]?code[1]->res:0)
            );
            break;
        case AST_SUB:
            result = tac_join(
                tac_join(code[0],code[1]),
                tac_create(TAC_SUB,create_temp(),code[0]?code[0]->res:0,code[1]?code[1]->res:0)
            );
            break;
        case AST_MUL:
            result = tac_join(
                tac_join(code[0],code[1]),
                tac_create(TAC_MUL,create_temp(),code[0]?code[0]->res:0,code[1]?code[1]->res:0)
            );
            break;
        case AST_DIV:
            result = tac_join(
                tac_join(code[0],code[1]),
                tac_create(TAC_DIV,create_temp(),code[0]?code[0]->res:0,code[1]?code[1]->res:0)
            );
            break;
        case AST_ATTR:
            result = tac_join(
                code[0],
                tac_create(TAC_ATTR,node->symbol,code[0]?code[0]->res:0,0)
            );
            break;
        default: 
            result = tac_join(code[0], tac_join(code[1], tac_join(code[2], code[3])));
            break;
    }

    return result;
}

tac_node* tac_join(tac_node* tac_list1, tac_node* tac_list2) {
    if (tac_list1 == NULL) {
        return tac_list2;
    }
    
    if (tac_list2 == NULL) {
        return tac_list1;
    }

    tac_node* point;

    for (point = tac_list2; point->prev != NULL; point = point->prev) {
        // do nothing
    }

    point->prev = tac_list1;
    return tac_list2;

}