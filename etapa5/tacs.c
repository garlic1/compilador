#include "tacs.h"

void tac_print(tac_node* tac) {
    if(!tac || tac->type == TAC_SYMBOL) {
        return;
    }

    fprintf(stderr, "TAC(");
    switch(tac->type) {
        case TAC_GLOBAL_DECLARATION_LIST: 
            fprintf(stderr, "TAC_GLOBAL_DECLARATION_LIST"); 
            break;
        case TAC_GLOBAL_DECLARATION: 
            fprintf(stderr, "TAC_GLOBAL_DECLARATION"); 
            break;
        case TAC_VARIABLE_DECLARATION: 
            fprintf(stderr, "TAC_VARIABLE_DECLARATION"); 
            break;
        case TAC_FUNCTION_DECLARATION: 
            fprintf(stderr, "TAC_FUNCTION_DECLARATION"); 
            break;
        case TAC_ARRAY_DECLARATION: 
            fprintf(stderr, "TAC_ARRAY_DECLARATION"); 
            break;
        case TAC_FUNCTION_PARAMETERS: 
            fprintf(stderr, "TAC_FUNCTION_PARAMETERS"); 
            break;
        case TAC_ARRAY_INITIAL_VALUES: 
            fprintf(stderr, "TAC_ARRAY_INITIAL_VALUES"); 
            break;
        case TAC_COMMAND: 
            fprintf(stderr, "TAC_COMMAND"); 
            break;
        case TAC_FLOW_CONTROL: 
            fprintf(stderr, "TAC_FLOW_CONTROL"); 
            break;
        case TAC_EXPRESSION: 
            fprintf(stderr, "TAC_EXPRESSION"); 
            break;
        case TAC_BLOCK: 
            fprintf(stderr, "TAC_BLOCK"); 
            break;
        case TAC_PRINT_EXPRESSION: 
            fprintf(stderr, "TAC_PRINT_EXPRESSION"); 
            break;
        case TAC_PRINT_TYPE_STRING: 
            fprintf(stderr, "TAC_PRINT_TYPE_STRING"); 
            break;
        case TAC_PRINT_STRING: 
            fprintf(stderr, "TAC_PRINT_STRING"); 
            break;
        case TAC_READ: 
            fprintf(stderr, "TAC_READ"); 
            break;
        case TAC_RETURN: 
            fprintf(stderr, "TAC_RETURN"); 
            break;
        case TAC_VARIABLE_ATTRIBUTION: 
            fprintf(stderr, "TAC_VARIABLE_ATTRIBUTION"); 
            break;
        case TAC_ARRAY_ATTRIBUTION: 
            fprintf(stderr, "TAC_ARRAY_ATTRIBUTION"); 
            break;
        case TAC_COMMANDS_LIST: 
            fprintf(stderr, "TAC_COMMANDS_LIST"); 
            break;
        case TAC_ARGUMENTS_LIST: 
            fprintf(stderr, "TAC_ARGUMENTS_LIST"); 
            break;
        case TAC_TYPE: 
            fprintf(stderr, "TAC_TYPE"); 
            break;
        case TAC_LITERAL: 
            fprintf(stderr, "TAC_LITERAL"); 
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
        case TAC_FUNCTION_CALL: 
            fprintf(stderr, "TAC_FUNCTION_CALL"); 
            break;
        case TAC_INT: 
            fprintf(stderr, "TAC_INT"); 
            break;
        case TAC_BOOL: 
            fprintf(stderr, "TAC_BOOL"); 
            break;
        case TAC_CHAR: 
            fprintf(stderr, "TAC_CHAR"); 
            break;
        case TAC_FLOAT: 
            fprintf(stderr, "TAC_FLOAT"); 
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
        case TAC_SYMBOL: 
            fprintf(stderr, "TAC_SYMBOL"); 
            break;
        case TAC_ARRAY_ACCESS: 
            fprintf(stderr, "TAC_ARRAY_ACCESS"); 
            break;
        case TAC_JUMP_FALSE: 
            fprintf(stderr, "TAC_JUMP_FALSE"); 
            break;
        case TAC_LABEL: 
            fprintf(stderr, "TAC_LABEL"); 
            break;
        case TAC_JUMP: 
            fprintf(stderr, "TAC_JUMP"); 
            break;
        case TAC_BEGIN_FUNCTION: 
            fprintf(stderr, "TAC_BEGIN_FUNCTION"); 
            break;
        case TAC_END_FUNCTION: 
            fprintf(stderr, "TAC_END_FUNCTION"); 
            break;
        case TAC_FUNCTION_RESULT: 
            fprintf(stderr, "TAC_FUNCTION_RESULT"); 
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
    if (!tac) {
        return;
    }

    tac_print_backwards(tac->prev);
    tac_print(tac);
}

tac_node* tac_join(tac_node* tac1, tac_node* tac2);
tac_node* tac_create(int type, hash_node* res, hash_node* op1, hash_node* op2);

tac_node* generate_code(AST* node);
