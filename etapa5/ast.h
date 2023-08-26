#ifndef _ARVORE_H_
#define _ARVORE_H_

#define CARACTERE_ESPECIAL 1
#define PALAVRA_RESERVADA  2
#define OPERADOR_COMPOSTO  3
#define IDENTIFICADOR      4
#define LITERAL            5

typedef struct data_t
{
  int tipo;
  int *precedencia;
  int line_number;
  char *valor_token;

} data;


typedef struct ast_tree_t {  
  data token;
  int number_of_children;
  struct ast_tree_t **children;
} ast_tree;

/*
 * Função new_data, cria uma struct com os dados.
 */
data *new_data(const char *newlabel, int newNumberLine, int tipo);
/*
 * Função ast_new, cria um nó sem filhos com o label informado.
 */
ast_tree *ast_new(data *dados);
/*
 * Função ast_new, cria um nó sem filhos com o label informado.
 */
ast_tree *ast_new_call(data *dados);
/*
 * Função cria um nodo para reconhecer o parenteses.
 */
ast_tree *ast_new_parenteses();
/*
 * Função ast_add_child, adiciona child como filho de tree.
 */
void ast_add_child(ast_tree *tree, ast_tree *child);
/*
 * Função ast_add_child_first, adiciona child como primeiro filho.
 */
void ast_add_child_first(ast_tree *tree, ast_tree *child);
/*
 * Função ast_add_child_end, adiciona child como filho do ultimo filho.
 */
void ast_add_child_end(ast_tree *tree, ast_tree *child);
/*
 * Função ast_adjust_expr, ajusta as prioridades das expressoes.
 */
ast_tree *ast_adjust_expr(ast_tree *tree);
/*
 * Função ast_tree, libera recursivamente o nó e seus filhos.
 */
void ast_free(ast_tree *tree);

void ast_node_free(ast_tree *tree);

#endif