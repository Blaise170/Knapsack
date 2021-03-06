/* Blaise Cannon
 * Knapsack Problem - Sequential
 * 27 September 2015
 *
 * The knapsack problem is an NP-Complete problem in mathematics and the
 * field of computer science. The knapsack problem is the idea that you
 * should take the most valuable items possible while also considering
 * a limited storage capacity. This creates a situation where you want to
 * take items based on the ratio of value to weight, and ignore items that
 * are indeed valuable but with a low ratio when compared to its weight.
 *
 * This problem is computationally hard as the computer must consider each
 * possible combination of items in order to give the best possible
 * solution. Computers will bog down after so many items are added to the
 * data file which the computer is reading from. This program is written
 * in a sequential manner, so the point at which the computer's
 * time-to-completion grows too large will be much quicker than the same
 * problem solved in a parallel manner.
 *
 * =========
 * Resources
 * =========
 *
 * 1. http://www.dreamincode.net/forums/topic/382784-global-array-becoming-null-after-appending-elements/
 */

/* Imports */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <inttypes.h>
#include <math.h>

using namespace std;

/* Values */
static const int ITEMS_AVAILABLE = 5; // how many items we are testing from the data set this run
static const int MAX_WEIGHT = 100; // how much weight the knapsack can hold this run

/* Arrays */
int value[ITEMS_AVAILABLE]; // store item value
int weight[ITEMS_AVAILABLE]; // store item weight
char *items[ITEMS_AVAILABLE]; // store item names
unsigned long long int binary[ITEMS_AVAILABLE]; // stores the binary permutations

//
void read() {
    int k = 0; // iterator
    FILE *data = fopen("data.txt", "r"); // opens data file

    if (data != NULL) {
        char line[256]; // sets max line length to 256
        while (fgets(line, sizeof line, data) != NULL && k < ITEMS_AVAILABLE) {
            // WARNINGS: this will break if the correct format of NAME VALUE WEIGHT is not followed

            items[k] = strdup(strtok(line, " ")); // takes the first token from line and assigns to array of items
            value[k] = atoi(strtok(NULL, " ")); // converts second token to int and assigns to array of values
            weight[k] = atoi(strtok(NULL, " ")); // converts last token to int and assigns to array of weight

            k++;
        }

        fclose(data); // close file
    }

    else {
        // problems with the file location are most likely to produce errors
        fprintf(stderr, "Error reading file, check to make sure it is not locked and that it exists.");
    }
}

// Function designed to check for file read integrity
void printItems() {
    int s;
    for (s = 0; s < ITEMS_AVAILABLE; s++) {
        // prints out each line of the data file
        printf("Name: %s, Value: %d, Weight: %d\n", items[s], value[s], weight[s]);
    }
    printf("\n");
}

// Solves number of permutations
unsigned long long int permutations(int n) {

    // the power function normally returns a float, but the solutions will never be floating point
    unsigned long long int r = pow(2.0, n);
    return r;

}

// Gives all permutations of binary for a given length
void bin(unsigned long long int n) {
    // index can be a short as ITEMS_AVAILABLE will not exceed 50
    short index = 0;
    unsigned long long int bit = 1 << ITEMS_AVAILABLE - 1;

    // bit shifting
    while (bit) {
        unsigned long long int k = (n & bit ? 1 : 0);
        bit >>= 1;
        binary[index] = k;
        index++;
    }
}

int main() {

    read(); // reads in file

    unsigned long long int p = permutations(ITEMS_AVAILABLE); // stores the total binary numbers
    unsigned long long int i; // allows for iteration up to p

    int bestValue = 0; // stores best possible knapsack value
    unsigned long long int bestValueItems[ITEMS_AVAILABLE]; // stores best possible knapsack binary

    printf("Please wait, items are now being checked...\n"); // after ITEMS_AVAILABLE > 25 or so, takes awhile to finish

    for (i = 0; i < p; i++) {
        int weightTaken = 0; // stores weight for each possible knapsack
        int valueTaken = 0;// stores total value for each possible knapsack
        short check = 0; // checks whether knapsack weighs too much
        int j = 0;

        bin(i);

        while (j < (ITEMS_AVAILABLE - 1)) {

            // if binary[j] == 1, we are taking the item
            if (binary[j] > 0) {

                // checks to make sure knapsack is not too heavy
                if ((weight[j] + weightTaken) < MAX_WEIGHT) {
                    weightTaken += weight[j]; // adds to weight
                    valueTaken += value[j]; // adds to value
                }

                    // otherwise we'll set the check bit
                else {
                    check = 1;
                    break;
                }
            }
            j++;
        }

        short q = 0; // will never be greater than ITEMS_AVAILABLE, in this case 50

        // checks to make sure that the knapsack isn't too heavy before setting a new best
        if (check != 1) {
            if (valueTaken > bestValue) {
                bestValue = valueTaken;
                for (q = 0; q < ITEMS_AVAILABLE; q++) {
                    bestValueItems[q] = binary[q];
                }
            }
        }
    }

    printf("\nThe best value available to take is: %d\n", bestValue);
    printf("In order to achieve this value, you need must take: ");

    // prints out the items you should take to get the best value
    int k = 0;
    while (k < (ITEMS_AVAILABLE)) {
        if (bestValueItems[k] > 0) {
            printf("%s ", items[k]);
        }

        k++;
    }

    return 0;
}
