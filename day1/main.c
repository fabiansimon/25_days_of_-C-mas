#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../common/hashtable.h"

#define MAX_LINES 1002
#define MAX_LEN 100

int comp(const void* a, const void* b) {
    return strcmp((const char *)a, (const char *)b);
}

int main() {
    char col_a[MAX_LINES][MAX_LEN];
    char col_b[MAX_LINES][MAX_LEN];

    const char *input_file = "./inputs/day1.txt";
    FILE *file = fopen(input_file, "r");
    if (file == NULL) {
        perror("Error opening file.");
        return 1;
    }

    char line[MAX_LEN];
    int line_count = 0; 

    while (fgets(line, sizeof(line), file) != NULL && line_count < MAX_LINES) {
        if (sscanf(line, "%s %s", col_a[line_count], col_b[line_count]) == 2) {
            line_count++;
        }
    }

    if (ferror(file)) {
        printf("Error reading file");
    }

    fclose(file);

    // Sort the cols
    qsort(col_a, line_count, sizeof(col_a[0]), comp);
    qsort(col_b, line_count, sizeof(col_b[0]), comp);

    int distance = 0; 
    for (int i = 0; i < line_count; ++i)
    {
        const int a = atoi(col_a[i]);
        const int b = atoi(col_b[i]);
        distance += abs(a - b);
    }

    // printf("Column A\tColumn B\n");
    // for (int i = 0; i < line_count; i++) {
    //     printf("%s\t\t%s\n", col_a[i], col_b[i]);
    // }

    for (int i = 0; i < line_count; ++i) {
        const int a = atoi(col_a[i]);
        int occ = search(a);
        if (occ == -1) {
            insert(a, 1);
        } else {
            insert(a, occ + 1);
        }
    }

    print();

    // First star
    printf("Total Distance: %d\n", distance);

    // int similarity = 0; 
    // for (int i = 0; i < line_count; ++i)
    // {
    //     const int a = atoi(col_a[i]);
    //     int occ = 0; 

    //     for (int j = 0; j < line_count; ++j)
    //     {
    //         if (a == atoi(col_b[j])) {
    //             occ++;
    //         }
    //     }

    //     similarity += a * occ;
    // }

    int similarity = 0; 
    for (int i = 0; i < line_count; ++i)
    {
        const int a = atoi(col_a[i]);
        int occs = search(a);
        if (occs != -1) {
            similarity += a * occs;
        }
    }

    // Second star
    printf("Similarity Score: %d\n", similarity);  
    return 0;
}