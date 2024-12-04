#include <stdio.h>
#include <stdlib.h>
#include "hashtable.h"

static int hash(int key) {
    return key % TABLE_SIZE;
}

void insert_map(HashMap* map, int key, int val) {
    int index = hash(key);

    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->key = key;
    newNode->value = val;
    newNode->next = NULL;

    // If not collision 
    if (map->table[index] == NULL) {
        map->table[index] = newNode;
    } else {
        Node *temp = map->table[index];
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

int search_map(HashMap* map, int key) {
    int index = hash(key);

    Node *temp = map->table[index];
    while (temp) {
        // Check if key matches
        if (temp->key == key) {
            return temp->value;
        }

        temp = temp->next;
    }

    return -1;
}

void delete_map(HashMap* map, int key) {
    int index = hash(key);

    Node *temp = map->table[index];
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
        map->table[index] = temp->next;
    } else {
        prev->next = temp->next;
    }

    free(temp);
    printf("Key %d deleted.\n", key);
}

void print_map(HashMap* map) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("Index %d: ", i);
        Node* temp = map->table[i];
        while (temp != NULL) {
            printf("(%d, %d) -> ", temp->key, temp->value);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}