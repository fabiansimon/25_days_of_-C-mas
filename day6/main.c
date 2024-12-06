#include <stdio.h>
#include <stdbool.h>

#define MAX_LEN 300
#define MAX_LINES 129

const int directions[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

void print_arr(char lines[MAX_LINES][MAX_LEN], int _y, int _x) {
    printf("\n");
    printf("\n");
    for (int y = 0; y < MAX_LINES && lines[y][0] != '\0'; ++y) {
        for (int x = 0; x < MAX_LEN && lines[y][x] != '\0' && lines[y][x] != '\n'; ++x) {
            char curr = lines[y][x];
            if (_y == y && _x == x) {
                printf("^");
            } else {
                printf("%c", curr);
            }
        }
        printf("\n");
    }
    printf("\n");
    printf("\n");
}

bool in_bounds(int y, int x, char lines[MAX_LINES][MAX_LEN]) {
    return y >= 0 && y < MAX_LINES && x >= 0 && x < MAX_LEN &&
           (lines[y][x] == '.' || lines[y][x] == '#' || lines[y][x] == '^');
}

int find_trail(int y, int x, char lines[MAX_LINES][MAX_LEN], int direction, int curr, bool visited[MAX_LINES][MAX_LEN]) {
    if (!in_bounds(y, x, lines)) {
        return curr;
    }

    if (!visited[y][x]) {
        curr++;
        visited[y][x] = true;
    }

    int new_y = y + directions[direction][0];
    int new_x = x + directions[direction][1];

    if (in_bounds(new_y, new_x, lines) && lines[new_y][new_x] == '#') {
        direction = (direction + 1) % 4;
        new_y = y + directions[direction][0];
        new_x = x + directions[direction][1];
    }

    return find_trail(new_y, new_x, lines, direction, curr, visited);
}

int main() {
    FILE *file = fopen("./inputs/day6.txt", "r");
    if (file == NULL) {
        printf("Error when opening file");
        return 1;
    }

    bool visited[MAX_LINES][MAX_LEN] = {0};
    char lines[MAX_LINES][MAX_LEN] = {0};
    int line_count = 0;

    // Read lines from the file
    while (line_count < MAX_LINES && fgets(lines[line_count], MAX_LEN, file) != NULL) {
        line_count++;
    }
    fclose(file);

    int res = 0;
    for (int y = 0; y < line_count; ++y) {
        for (int x = 0; x < MAX_LEN && lines[y][x] != '\0' && lines[y][x] != '\n'; ++x) {
            char curr = lines[y][x];
            // printf("%c", curr);
            if (curr == '^') {
                res += find_trail(y, x, lines, 0, 0, visited);
                break;
            }
        }
        printf("\n");
        if (res != 0)
            break;
    }

    printf("Result for Part I:\t%d", res);
    return 0;
}
