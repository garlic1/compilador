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
    dados->precedencia = NULL;
    dados->line_number = newNumberLine;
    dados->valor_token = strdup(newlabel);
  }
  return dados;  
}

ast_tree *ast_new(data *dados)
{
  ast_tree *ret = NULL;  
  ret = calloc(1, sizeof(ast_tree));
  if (ret != NULL){
    ret->token = *dados;
    ret->number_of_children = 0;
    ret->children = NULL;
  }
  return ret;
}

ast_tree *ast_new_call(data *dados)
{
  ast_tree *ret = NULL;  
  ret = calloc(1, sizeof(ast_tree));
  if (ret != NULL){  
    char *newToken = calloc(1, sizeof(dados->valor_token) + 5*sizeof(char));
    strcpy(newToken, "call ");
    strcat(newToken, dados->valor_token);
    dados->valor_token = newToken;    
    ret->token = *dados;
    ret->number_of_children = 0;
    ret->children = NULL;
  }
  return ret;
}

ast_tree *ast_new_parenteses()
{
  data *dados = NULL;
  dados = calloc(1, sizeof(data));
  if (dados != NULL){
    dados->tipo = PALAVRA_RESERVADA;
    dados->precedencia = (int*)malloc(sizeof(int));
    *(dados->precedencia) = 0;
    dados->line_number = -1;
    dados->valor_token = strdup("par");
  }

  ast_tree *ret = NULL;  
  ret = calloc(1, sizeof(ast_tree));
  if (ret != NULL){
    ret->token = *dados;
    ret->number_of_children = 0;
    ret->children = NULL;
  }

  return ret;
}

