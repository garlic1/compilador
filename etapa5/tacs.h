#ifndef TACS_HEADER
#define TACS_HEADER

#include "hash.h"
#include "ast.h"

#define MAX_CHILDREN 4

#define TAC_GLOBAL_DECLARATION_LIST 1
#define TAC_GLOBAL_DECLARATION 2
#define TAC_VARIABLE_DECLARATION 3 
#define TAC_FUNCTION_DECLARATION 4
#define TAC_ARRAY_DECLARATION 5
#define TAC_FUNCTION_PARAMETERS 6
#define TAC_ARRAY_INITIAL_VALUES 7
#define TAC_COMMAND 8
#define TAC_FLOW_CONTROL 9
#define TAC_EXPRESSION 10
#define TAC_BLOCK 11

#define TAC_PRINT_EXPRESSION 12
#define TAC_PRINT_TYPE_STRING 13
#define TAC_PRINT_STRING 14
#define TAC_READ 15 
#define TAC_RETURN 16
#define TAC_VARIABLE_ATTRIBUTION 17
#define TAC_ARRAY_ATTRIBUTION 18

#define TAC_COMMANDS_LIST 19
#define TAC_ARGUMENTS_LIST 20
#define TAC_TYPE 21
#define TAC_LITERAL 22

#define TAC_SUM 23
#define TAC_SUB 24
#define TAC_MUL 25
#define TAC_DIV 26
#define TAC_LT 27
#define TAC_GT 28
#define TAC_LE 29
#define TAC_GE 30
#define TAC_EQ 31
#define TAC_DIF 32
#define TAC_AND 33 
#define TAC_OR 34
#define TAC_NOT 35
#define TAC_CALL 36

#define TAC_INT 37
#define TAC_BOOL 38
#define TAC_CHAR 39
#define TAC_FLOAT 40

#define TAC_IF 41
#define TAC_IF_ELSE 42
#define TAC_WHILE 43

#define TAC_SYMBOL 44
#define TAC_ARRAY_ACCESS 45

#define TAC_JUMP_FALSE 46
#define TAC_LABEL 47
#define TAC_JUMP 48

#define TAC_BEGINFUN 49
#define TAC_ENDFUN 50

#define TAC_RET 51
#define TAC_FUNCTION_RESULT 52
#define TAC_FUNCTION_ARGUMENT 53

typedef struct tac_node {
    int type;
    hash_node* res;
    hash_node* op1;
    hash_node* op2;
    struct tac_node* prev;
    struct tac_node* next;
} tac_node;

void tac_print(tac_node* tac);
void tac_print_backwards(tac_node* tac);
tac_node* tac_join(tac_node* tac1, tac_node* tac2);
tac_node* tac_create(int type, hash_node* res, hash_node* op1, hash_node* op2);

tac_node* generate_code(AST* node);

#endif