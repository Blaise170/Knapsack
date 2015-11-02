#define LENGTH 3
#define MAX_ITEMS 7

#include <stdio.h>

/*
000
001
010
011
101
110
111
*/

void print_binary(int n) {
    int index = 0;
    int arr[MAX_ITEMS];

    // Bit premise
    int bit = 1 << LENGTH - 1;
    //While bit
    while (bit) {
        int k = (n & bit ? 1 : 0);
        bit >>= 1;
        arr[index] = k;
        index++;

    }
    for (index = 0; index < LENGTH; index++) {
        printf("%d", arr[index]);

    }
    printf("\n");
}

int main() {
    int n = (1 << LENGTH), i;
    for (i = 0; i < n; i++)
        print_binary(i);
}