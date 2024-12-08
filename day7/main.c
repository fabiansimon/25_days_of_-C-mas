#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_LINES 1000
#define MAX_LEN 100
#define MAX_NUMBERS 20

long conc_number(long a, long b) {
    long pow = 10;
    while (b >= pow) {
        pow *= 10;
    }
    return a * pow + b; 
}

int arr_len(const long equation[MAX_NUMBERS]) {
    int l = 0;
    while (l < MAX_NUMBERS && equation[l] != -1) { 
        l++;
    }
    return l;
}

void populate_variants(char *arr, int size) {
    const char operations[] = {'*', '+', '|'};
    int num_operations = 3; 
    int num_combinations = pow(num_operations, size);

    for (int i = 0; i < num_combinations; i++) { 
        for (int j = 0; j < size; j++) {
            arr[i * size + j] = operations[(i / (int)pow(num_operations, j)) % num_operations];
        }
    }
}

long solvable(const long target, const long equation[MAX_NUMBERS]) {
    int n = arr_len(equation); 
    int num_combinations = pow(3, n - 1);
    char op_variants[num_combinations * (n - 1)];

    populate_variants(op_variants, n - 1);

    for (int i = 0; i < num_combinations; i++) {
        long curr = equation[0];
        for (int j = 0; j < n - 1; j++) {
            char op = op_variants[i * (n - 1) + j];
            long b = equation[j + 1];
            if (op == '*') {
                curr *= b;
            } else if (op == '|') {
                curr = conc_number(curr, b);
            } else {
                curr += b;
            }
        }

        if (curr == target) {
            // printf("Found one:\ttarget:\t%ld\n", target);
            return target;
        }
    }

    return 0;
}

int main() {
    FILE *file = fopen("inputs/day7.txt", "r");
    if (file == NULL) {
        perror("File could not be opened.\n");
        return 1;
    }

    long results[MAX_LINES] = {0};
    long equations[MAX_LINES][MAX_NUMBERS] = {0}; 
    int line_count = 0;

    char buffer[MAX_LEN];
    while (fgets(buffer, sizeof(buffer), file) != NULL && line_count < MAX_LINES) {
        char *colon = strchr(buffer, ':');
        if (colon == NULL) {
            printf("Invalid format.\n");
            continue;
        }

        *colon = '\0';
        results[line_count] = strtol(buffer, NULL, 10); // Use strtol for long parsing

        char *equation = colon + 1;
        char *token = strtok(equation, " \n");
        int nr_count = 0; 

        while (token != NULL && nr_count < MAX_NUMBERS) {
            equations[line_count][nr_count++] = strtol(token, NULL, 10); // Use strtol for long parsing
            token = strtok(NULL, " \n");
        }

        equations[line_count][nr_count] = -1; // Mark end of equation with -1
        line_count++;
    }

    fclose(file);

    long res = 0; 
    for (int i = 0; i < line_count; ++i) {
        res += solvable(results[i], equations[i]);
    }

    printf("Result for Part II:\t%ld\n", res);

    return 0;
}
