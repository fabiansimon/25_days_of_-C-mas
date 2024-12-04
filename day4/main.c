#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LINES 200
#define MAX_LEN 200

const char match[] = "MAS"; // Chnage to XMAS for Part I
const int match_size = 3; // Change to 4 for Part I
const int directions[8][2] = {
    {0, -1},  // Left
    {-1, -1}, // Top-Left
    {-1, 0},  // Top
    {-1, 1},  // Top-Right
    {0, 1},   // Right
    {1, 1},   // Bottom-Right
    {1, 0},   // Bottom
    {1, -1}   // Bottom-Left
};

const int diag[4][2] = {
    {-1, -1}, // Top-Left
    {-1, 1},  // Top-Right
    {1, 1},   // Bottom-Right
    {1, -1}   // Bottom-Left
};

bool in_bounds(int y, int x, const char matrix[MAX_LINES][MAX_LEN], int line_count) {
    return !(x < 0 || y < 0 || y >= line_count || x >= MAX_LEN || matrix[y][x] == '\0');
}

bool check(int y, int x, const char matrix[MAX_LINES][MAX_LEN], int line_count, char target) {
    if (!in_bounds(y, x, matrix, line_count))
        return false;

    // printf("Comp:\t%c\tTarget:\t%c\n", matrix[y][x], target);
    return matrix[y][x] == target;
}

bool find_match(int y, int x, const char matrix[MAX_LINES][MAX_LEN], int line_count, int dir, int index) {
    if (index == match_size) {
        return 1;
    }

    if (!in_bounds(y, x, matrix, line_count) || matrix[y][x] != match[index]) {
        return 0; 
    }

    return find_match(y + directions[dir][0], x + directions[dir][1], matrix, line_count, dir, index + 1);
}

int main() {
    FILE *file = fopen("./inputs/day4.txt", "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return -1;
    }

    char matrix[MAX_LINES][MAX_LEN];
    int line_count = 0;

    while (fgets(matrix[line_count], MAX_LEN, file) != NULL) {
        matrix[line_count][strcspn(matrix[line_count], "\n")] = '\0'; 
        line_count++;
        if (line_count >= MAX_LINES) {
            break;
        }
    }

    fclose(file);

    int res = 0;

    // Part I
    for (int y = 0; y < line_count; ++y) {
        for (int x = 0; matrix[y][x] != '\0'; ++x) {
            char curr = matrix[y][x];
            if (curr != 'X') continue;
            for (int dir = 0; dir < 8; ++dir) {
                res += find_match(y, x, matrix, line_count, dir, 0);
            }
        }
    }
    printf("Answer to question I:\t%d\n", res);
    res = 0;

    char orientations[4][4] = { {'M', 'S', 'S', 'M'}, 
                                {'M', 'M', 'S', 'S'},  
                                {'S', 'S', 'M', 'M'},
                                {'S', 'M', 'M', 'S'}};


    for (int y = 0; y < line_count; ++y)
    {
        for (int x = 0; matrix[y][x] != '\0'; ++x) {
            char curr = matrix[y][x]; 
            if (curr != 'A') continue;

            for (size_t o = 0; o < 4; ++o) {
                if (check(y - 1, x - 1, matrix, line_count, orientations[o][0]) && // top left
                    check(y - 1, x + 1, matrix, line_count, orientations[o][1]) && // top right
                    check(y + 1, x + 1, matrix, line_count, orientations[o][2]) && // bottom right
                    check(y + 1, x - 1, matrix, line_count, orientations[o][3])) // bottom left
                { 
                    res++;
                    // printf("Found one. @%d\n", o);
                    continue;
                }
            }
        }
    }

    printf("Answer to question II:\t%d\n", res);
    return 0;
}
