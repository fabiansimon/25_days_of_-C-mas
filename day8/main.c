#include <stdio.h>
#include <stdbool.h>

#include "../common/hashset.c"

#define MAX_LINES 200
#define MAX_LEN 20

typedef struct State {
    int y, x, dir
} State;

const int directions[8][2] = {{0, -1}, {-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}};

bool in_bounds(int y, int x, char matrix[MAX_LINES][MAX_LEN]) {
    return !(y < 0 || x < 0 || y >= MAX_LINES || y >= MAX_LEN || matrix[y][x] == '\0');
}

int count_antennas(char curr, char matrix[MAX_LINES][MAX_LEN], int line_count) {
    int occs[100][2] = {0};
    int idx = 0;
    for (int y = 0; y < line_count; y++) {
        for (int x = 0; x < MAX_LEN && matrix[y][x] != '\0'; ++x) {
            if (matrix[y][x] == curr)
                occs[idx][0] = y;
                occs[idx][1] = x;
                idx++;
        }
    }
}

int main() {
    FILE *file = fopen("inputs/day8_small.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    char matrix[MAX_LINES][MAX_LEN];
    int line_count = 0; 
    while (fgets(matrix[line_count], MAX_LEN, file) != NULL) {
        line_count++;
    }

    int res = 0;

    HashSet occs__done; 
    for (size_t y = 0; y < line_count; y++) {
        for (size_t x = 0; x < MAX_LEN && matrix[y][x] != '\0'; ++x) {
            char curr = matrix[y][x];
            insert_set(&occs__done, curr);
            if (curr != '.')
                res += count_antennas(curr, matrix, line_count);
        }
    }

    printf("Result for Part I:\t%d", res);
    return 0;
}