#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_LEN 100000
#define DEBUG false

int int_len(int num) {
    int length = 0;

    if (num == 0) {
        return 1;
    }

    if (num < 0) {
        num = -num;
    }

    while (num > 0) {
        num /= 10;
        length++;
    }

    return length;
}

int number(const char* start) {
    const int max_len = 3;
    size_t i = 0;

    while (isdigit(start[i]) && i < max_len)
        i++;

    if (i == 0 || i > max_len)
        return -1;

    char buffer[4] = {0};
    strncpy(buffer, start, i);
    return atoi(buffer); 
}

int count(const char *input, int *offset) {
    const char *curr = input + *offset;
    const char pre[] = "mul(";
    size_t i;

    // Check for "mul(" prefix
    for (i = 0; i < 4; ++i) {
        if (curr[i] != pre[i]) {
            (*offset)++;
            return 0; 
        }
    }

    if (DEBUG)
        printf("Prefix correct\n");
    *offset += strlen(pre);

    // Parse the first number
    int x = number(input + *offset);
    if (x == -1) {
        if (DEBUG)
            printf("Invalid first number.\n");
        (*offset)++;  // Skip invalid character
        return 0;
    }

    *offset += int_len(x);

    // Check for the comma
    if (input[*offset] != ',') {
        if (DEBUG)
            printf("Expected comma.\n");
        (*offset)++; 
        return 0;
    }

    *offset += 1;  // Skip comma

    // Parse the second number
    int y = number(input + *offset);
    if (y == -1) {
        if (DEBUG)
            printf("Invalid second number.\n");
        (*offset)++; 
        return 0;
    }

    *offset += int_len(y);

    // Check for the closing parenthesis
    if (input[*offset] != ')') {
        if (DEBUG)
            printf("Expected ')'.\n");
        (*offset)++;
        return 0;
    }

    *offset += 1;  // Skip closing parenthesis

    if (DEBUG)
        printf("Numbers found: %d, %d\n", x, y);

    return y*x;  // Successful parsing
}

int is_enabled(const char *input, int *offset) {
    const char *curr = input + *offset;
    if (strncmp(curr, "don't", 5) == 0) {
        return 0;
    }

    if (strncmp(curr, "do", 2) == 0) {
        return 1;
    }

    return -1;
}

int main() {
    const char *file_input = "./inputs/day3.txt";
    FILE *file = fopen(file_input, "r");
    if (file == NULL) {
        printf("Error opening file %s\n", file_input);
        return 1;
    }

    char line[MAX_LEN];
    int size = 0;

    if (fgets(line, sizeof(line), file) != NULL) {
        size = strlen(line);
    } else {
        printf("Error reading line.\n");
        fclose(file);
        return 1;
    }

    fclose(file);

    int res = 0, offset = 0;
    while (offset < size) {
        res += count(line, &offset);  
    }

    printf("Part I: %d\n", res);

    res = 0, offset = 0;
    int temp = 0;
    bool enabled = true;
    while (offset < size) {
        int enable_state = is_enabled(line, &offset);
        if (enable_state != -1) {
            enabled = enable_state;
        }

        temp = count(line, &offset);
        if (enabled) {
            res += temp;
        }
    }

    printf("Part II: %d\n", res);
    return 0;
}
