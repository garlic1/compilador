#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "ast.h"

data *new_data(const char *newlabel, int newNumberLine, int newTipo)
{
  data *dados = NULL;
  dados = calloc(1, sizeof(data));
  if (dados != NULL){
    dados->tipo = newTipo;
    dados->line_number = newNumberLine;
    dados->valor_token = strdup(newlabel);
  }
  return dados;  
}

asd_tree *asd_new(data *dados)
{
  asd_tree *ret = NULL;  
  ret = calloc(1, sizeof(asd_tree));
  if (ret != NULL){
    ret->token = *dados;
    ret->number_of_children = 0;
    ret->children = NULL;
  }
  return ret;
}

void asd_add_child(asd_tree *tree, asd_tree *child)
{
  if (tree != NULL && child != NULL){
    tree->number_of_children++;
    tree->children = realloc(tree->children, tree->number_of_children * sizeof(asd_tree*));
    tree->children[tree->number_of_children-1] = child;
  }else{
    if(child == NULL)
    {
      return;
    }else{
      printf("Erro: %s recebeu parâmetro tree = %p / %p.\n", __FUNCTION__, tree, child);
    }    
  }
}

void asd_add_child_end(asd_tree *tree, asd_tree *child)
{
  if (tree != NULL && child != NULL){
    for(int i = 0; i < tree->number_of_children; i++)
    {
      if( strcmp(tree->children[i]->token.valor_token, "<=") == 0 )
      {
        asd_add_child_end(tree->children[i], child);
        return;
      }
    }
    tree->number_of_children++;
    tree->children = realloc(tree->children, tree->number_of_children * sizeof(asd_tree*));
    tree->children[tree->number_of_children-1] = child;
  }else{
    if(child == NULL)
    {
      return;
    }else{
      printf("Erro: %s recebeu parâmetro tree = %p / %p.\n", __FUNCTION__, tree, child);
    }    
  }  
}

void asd_free(asd_tree *tree)
{
  if (tree != NULL){
    int i;
    for (i = 0; i < tree->number_of_children; i++){
      asd_free(tree->children[i]);
    }
    free(tree->children);
    free(tree->token.valor_token);
    free(&tree->token);
    free(tree);
  }else{
    printf("Erro: %s recebeu parâmetro tree = %p.\n", __FUNCTION__, tree);
  }
}