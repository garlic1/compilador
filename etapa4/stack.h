#include "semantics.h"

#define MAX_STACK_SIZE 1000

int top_index = -1;
pointer_table_node* stack[MAX_STACK_SIZE];

void push(pointer_table_node* new_table);
pointer_table_node* pop();
pointer_table_node* peek();
bool is_empty();
bool is_full();