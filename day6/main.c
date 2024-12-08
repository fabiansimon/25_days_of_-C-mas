#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LEN 300
#define MAX_LINES 129

const int directions[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

bool in_bounds(int y, int x, char lines[MAX_LINES][MAX_LEN]) {
    return y >= 0 && y < MAX_LINES && x >= 0 && x < MAX_LEN &&
           (lines[y][x] == '.' || lines[y][x] == '#' || lines[y][x] == '^');
}

bool infinite_loop(int y, int x, char lines[MAX_LINES][MAX_LEN], int direction) {
    bool visited[MAX_LINES][MAX_LEN][4] = {0};

    while (true) {
        if (!in_bounds(y, x, lines)) {
            return false;
        }

        if (visited[y][x][direction]) {
            return true; // Loop detected
        }

        visited[y][x][direction] = true;

        int new_y = y + directions[direction][0];
        int new_x = x + directions[direction][1];

        if (in_bounds(new_y, new_x, lines) && lines[new_y][new_x] == '#') {
            direction = (direction + 1) % 4; // Turn right
        } else {
            y = new_y;
            x = new_x;
        }
    }
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

    char temp = lines[new_y][new_x];
    lines[new_y][new_x] = '#';

    if (infinite_loop(y, x, lines, direction)) {
        printf("FOUND ONE\n");
        lines[new_y][new_x] = temp;
    }

    int result = find_trail(new_y, new_x, lines, direction, curr, visited);
    lines[new_y][new_x] = temp; 

    return result;
}

int main() {
    FILE *file = fopen("./inputs/day6_small.txt", "r");
    if (file == NULL) {
        printf("Error when opening file\n");
        return 1;
    }

    // Initialize map and visited array
    bool visited[MAX_LINES][MAX_LEN] = {0};
    char lines[MAX_LINES][MAX_LEN] = {0};
    int line_count = 0;

    // Read input file into the map
    while (line_count < MAX_LINES && fgets(lines[line_count], MAX_LEN, file) != NULL) {
        line_count++;
    }
    fclose(file);

    // Find the guard's starting position and compute the result
    int result = 0;
    for (int y = 0; y < line_count; ++y) {
        for (int x = 0; x < MAX_LEN && lines[y][x] != '\0' && lines[y][x] != '\n'; ++x) {
            if (lines[y][x] == '^') { // Guard's starting position
                result = find_trail(y, x, lines, 0, 0, visited);
                break;
            }
        }
        if (result != 0) {
            break;
        }
    }

    // Print the result
    printf("Result for Part I:\t%d\n", result);
    return 0;
}
