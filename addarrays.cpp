#define LENGTH 5
#define MAX_ITEMS 70

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

void bin(int n) {
    int index = 0;
    int arr[MAX_ITEMS];
    int bit = 1 << LENGTH - 1;

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
    for (i = 0; i < n; i++) {
        bin(i);
    }
}