void ast_add_child(ast_tree *tree, ast_tree *child)
{
  if (tree != NULL && child != NULL){
    tree->number_of_children++;
    tree->children = realloc(tree->children, tree->number_of_children * sizeof(ast_tree*));
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

void ast_add_child_first(ast_tree *tree, ast_tree *child)
{
  if (tree != NULL && child != NULL){
    tree->number_of_children++;
    tree->children = realloc(tree->children, tree->number_of_children * sizeof(ast_tree*));
    // tree->children[tree->number_of_children-1] = child;
    ast_tree *shift_child = NULL;
    for(int i = 0; i < tree->number_of_children; i++)
    {
      shift_child = tree->children[i];
      tree->children[i] = child;
      child = shift_child;
    }
  }else{
    if(child == NULL)
    {
      return;
    }else{
      printf("Erro: %s recebeu parâmetro tree = %p / %p.\n", __FUNCTION__, tree, child);
    }    
  }
}

void ast_add_child_end(ast_tree *tree, ast_tree *child)
{
  if (tree != NULL && child != NULL){
    for(int i = 0; i < tree->number_of_children; i++)
    {
      if( strcmp(tree->children[i]->token.valor_token, "<=") == 0 )
      {
        ast_add_child_end(tree->children[i], child);
        return;
      }
    }
    tree->number_of_children++;
    tree->children = realloc(tree->children, tree->number_of_children * sizeof(ast_tree*));
    tree->children[tree->number_of_children-1] = child;
  }else{
    if(child == NULL || tree == NULL)
    {
      return;
    }else{
      printf("Erro: %s recebeu parâmetro tree = %p / %p.\n", __FUNCTION__, tree, child);
    }    
  }  
}

ast_tree * parentheses_adjust(ast_tree *tree)
{
  ast_tree *p = tree;
  tree = tree->children[0];
  ast_node_free(p);
  return ast_adjust_expr(tree);
}

ast_tree * unary_adjust(ast_tree *tree)
{
  fprintf(stderr, "Entrou unário\nnode %s \t precedência %d\n---\n", tree->token.valor_token, *(tree->token.precedencia));

  //cria um ponteiro para iterar
  ast_tree *p = tree;
  
  //vai até o ultimo operador unário já que não precisa trocar a
  //que os calculos são aplicados
  while( p->children[0]->token.precedencia != NULL && 
          *(p->children[0]->token.precedencia) == 1 )
  {
    p = p->children[0];      
  }

  //se no final tiver uma operação binária tem que ajustar
  //desde a raíz
  if(p->children[0]->number_of_children == 2)
  {
    ast_tree *n = p->children[0];
    p->children[0] = n->children[0];
    n->children[0] = tree;
    tree = n;
     
  }

  if(p->children[0]->number_of_children == 1 &&
      *(p->children[0]->token.precedencia) == 0)
  {    
    p->children[0] = ast_adjust_expr(p->children[0]);     
  }
  
  return tree;
}

//Ao entrar é necessário que a arvore possua dois filhos
ast_tree * binary_adjust(ast_tree *tree)
{  
  fprintf(stderr, "Entrou binário\nnode %s \t precedência %d\n", tree->token.valor_token, *(tree->token.precedencia));
  // fprintf(stderr, "childrens's [%s,%s]\n---\n", tree->children[0]->token.valor_token, tree->children[1]->token.valor_token);


  //cria um ponteiro para iterar e outro para seguir um passo atrás
  ast_tree *p_last = tree;  
  ast_tree *p = tree->children[1];
  ast_tree *mark = NULL;

  if(p->token.precedencia == NULL &&
      tree->children[0]->number_of_children == 1 &&
         *(tree->children[0]->token.precedencia) == 0)
  {
    tree->children[0] = ast_adjust_expr(tree->children[0]);
  }

  while(p->token.precedencia != NULL)
  {
    if(p_last->children[0]->number_of_children == 1 &&
         *(p_last->children[0]->token.precedencia) == 0)
    {
      p_last->children[0] = ast_adjust_expr(p_last->children[0]);
    }
    if(*p->token.precedencia == 0)
    {
      p_last->children[1] = ast_adjust_expr(p->children[0]);
      ast_node_free(p);
      break;
    }

    if(*p->token.precedencia == 1)
    {
      p = unary_adjust(p);
      p_last->children[1] = p;      
      if(p->number_of_children < 2) break;      
    }    

    if(*p_last->token.precedencia < *p->token.precedencia)
    {
      p_last->children[1] = p->children[0];      
      p->children[0] = tree;
      tree = p;
      p_last = tree;
      p = tree->children[1];
      mark = NULL;
      continue;
    }

    if(*p_last->token.precedencia == *p->token.precedencia)
    {
      p_last->children[1] = p->children[0];      
      p->children[0] = p_last;
      if(mark != NULL)
      {
        mark->children[1] = p;
      }else
      {
        tree = p;
      }
      p_last = p;
      p = p->children[1];
      continue;
    }

    mark = p_last;
    p_last = p;
    p = p->children[1];
  }

  return tree;
}

ast_tree * ast_adjust_expr(ast_tree *tree)
{
  //verificações
  //fprintf(stderr, "Entrou adjust_expr\nnode %s \t precedência %d\n---\n", tree->token.valor_token, *(tree->token.precedencia));
  //if(tree->number_of_children == 1) fprintf(stderr, "Entrou adjust_expr\nchildren [%s]\n---\n", tree->children[0]->token.valor_token);
  //if(tree->number_of_children == 2) fprintf(stderr, "Entrou adjust_expr\nchildrens's [%s,%s]\n---\n", tree->children[0]->token.valor_token, tree->children[1]->token.valor_token);

  if(tree == NULL) return tree;
  if(tree->children == 0) return tree;
  
  switch (*(tree->token.precedencia))
  {
    case 0: return parentheses_adjust(tree);            

    case 1: tree = unary_adjust(tree);
            if(tree->number_of_children == 2) tree = binary_adjust(tree);
            break;

    default: tree = binary_adjust(tree);
             break;
  }

  return tree;
}

void ast_free(ast_tree *tree)
{
  if (tree != NULL){
    int i;
    for (i = 0; i < tree->number_of_children; i++){
      ast_free(tree->children[i]);
    }
    free(tree->children);
    free(tree->token.valor_token);
    free(tree->token.precedencia);
    free(&tree->token);
    free(tree);
  }else{
    printf("Erro: %s recebeu parâmetro tree = %p.\n", __FUNCTION__, tree);
  }
}

void ast_node_free(ast_tree *tree)
{
  if (tree != NULL){
    free(tree->children);
    free(tree->token.valor_token);
    free(tree->token.precedencia);
    free(&tree->token);
  }else{
    printf("Erro: %s recebeu parâmetro tree = %p.\n", __FUNCTION__, tree);
  }
}