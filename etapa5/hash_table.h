#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 1000

typedef struct node_temp
{
    int type;
    char *token;
    struct node_temp *parameters;
    struct node_temp *next;

} node;

void init(void);
int address(char *text);
node *find(char *text);
node *insert(char *text, int type);
node *insertFun(char *text, int type, node *param);
void print(void);