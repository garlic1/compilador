#ifndef HASH_HEADER
#define HASH_HEADER

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TABLE_SIZE 997

#define SYMBOL_VARIABLE 6
#define SYMBOL_LABEL 7

typedef struct hash_node {
    int type;
    char *value;
    struct hash_node *next_node;
    int initial_value;
} hash_node;

void init_table(void);
int hash(char *entry);
hash_node* insert_node(char *entry, int type);
hash_node* get_node(char *entry);
hash_node* delete_table(void);
void print_table(void);
hash_node* makeTemp(void);
hash_node* makeLabel(void);
void printAsm(FILE *fout);

#endif