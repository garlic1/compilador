#ifndef HASH_HEADER
#define HASH_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 997

#define SYMBOL_VARIABLE 6
#define SYMBOL_LABEL 7

typedef struct hash_node {
    int type;
    char *value;
    struct hash_node *next_node;
} hash_node;

void init_table(void);
int hash(char *entry);
hash_node* insert_node(char *entry, int type);
hash_node* get_node(char *entry);
hash_node* delete_table(void);
void print_table(void);
hash_node* create_temp(void);
hash_node* create_label(void);

#endif