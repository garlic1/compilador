#include "stack.h"

void push(table_node* new_table) {
    if (is_full()) {
        printf("TABLE STACK FULL, ABORTING PUSH");
        return;
    }
    top_index++;
    stack[top_index] = new_table;
    return;
};

table_node* pop() {
    if (is_empty()) {
        printf("UNDERFLOW IN TABLE STACK, ABORTING POP");
        return NULL;
    }

    table_node* table = stack[top_index];
    top_index--;
    return table;
};

table_node* peek() {
    if (is_empty()){
        printf("TRYING TO ACCESS EMPTY TABLE STACK");
        return NULL;
    }
    return stack[top_index];
};

bool is_empty() {
    return top_index == -1;
};

bool is_full() {
    return top_index == MAX_STACK_SIZE - 1;
};