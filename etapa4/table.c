#include "semantics.h"
#include "table.h"
#include "ast.h"

pointer_table_node *pointer_lista;

pointer_table_node* cria_lista() {
    return NULL;
}

pointer_table_node* insere_inicio(
    pointer_table_node* pointer_lista,
    int row,
    int column,
    bool is_literal,
    bool is_identifier,
    bool is_function,
    char* type,
    char* valor_token
) {
    pointer_table_node* new_nodo;
    new_nodo = (pointer_table_node*) malloc(sizeof(pointer_table_node));
    
    new_nodo -> node_content.node_location.row = row;
    new_nodo -> node_content.node_location.column = column;
    new_nodo -> node_content.node_nature.is_literal = is_literal;
    new_nodo -> node_content.node_nature.is_identifier=is_identifier;
    new_nodo -> node_content.node_nature.is_function=is_function;
    new_nodo -> node_content.type = type;
    new_nodo -> node_content.valor_token = valor_token;
    new_nodo -> next_node=NULL;

    pointer_lista = new_nodo;

    return pointer_lista;
}

pointer_table_node* free_table(pointer_table_node* pointer_lista){
    pointer_table_node *aux;

    while(pointer_lista != NULL) {
        aux = pointer_lista;
        pointer_lista = pointer_lista->next_node;
        free(aux);
    }

    return NULL;
};