#define LENGTH 12

#include <stdio.h>

void print_binary(int n)
{
    int bit = 1 << LENGTH - 1;
    while (bit) {
        printf("%d", n & bit ? 1 : 0);
        bit >>= 1;
    }
    printf("\n");
}

int main() {
    int n = 1 << LENGTH, i;
    for (i = 0; i < n; i++)
        print_binary(i);
}