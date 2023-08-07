#ifndef _ARVORE_H_
#define _ARVORE_H_

#define CARACTERE_ESPECIAL 1
#define PALAVRA_RESERVADA  2
#define OPERADOR_COMPOSTO  3
#define IDENTIFICADOR      4
#define LITERAL            5

#define INTEIRO 1
#define PONTOFLUTUANTE 2
#define BOOLEANO 3

typedef struct data_t
{
  int tipo;
  int tipo_inferido;
  int line_number;
  char *valor_token; 

} data;


typedef struct asd_tree_t {  
  data token;
  int number_of_children;
  struct asd_tree_t **children;
} asd_tree;

/*
 * Função new_data, cria uma struct com os dados.
 */
data *new_data(const char *newlabel, int newNumberLine, int newTipo);
/*
 * Função new_data, cria uma struct com os dados.
 */
data *new_data_typed(const char *newlabel, int newNumberLine, int newTipo, int newTipo_Inferido);
/*
 * Função setType, altera um tipo de um nó.
 */
void setType(data *dados, int newTipo_Inferido);
/*
 * Função asd_new, cria um nó sem filhos com o label informado.
 */
asd_tree *asd_new(data *dados);
/*
 * Função asd_new, cria um nó sem filhos com o label informado.
 */
asd_tree *asd_new_call(data *dados);
/*
 * Função asd_add_child, adiciona child como filho de tree.
 */
void asd_add_child(asd_tree *tree, asd_tree *child);
/*
 * Função asd_add_child_end, adiciona child como filho do ultimo filho.
 */
void asd_add_child_end(asd_tree *tree, asd_tree *child);
/*
 * Função asd_tree, libera recursivamente o nó e seus filhos.
 */
void asd_free(asd_tree *tree);

#endif