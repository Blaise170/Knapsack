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

using namespace std;

/* Arrays */
int value[50]; // store item value
int weight[50]; // store item weight
char *items[50]; // store item names
char *binNums[50]; // store all of the binary strings


// data set is no larger than 50 items, so arrays only need to hold a max of 50 elements

/* Values */
static const int ITEMS_AVAILABLE = 50; // how many items we are testing from the data set this run
static const int MAX_WEIGHT = 400; // how much weight the knapsack can hold this run
int bestValue; // stores the best value for a knapsack
char bestKnapsack[50]; // store string for best binary string knapsack possible

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

            k++; // iterates
        }

        fclose(data); // close file
    }

    else {
        // problems with the file location are most likely to produce errors
        fprintf(stderr, "Error reading file, check to make sure it is not locked and that it exists.");
    }
}

void printItems() {
    int s;
    for (s = 0; s < ITEMS_AVAILABLE; s++) {
        printf("Name: %s, Value: %d, Weight: %d\n", items[s], value[s], weight[s]);
    }
    printf("\n");
}

unsigned long long int factorial(int n) {
    // Range: 0 to 18,446,744,073,709,551,615
    // Outside of range returns 0
    // Maximum elements: 51

    if (n == 0) {
        return 1;
    }
    return n * factorial(n - 1);
}

int main() {
    int i;

    read(); // reads in file
    printItems(); // prints out the file

    unsigned long long int numPerms = factorial(ITEMS_AVAILABLE); // stores the number of different combinations
    printf("Total possible permutations: %llu\n", numPerms);
    char *permutations[numPerms]; // holds all of the different strings

/*
    for (i = 0; i < numPerms; i++)
    {
        int weightTaken = 0;
        int valueTaken = 0;
        int j = 0;

        while (j < ITEMS_AVAILABLE)
        {
            j++;
            int temp = atoi(array[i].getNextChar()); // i.e. if number is 010011 we want 0 then 1 then 0 then 0 etc.
            if (temp == 1) // 0 don't take, 1 do take
            {
                if ((weight[j] + weightTaken) < MAX_WEIGHT)
                {
                    weightTaken += weight[j];
                    valueTaken += values[j];
                }
                else
                {
                    // break the while loop
                }
            }
        }

        if (valueTaken > bestValue)
        {
            printf("array[i] is better...");
            bestKnapsack[0] = array[i];
            bestValue = valueTaken;
        }

    }
*/
    return 0;
}