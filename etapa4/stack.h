#include "semantics.h"

#define MAX_STACK_SIZE 1000

int top_index = -1;
table_node* stack[MAX_STACK_SIZE];

void push(table_node* new_table);
table_node* pop();
table_node* peek();
bool is_empty();
bool is_full();