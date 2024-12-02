#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define MAX_LINES 1001
#define MAX_LEN 20

// Function to check if the report is strictly increasing or decreasing
bool is_incr(const int row[]) {
    int first = row[0];
    int i = 0;
    while (row[i] != 0) {
        i++;
    }
    int last = row[i - 1];
    return first < last;
}

// Function to check if the report is safe
bool is_safe(const int row[], bool increasing) {
    int prev = row[0];
    for (int i = 1; row[i] != 0; ++i) {
        int curr = row[i];

        // Check distance
        if (abs(prev - curr) > 3) {
            return false;
        }

        // Check trend consistency
        if ((increasing && curr <= prev) || (!increasing && curr >= prev)) {
            return false;
        }

        prev = curr;
    }
    return true;
}

int main() {
    int reports[MAX_LINES][MAX_LEN] = {0};
    const char *input_file = "./inputs/day2.txt";
    FILE *file = fopen(input_file, "r");
    if (file == NULL) {
        perror("File not found.");
        return 1;
    }

    char line[256];
    int line_count = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        int col_count = 0;
        char *ptr = line;

        while (sscanf(ptr, "%d", &reports[line_count][col_count]) == 1) {
            col_count++;
            while (*ptr != ' ' && *ptr != '\0') ptr++;
            while (*ptr == ' ') ptr++;
        }

        if (col_count > 0) {
            line_count++;
        }

        if (line_count >= MAX_LINES) break;
    }

    fclose(file);

    // Part I
    int res = 0;
    for (int i = 0; i < line_count; ++i) {
        bool increasing = is_incr(reports[i]);
        if (is_safe(reports[i], increasing)) {
            res++;
        }
    }

    printf("Safe reports (Part I): %d\n", res);

    // Part II
    res = 0;

    for (int i = 0; i < line_count; ++i) {
        bool increasing = is_incr(reports[i]);

        if (is_safe(reports[i], increasing)) {
            res++;
            continue;
        }

        for (int j = 0; reports[i][j] != 0; ++j) {
            int temp[MAX_LEN] = {0};
            int k = 0;

            for (int l = 0; reports[i][l] != 0; ++l) {
                if (l != j) {
                    temp[k++] = reports[i][l];
                }
            }

            if (is_safe(temp, increasing)) {
                res++;
                break;
            }
        }
    }

    printf("Safe reports (Part II): %d\n", res);

    return 0;
}


