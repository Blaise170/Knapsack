#define LENGTH 12

#include <stdio.h>
#include <string.h>

void print_binary(int n)
{
    int store;
    char buffer[50];
    int bit = 1 << LENGTH - 1;
    while (bit) {
        store = sprintf(buffer, "%d", n & bit ? 1 : 0);
        bit >>= 1;
    }
    strcat(buffer, "\n");

    // array[i] = buffer; // won't work, just an example
}

int main() {
    int n = 1 << LENGTH, i;
    for (i = 0; i < n; i++)
        print_binary(i);
}