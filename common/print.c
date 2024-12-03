#include <stdio.h>
#include "print.h"

void print_str(const char c[], const int size) {
    int i = 0;
    while (i < size) {
        printf("%c", c[i++]);
    }
    printf("\n");
}
