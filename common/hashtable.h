#ifndef HASHTABLE_H
#define HASHTABLE_H

#define TABLE_SIZE 1000

typedef struct Node {
    int key;
    int value;
    struct Node *next;
} Node;

typedef struct HashMap {
    Node *table[TABLE_SIZE];
} HashMap;

void insert_map(HashMap* map, int key, int val);
void delete_map(HashMap* map, int key);
int search_map(HashMap* map, int key);
void print_map(HashMap* map);

#endif