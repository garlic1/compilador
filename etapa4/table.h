#include "semantics.h"

typedef struct pointer_table_node_t pointer_table_node;
struct pointer_table_node_t {
    int key;
    node_content node_content;
    pointer_table_node* next_node;
};

pointer_table_node* cria_lista(void);

pointer_table_node* insere(
    pointer_table_node* new_nodo,
    int row,
    bool is_literal,
    bool is_identifier,
    bool is_function,
    char* type,
    char* valor_token
);

pointer_table_node* free_table(pointer_table_node* pointer_lista);