#include "tacs.h"

tac_node* make_if(tac_node* tac1, tac_node* tac2);
tac_node* make_if_else(tac_node* tac1, tac_node* tac2, tac_node* tac3);
tac_node* make_while(tac_node* tac1, tac_node* tac2, hash_node* return_label);
tac_node* make_print(tac_node* tac1, AST* node);
tac_node* make_function(tac_node* tacs[], AST* node);
tac_node* make_access_function(tac_node* tacs[], AST* node, hash_node* label);

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
        
        case TAC_JUMP_FALSE:
            fprintf(stderr, "TAC_JUMP_FALSE");
            break;
        
        case TAC_JUMP:
            fprintf(stderr, "TAC_JUMP");
            break;
        
        case TAC_LABEL:
            fprintf(stderr, "TAC_LABEL");
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
    hash_node* label = NULL;

    if (node->type == AST_WHILE) {
        label = create_label();
    }

    for (int i=0; i<MAX_CHILDREN; i++) {
        code[i]=generate_code(node->children[i]);
    }

    switch (node->type) {
        case AST_SYMBOL:
            result = tac_create(TAC_SYMBOL, node->symbol, 0, 0);
            break;
        case AST_SUM:
        case AST_SUB:
        case AST_MUL:
        case AST_DIV:
        case AST_LT:
        case AST_GT:
        case AST_LE:
        case AST_GE:
        case AST_EQ:
        case AST_DIF:
        case AST_AND:
        case AST_OR:
            result = tac_join(
                tac_join(code[0],code[1]),
                tac_create(node->type,create_temp(),code[0]?code[0]->res:0,code[1]?code[1]->res:0)
            );
            break;
        case AST_ATTR:
            result = tac_join(
                code[0],    
                tac_create(TAC_ATTR,node->symbol,code[0]?code[0]->res:0,0)
            );
            break;
        case AST_NOT:
            result = tac_join(
                code[0],
                tac_create(TAC_NOT,create_temp(), code[0]?code[0]->res:0,0)
            );
            break;
        case AST_IF:
            result = make_if(code[0],code[1]);
            break;
        case AST_IF_ELSE:
            result = make_if_else(code[0],code[1],code[2]);
            break;
        case AST_WHILE:
            result = make_while(code[0], code[1], label);
            break;
        
        case AST_PRINT:
            result = code[0];
            break;
        case AST_PRINT_VALUE:
            result = make_print(code[0],node);
            break;

        case AST_RETURN:
            result = tac_join(code[0], tac_create(TAC_RETURN, code[0]?code[0]->res:0,0,0));
            break;
        case AST_INPUT:
            result = tac_create(TAC_INPUT,create_temp(),0,0);
            break;
        
        case AST_FUNCTION:
            result = make_function(code, node);
            break;
        case AST_ACCESS_FUNCTION:
            label = create_label();
            result = make_access_function(code,node,label);
            break;
        
        case AST_ACCESS_VECTOR:
            result = tac_join(code[0], tac_create(TAC_ACCESS_VECTOR,create_temp(),node->symbol,code[0]?code[0]->res:0));
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

tac_node* make_if(tac_node* tac1, tac_node* tac2) {
    tac_node* jump_tac = NULL;
    tac_node* label_tac = NULL;
    hash_node* new_label = NULL;

    new_label = create_label();

    jump_tac = tac_create(TAC_JUMP_FALSE,new_label,tac1?tac1->res:0,0);
    jump_tac->prev=tac1;
    label_tac = tac_create(TAC_LABEL,new_label,0,0);
    label_tac->prev=tac2;

    return tac_join(jump_tac,label_tac);
}

tac_node* make_if_else(tac_node* tac1, tac_node* tac2, tac_node* tac3) {
    tac_node* jump_tac = NULL;
    tac_node* label_tac = NULL;
    tac_node* else_tac = NULL;
    hash_node* new_label = NULL;
    hash_node* label_end = NULL;

    new_label = create_label();
    label_end = create_label();

    jump_tac = tac_create(TAC_JUMP_FALSE,new_label,tac1?tac1->res:0,0);
    jump_tac->prev=tac1;
    label_tac = tac_create(TAC_LABEL,new_label,0,0);
    label_tac->prev=tac_join(tac2,tac_create(TAC_JUMP,label_end,0,0));
    else_tac = tac_create(TAC_LABEL,label_end,0,0);
    else_tac->prev=tac3;

    return tac_join(jump_tac,tac_join(label_tac,else_tac));
}

tac_node* make_while(tac_node* tac1, tac_node* tac2, hash_node* return_label) {
    tac_node* while_tac = NULL;
    tac_node* label_tac = NULL;
    tac_node* end_tac = NULL;
    hash_node* end_label = NULL;

    end_label = create_label();

    while_tac = tac_create(TAC_WHILE,return_label,0,0);
    label_tac = tac_create(TAC_JUMP_FALSE,end_label,tac1?tac1->res:0,0);
    label_tac->prev=tac1;
    end_tac = tac_create(TAC_LABEL,end_label,0,0);
    end_tac->prev=tac_join(tac2,tac_create(TAC_JUMP,return_label,0,0));

    return tac_join(
        while_tac,
        tac_join(
                label_tac,
                end_tac
            )
        );
}

tac_node* make_print(tac_node* tac1, AST* node) {
    tac_node* print_tac = NULL;

    if(node->symbol) {
        print_tac=tac_create(TAC_PRINT_VALUE,node->symbol,0,0);
        print_tac->prev = tac1;
        return tac_join(tac1,print_tac);
    }
    
    print_tac=tac_create(TAC_PRINT_VALUE,tac1?tac1->res:0,0,0);
    print_tac->prev = tac1;
    return print_tac;
}

tac_node* make_function(tac_node* tacs[], AST* node) {
    tac_node* symbol = NULL;
    tac_node* tac_begin_function = NULL;
    tac_node* tac_end_function = NULL;

    symbol = tac_create(TAC_SYMBOL, node->symbol, 0,0);
    tac_begin_function = tac_create(TAC_BEGIN_FUNCTION, symbol->res, 0, 0);
    tac_begin_function->prev = symbol;
    tac_end_function = tac_create(TAC_END_FUNCTION, symbol->res, 0, 0);
    tac_end_function->prev=tacs[0];

    return tac_join(tac_begin_function, tac_end_function);
}

tac_node* make_access_function(tac_node* tacs[], AST* node, hash_node* label) {
    tac_node* tac_function_call = NULL;
    tac_node* tac_jump_to_function = NULL;
    tac_function_call = tac_create(TAC_ACCESS_FUNCTION,node->symbol,label,0);
    tac_jump_to_function = tac_join(tac_create(TAC_JUMP,node->symbol,0,0), tac_create(TAC_LABEL,label,0,0)); 

    // params?

    return tac_join(
                tac_join(
                    tac_join(tac_function_call,tacs[0]),
                    tac_jump_to_function
                ),
                tac_create(TAC_FUNCTION_RESULT, create_temp(), 0, 0)
            );
}

tac_node* tac_reverse(tac_node* tac) {
    tac_node* t = tac;

    for (t=tac;t->prev;t=t->prev) {
        t->prev->next = t;
    }

    return t;
}