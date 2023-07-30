#include <stdbool.h>
#include <stdlib.h>

#define ERR_UNDECLARED 10 //2.2
#define ERR_DECLARED 11 //2.2
#define ERR_VARIABLE 20 //2.3
#define ERR_FUNCTION 21 //2.3

typedef struct node_location_t {
    int row;
    int column;
} node_location;

typedef struct node_nature_t {
    bool is_literal;
    bool is_identifier;
    bool is_function;
} node_nature;

typedef struct node_content_t {
    node_location node_location;
    node_nature node_nature;
    char* type;
    char* valor_token;
} node_content;

typedef struct table_node_t {
    int key;
    node_content node_content;
    table_node *next_node;
} table_node;

table_node* cria_lista(void);

table_node* insere_inicio();
table_node* insere_fim();
table_node* insere_meio();

table_node* free_table();