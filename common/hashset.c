#include <stdio.h>
#include <stdlib.h>
#include "hashset.h"

// Hash function
static int hash(int key) {
    // Could definitely be improved 
    return key % TABLE_SIZE;
}

// Insert a key into the hashset
void insert_set(HashSet* set, int key) {
    int index = hash(key);

    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Error: Memory allocation failed\n");
        return;
    }

    newNode->key = key;
    newNode->next = NULL;

    // If no collision
    if (set->table[index] == NULL) {
        set->table[index] = newNode;
    } else {
        Node *temp = set->table[index];
        while (temp->next != NULL) {
            // If key already exists, free newNode and return
            if (temp->key == key) {
                free(newNode);
                return;
            }
            temp = temp->next;
        }

        // Check the last node for the same key
        if (temp->key == key) {
            free(newNode);
        } else {
            temp->next = newNode;
        }
    }
}

void populate_items(HashSet* set, int* arr, int size) {
    int count = 0; 

    for (int i = 0; i < TABLE_SIZE; ++i) {
        Node* temp = set->table[i];
        while (temp != NULL) {
            if (count >= size) {
                return;
            }

            arr[count++] = temp->key;
            temp = temp->next;     
        }
    }

    while (count < size) {
        arr[count++] = 0;
    }
}

int search_set(HashSet* set, int key) {
    int index = hash(key);

    Node *temp = set->table[index];
    while (temp != NULL) {
        if (temp->key == key) {
            return 1; // Key found
        }
        temp = temp->next;
    }

    return 0; // Key not found
}

void delete_set(HashSet* set, int key) {
    int index = hash(key);

    Node *temp = set->table[index];
    Node *prev = NULL;

    while (temp != NULL && temp->key != key) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Key %d not found.\n", key);
        return;
    }

    // Remove the node from the list
    if (prev == NULL) {
        set->table[index] = temp->next;
    } else {
        prev->next = temp->next;
    }

    free(temp);
    // printf("Key %d deleted.\n", key);
}

void erase_set(HashSet* set) {
   for (int i = 0; i < TABLE_SIZE; ++i) {
        Node* temp = set->table[i];
        while (temp != NULL) {
            Node* to_free = temp; 
            temp = temp->next;    
            free(to_free);       
        }
        set->table[i] = NULL; 
    } 
}

int size_set(HashSet* set) {
    int count = 0;

    // Iterate through all buckets in the hash table
    for (size_t i = 0; i < TABLE_SIZE; ++i) {
        Node* temp = set->table[i];
        while (temp != NULL) {
            count++;
            temp = temp->next;
        }
    }

    return count;
}

// Print the contents of the hashset
void print_set(HashSet* set, const char* name) {
    if (name != NULL) {
        printf("Set %s\n", name);
    }
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (set->table[i] == NULL) continue;
        printf("Index %d: ", i);
        Node* temp = set->table[i];
        while (temp != NULL) {
            printf("(%d) -> ", temp->key);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}
