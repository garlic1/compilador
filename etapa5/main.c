/*
Função principal para realização da análise sintática.

Este arquivo será posterioremente substituído, não acrescente nada.
*/
#include <stdio.h>
#include "ast.h"
#include "parser.tab.h" //arquivo gerado com bison -d parser.y

extern int yylex_destroy(void);

void *arvore = NULL;

void exporta(asd_tree *tree)
{
  if (tree == NULL){
    return;
  }else{
    printf("%p [label = \"%s\"]\n", tree, tree->token.valor_token);
    //printf("%p [label = \"%s\", %d, %d]\n", tree, tree->token.valor_token, tree->token.line_number, tree->token.tipo);
    for(int i = 0; i < tree->number_of_children; i++)
    {
        printf("%p, %p\n", tree, tree->children[i]);        
        exporta(tree->children[i]);
    }    
  }
}

int main (int argc, char **argv)
{


  int ret = yyparse();
  exporta (arvore);
  yylex_destroy();
  return ret;
}
