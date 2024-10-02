#include "tacs.h"

tac_node* makeIf(tac_node* tac1, tac_node* tac2);
tac_node* makeIfElse(tac_node* tac1, tac_node* tac2, tac_node* tac3);
tac_node* makeWhile(tac_node* tac1, tac_node* tac2, hash_node* return_label);
tac_node* makePrint(tac_node* tacs[], AST* node);
tac_node* makeFunction(tac_node* tacs[], AST* node);
tac_node* makeFunctionCall(tac_node* tacs[], AST* node, hash_node* label);

void tac_print(tac_node* tac) {
    if(!tac || tac->type == TAC_SYMBOL) return;

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
        case TAC_CALL: 
            fprintf(stderr, "TAC_CALL"); 
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
        case TAC_BEGINFUN: 
            fprintf(stderr, "TAC_BEGINFUN"); 
            break;
        case TAC_ENDFUN: 
            fprintf(stderr, "TAC_ENDFUN"); 
            break;
        case TAC_FUNCTION_RESULT: 
            fprintf(stderr, "TAC_FUNCTION_RESULT"); 
            break;
        case TAC_FUNCTION_ARGUMENT:
            fprintf(stderr, "TAC_FUNCTION_ARGUMENT");
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
    if (!tac) return;

    tac_print_backwards(tac->prev);
    tac_print(tac);
}

tac_node* tac_join(tac_node* tac1, tac_node* tac2) {
    if (!tac1) return tac2;
    if (!tac2) return tac1;

    tac_node* point;

    for (point = tac2; point->prev != NULL; point = point->prev) {
        // do nothing
    }

    point->prev = tac1;
    return tac2;
}

tac_node* tac_create(int type, hash_node* res, hash_node* op1, hash_node* op2) {
    tac_node* node = (tac_node*)calloc(1, sizeof(tac_node));

    *node = (tac_node) {
        .type = type,
        .res = res,
        .op1 = op1,
        .op2 = op2,
        .prev = NULL,
        .next = NULL
    };

    return node;
}

tac_node* generate_code(AST* node) {
    if (!node) return NULL;

    tac_node *output = NULL;
    tac_node *code[MAX_CHILDREN];
    hash_node* label = NULL;

    if (node->type == AST_WHILE) {
        label = makeLabel();
    }

    for (int i = 0; i < MAX_CHILDREN; i++) {
        code[i] = generate_code(node->children[i]);
    }

    switch (node->type) {
        case AST_SYMBOL:
            output = tac_create(TAC_SYMBOL, node->symbol, 0, 0);
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
            // works because AST_[OPERATOR] == TAC_[OPERATOR]
            output = tac_join(tac_join(code[0],code[1]),tac_create(node->type,makeTemp(),code[0]?code[0]->res:0,code[1]?code[1]->res:0));
            break;
        case AST_NOT:
            output = tac_join(code[0],tac_create(TAC_NOT,makeTemp(), code[0]?code[0]->res:0,0));
            break;
        case AST_VARIABLE_ATTRIBUTION:
            output = tac_join(code[0],tac_create(TAC_VARIABLE_ATTRIBUTION,node->symbol,code[0]?code[0]->res:0,0));
            break;
        case AST_ARRAY_ATTRIBUTION:
            output = tac_join(tac_join(code[0], code[1]), tac_create(TAC_ARRAY_ATTRIBUTION, code[0] ? code[0]->res : 0, code[1] ? code[1]->res : 0, 0));
            break;
        case AST_PRINT_EXPRESSION:
            output = makePrint(code, node);
            break;
        case AST_PRINT_STRING:
            output = tac_join(code[0], tac_create(TAC_PRINT_STRING,code[0]?code[0]->res:0,0,0));
            break;
        case AST_READ:
            output = tac_join(code[0],tac_create(TAC_READ,node->symbol,0,0));
            break;
        case AST_IF:
            output = makeIf(code[0], code[1]);
            break;
        case AST_IF_ELSE:
            output = makeIfElse(code[0],code[1],code[2]);
            break;
        case AST_WHILE:
            output = makeWhile(code[0], code[1], label);
            break;
        case AST_RETURN:
            output = tac_join(code[0], tac_create(TAC_RETURN, code[0]?code[0]->res:0,0,0));
            break;
        case AST_FUNCTION_DECLARATION:
            output = makeFunction(code, node);
            break;
        case AST_FUNCTION_PARAMETERS:
            output = tac_join(tac_join(code[0], tac_create(TAC_FUNCTION_PARAMETERS,node->symbol,code[0]?code[0]->res:0,0)), code[1]);
            break;
        case AST_FUNCTION_CALL:
            label = makeLabel();
            output = makeFunctionCall(code,node,label);
            break;
        case AST_ARGUMENTS_LIST:
            output = tac_join(code[0],tac_create(TAC_FUNCTION_ARGUMENT, node->symbol, code[0]?code[0]->res:0, 0));
            if(code[1]) {
                output = tac_join(output,code[1]);
            }
            break;
        case AST_ARRAY_ACCESS:
            output = tac_join(code[0], tac_create(TAC_ARRAY_ACCESS,makeTemp(),node->symbol,code[0]?code[0]->res:0));
            break;
        
        default:
            output = tac_join(code[0], tac_join(code[1], tac_join(code[2], code[3])));
            break;
    }

    return output;
}

