#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../common/hashset.h"
#define MAX_LINES 1000
#define MAX_LEN 400

void swap(int a, int b, int line[MAX_LEN]) {
    int temp = line[a];
    line[a] = line[b];
    line[b] = temp;
}

int valid(HashSet* pre, HashSet* post, const int index, const int line[MAX_LEN]) {
    for (size_t i = 0; i < MAX_LEN && line[i] != 0; ++i) {
        if (i == index) continue;

        int target = line[i];
        if (search_set(pre, target) == 0 && search_set(post, target) == 0) {
            continue;
        }

        if (index > i && search_set(pre, target) == 0 || 
            index < i && search_set(post, target) == 0) {
            return i;
        }
    }

    return -1;
}

void reorder_line(HashSet *pre, HashSet* post, int line[MAX_LEN]) {
    bool sorted = false;
    while (!sorted) {
        sorted = true;
        for (size_t i = 0; i < MAX_LEN && line[i] != 0; ++i) {
            int sw = valid(&pre[line[i]], &post[line[i]], i, line);
            if (sw != -1) {
                swap(i, sw, line);
                sorted = false; // If a swap was made, the list is not sorted yet
            }
        }
    }
}

int find_middle(HashSet* pre, HashSet* post, int line[MAX_LEN]) {
    bool sorted = false;
    size_t i;
    while (!sorted) {
        sorted = true;
        for (i = 0; i < MAX_LEN && line[i] != 0; ++i) {
            int curr = line[i];
            int sw = valid(&pre[curr], &post[curr], i, line);
            if (sw != -1) {
                swap(i, sw, line);
                sorted = false; // If a swap was made, the list is not sorted yet
            }
        }
    }

    return line[i/2];
}


void populate_update(const char line[MAX_LEN], int update[MAX_LEN], HashSet* upcoming) {
    int count = 0;

    char line_copy[MAX_LEN];
    strncpy(line_copy, line, MAX_LEN);

    char* token = strtok(line_copy, ",");
    while (token != NULL) {
        int n = atoi(token);
        update[count++] = n;
        insert_set(upcoming, n);
        token = strtok(NULL, ",");
    }

    // Ensure any remaining entries are set to 0
    for (int i = count; i < MAX_LEN; ++i) {
        update[i] = 0;
    }
}

int main() {
    FILE* file = fopen("./inputs/day5.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    HashSet pre[100] = { {NULL} };
    HashSet post[100] = { {NULL} };

    HashSet visited = { {NULL} };
    HashSet upcoming = { {NULL} };

    char line[MAX_LEN];
    int update[MAX_LEN];

    int res = 0, incorrect = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        // Parse "|" lines
        int a, b;
        if (sscanf(line, "%d|%d", &a, &b) == 2) {
            insert_set(&post[a], b);
            insert_set(&pre[b], a);
            continue;
        }

        // Clear state
        erase_set(&upcoming);
        erase_set(&visited);
        memset(update, 0, sizeof(update));

        // Populate `update` array
        populate_update(line, update, &upcoming);

        // Process the first element of `update`
        int curr = update[0];
        if (curr == 0)
            continue;

        int to_check[MAX_LEN], mid = 0, error = 0;
        int total[MAX_LEN];

        for (int i = 0; i < MAX_LEN && update[i] != 0; ++i)
        {
            curr = update[i];

            delete_set(&upcoming, curr);

            // PRE CHECK
            populate_items(&pre[curr], to_check, MAX_LEN);
            for (size_t j = 0; j < MAX_LEN && to_check[j] != 0; ++j) {

                int c = to_check[j];
                
                if (search_set(&visited, c) == 0 && search_set(&upcoming, c) == 0) {
                    continue;
                }

                if (search_set(&visited, c) == 0) {
                    error = 1;
                    break;
                }
            }

            // POST CHECK
            populate_items(&post[curr], to_check, MAX_LEN);
            for (size_t j = 0; j < MAX_LEN && to_check[j] != 0; ++j) {

                int c = to_check[j];
                if (search_set(&visited, c) == 0 && search_set(&upcoming, c) == 0) {
                    continue;
                }

                if (search_set(&upcoming, c) == 0) {
                    error = 1;
                    break;
                }
            }

            if (error == 1) {
                incorrect += find_middle(pre, post, update);
                break;
            }

            // Check if current is the middle
            if (size_set(&visited) == size_set(&upcoming)) {
                mid = curr;
            }

            insert_set(&visited, curr);
        }

        if (error == 0) {
            res += mid;
        }
    }

    fclose(file);

    printf("Answer Part I: %d\n", res);
    printf("Answer Part II: %d\n", incorrect);
    return 0;
}
