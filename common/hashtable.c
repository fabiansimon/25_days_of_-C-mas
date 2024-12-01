#include <stdio.h>
#include <stdlib.h>
#include "hashtable.h"

#define TABLE_SIZE 10000

typedef struct Node {
    int key;
    int value;
    struct Node *next;
} Node;

Node *hash_table[TABLE_SIZE];

int hash(int key) {
    return key % TABLE_SIZE;
}

void insert(int key, int val) {
    int index = hash(key);

    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->key = key;
    newNode->value = val;
    newNode->next = NULL;

    // If not collision 
    if (hash_table[index] == NULL) {
        hash_table[index] = newNode;
    } else {
        Node *temp = hash_table[index];
        while(temp->next != NULL) {

            // If already inside, just override value and free newNode
            if (temp->key == key) {
                temp->value = val;
                free(newNode);
                return;
            }

            temp = temp->next;
        }

        //Check if last node has same key
        if (temp->key == key) {
            temp->value = val;
            free(newNode);
        } else {
            temp->next = newNode;
        }
    }
}

int search(int key) {
    int index = hash(key);

    Node *temp = hash_table[index];
    while (temp) {
        // Check if key matches
        if (temp->key == key) {
            return temp->value;
        }

        temp = temp->next;
    }

    return -1;
}

void delete(int key) {
    int index = hash(key);

    Node *temp = hash_table[index];
    Node *prev = NULL;

    while (temp != NULL && temp->key != key)
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Key %d not found.\n", key);
        return;
    }

    if (prev == NULL) {
        hash_table[index] = temp->next;
    } else {
        prev->next = temp->next;
    }

    free(temp);
    printf("Key %d deleted.\n", key);
}

void print() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("Index %d: ", i);
        Node* temp = hash_table[i];
        while (temp != NULL) {
            printf("(%d, %d) -> ", temp->key, temp->value);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}