#include "hash_table.h"

node* Table[SIZE][1];

void init(void)
{
    int i;
    for(i=0; i<SIZE; ++i)
    {
        Table[i][0]=NULL;
    }
}

int address(char *text)
{
    int address = 1;
    int i;
    for(i=0; i<strlen(text); ++i) address = (address * text[i]) % SIZE + 1;

    return address-1;
}

node *find(char *text)
{
    node *node;
    int address = hashAddress(text);
    for( node=Table[address][0]; node != NULL; node=node->next)
    {
        if(strcmp(node->token, text)==0) return node;
    }
    return NULL;
}

node *insert(char *text, int type)
{
    node *newnode;
    int address = hashAddress(text);

    if((newnode = hashFind(text)) != NULL)
        return newnode;
    
    newnode = (node*)calloc(1, sizeof(node));
    newnode->type = type;
    newnode->token = (char*)calloc(strlen(text)+1, sizeof(char));
    newnode->parameters = NULL;
    strcpy(newnode->token, text);
    newnode->next = Table[address];
    Table[address][0] = newnode;
    return newnode;
}

node *insertFun(char *text, int type, node *param)
{
    node *newnode;
    int address = hashAddress(text);

    if((newnode = hashFind(text)) != NULL)
        return newnode;
    
    newnode = (node*)calloc(1, sizeof(node));
    newnode->type = type;
    newnode->token = strdup(newnode->token, text);
    newnode->parameters = param;
    newnode->next = Table[address][0];
    Table[address][0] = newnode;
    return newnode;
}

void print(void)
{
    int i;
    node *node;
    for(i=0;i<SIZE;++i)
    {
        for(node=Table[i][0]; node; node=node->next)
        {
            printf("Tabela[%d][0] = %s\n", i,node->token);
        }
    }
}