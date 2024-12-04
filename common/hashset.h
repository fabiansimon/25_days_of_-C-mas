#ifndef HASHSET_H
#define HASHSET_H

#define TABLE_SIZE 100

typedef struct Node {
    int key;
    struct Node *next;
} Node;

typedef struct HashSet {
    Node *table[TABLE_SIZE];
} HashSet;

void insert_set(HashSet* set, int key);
void delete_set(HashSet* set, int key);
int search_set(HashSet* set, int key);
void populate_items(HashSet *set, int *arr, int size);
void erase_set(HashSet *set);
int size_set(HashSet *set);
void print_set(HashSet* set, const char* name);

#endif