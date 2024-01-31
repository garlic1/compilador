#ifndef TACS_HEADER
#define TACS_HEADER

#include "hash.h"
#include "ast.h"

#define MAX_CHILDREN 4

#define TAC_SYMBOL 1
#define TAC_GLOBAL_LIST 2
#define TAC_GLOBAL_VARIABLE 3
#define TAC_ACCESS_VECTOR 4
#define TAC_SUM 5
#define TAC_SUB 6
#define TAC_MUL 7
#define TAC_DIV 8
#define TAC_LT 9
#define TAC_GT 10
#define TAC_LE 11
#define TAC_GE 12
#define TAC_EQ 13
#define TAC_DIF 14
#define TAC_AND 15 
#define TAC_OR 16
#define TAC_NOT 17
#define TAC_ACCESS_FUNCTION 18
#define TAC_INPUT 19
#define TAC_INT 20
#define TAC_CHAR 21
#define TAC_FLOAT 22

#define TAC_BLOCK 23
#define TAC_COMMANDS_CHAIN 24
#define TAC_FUNCTION_LIST 25
#define TAC_VECTOR_DECLARATION 26
#define TAC_EXPR_LIST 27
#define TAC_FUNCTION_PROTOTYPE 28
#define TAC_PARAMETER_LIST 29
#define TAC_PARAMETER 30

#define TAC_IF 31
#define TAC_IF_ELSE 32
#define TAC_WHILE 33

#define TAC_ATTR 34
#define TAC_ATTR_VECTOR 35

#define TAC_RETURN 36
#define TAC_PRINT 37
#define TAC_PRINT_VALUE 38
#define TAC_VECTOR_INTIIAL_VALUES 39
#define TAC_FUNCTION 40

#define TAC_JUMP_FALSE 41
#define TAC_LABEL 42

typedef struct tac_node {
    int type;
    hash_node* res;
    hash_node* op1;
    hash_node* op2;
    struct tac_node* prev;
    struct tac_node* next;
} tac_node;

tac_node* tac_create(int type, hash_node* res, hash_node* op1, hash_node* op2);
void tac_print(tac_node* tac);
void tac_print_backwards(tac_node* tac);
tac_node* tac_join(tac_node* tac1, tac_node* tac2);

tac_node* generate_code(AST* node);

#endif