tac_node* makeIf(tac_node* tac1, tac_node* tac2) {
    tac_node* jump_instruction = NULL;
    tac_node* label_instruction = NULL;
    hash_node* generated_label = NULL;

    generated_label = makeLabel();

    jump_instruction = tac_create(TAC_JUMP_FALSE, generated_label, tac1 ? tac1->res : 0, 0);
    jump_instruction->prev = tac1;
    label_instruction = tac_create(TAC_LABEL, generated_label, 0, 0);
    label_instruction->prev = tac2;

    return tac_join(jump_instruction, label_instruction);
}

tac_node* makeIfElse(tac_node* tac1, tac_node* tac2, tac_node* tac3) {
    tac_node *jump_instruction = NULL, *label_instruction = NULL, *else_instruction = NULL;
    hash_node *start_label = NULL, *end_label = NULL;
    start_label = makeLabel();
    end_label = makeLabel();

    jump_instruction = tac_create(TAC_JUMP_FALSE, start_label, tac1 ? tac1->res : 0, 0);
    jump_instruction->prev = tac1;
    label_instruction = tac_create(TAC_LABEL, start_label, 0, 0);
    label_instruction->prev = tac_join(tac2, tac_create(TAC_JUMP, end_label, 0, 0));
    else_instruction = tac_create(TAC_LABEL, end_label, 0, 0);
    else_instruction->prev = tac3;

    return tac_join(jump_instruction, tac_join(label_instruction, else_instruction));
}

tac_node* makeWhile(tac_node* tac1, tac_node* tac2, hash_node* return_label) {
    tac_node *while_instruction = NULL, *label_instruction = NULL, *end_instruction = NULL;
    hash_node *end_label = NULL;
    end_label = makeLabel();

    while_instruction = tac_create(TAC_WHILE, return_label, 0, 0);
    label_instruction = tac_create(TAC_JUMP_FALSE, end_label, tac1 ? tac1->res : 0, 0);
    label_instruction->prev = tac1;
    end_instruction = tac_create(TAC_LABEL, end_label, 0, 0);
    end_instruction->prev = tac_join(tac2, tac_create(TAC_JUMP, return_label, 0, 0));

    return tac_join(while_instruction,tac_join(label_instruction,end_instruction));
}

tac_node* makePrint(tac_node* tacs[], AST* node) {
    tac_node *print_instruction = NULL;

    if (tacs[1]) {
        print_instruction = tac_join(tacs[0],tac_create(TAC_PRINT_EXPRESSION, tacs[1] ? tacs[1]->res : 0, 0, 0));
        return tac_join(tacs[1],print_instruction);
    }
    
    if (node->symbol) {
        print_instruction = tac_join(tac_create(TAC_PRINT_EXPRESSION, node->symbol, 0, 0),tacs[0]);
        return print_instruction;
    }
}

tac_node* makeFunction(tac_node* tacs[], AST* node) {
    tac_node *symbol = NULL, *begin_function_instruction = NULL, *end_function_instruction = NULL, *function_body_instruction = NULL;

    symbol = tac_create(TAC_SYMBOL, node->symbol, 0, 0);
    begin_function_instruction = tac_create(TAC_BEGINFUN, symbol->res, 0, 0);
    function_body_instruction = tac_join(begin_function_instruction, tacs[1]);
    function_body_instruction = tac_join(function_body_instruction, tacs[2]);
    end_function_instruction = tac_create(TAC_ENDFUN, symbol->res, 0, 0);

    return tac_join(function_body_instruction, end_function_instruction);
}

tac_node* makeFunctionCall(tac_node* tacs[], AST* node, hash_node* label) {
    tac_node *function_call_instruction = NULL;

    function_call_instruction = tac_create(TAC_CALL, node->symbol, 0, 0);

    return tac_join(tac_join(function_call_instruction, tacs[0]),tac_create(TAC_FUNCTION_RESULT, makeTemp(), 0, 0));
}

tac_node* tac_reverse(tac_node* tac) {
    tac_node* t = tac;
    for (t=tac;t->prev;t=t->prev) {
        t->prev->next = t;
    }
    return t;
}
