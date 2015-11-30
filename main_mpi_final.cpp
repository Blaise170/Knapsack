/* Blaise Cannon
 * Knapsack Problem - Parallel
 * 25 November 2015
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
 * in a parallel manner, so the point at which the computer's
 * time-to-completion grows too large will be much slower than the same
 * problem solved in a sequential manner.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <inttypes.h>
#include <math.h>
#include "mpi.h"

using namespace std;

static const int ITEMS_AVAILABLE = 30; // how many items we are testing from the data set this run
static const int MAX_WEIGHT = 325; // how much weight the knapsack can hold this run

/* Note: On 32 bit systems, a value for ITEMS_AVAILABLE greater than 31 will
 * cause an overflow of the unsigned long long int. On 64 bit systems, this
 * issue will likely not occur although it is still not guaranteed that any
 * unsigned long long int will take a 64 bit value.
 */

int value[ITEMS_AVAILABLE]; // store item value
int weight[ITEMS_AVAILABLE]; // store item weight

char *items[ITEMS_AVAILABLE]; // store item names

unsigned long long int rcv[128];
unsigned long long int binary[ITEMS_AVAILABLE]; // stores binary numbers
unsigned long long int process_index[2];

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

void init(unsigned long long int array[])
{
    int x;
    int arraysize = 32;

    for (x = 0; x < arraysize; x++)
    {
	array[x] = 0;
    }	
}

int main(int argc, char *argv[]) {

    // MPI Variables
    int flag;
    int size;
    int rank;
    int rc;
    int num;

    // initialize MPI
    rc = MPI_Init(&argc, &argv);
    flag = 0;
    MPI_Initialized(&flag);

    // checks for init errors
    if (!flag) {
        printf("Failed to initialize.");
        MPI_Abort(MPI_COMM_WORLD, rc);
    }

    // Sets size and rank
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    read(); // reads in file
    init(rcv);

    unsigned long long int p = permutations(ITEMS_AVAILABLE); // stores the total binary numbers
    unsigned long long int i; // allows for iteration up to p
    unsigned long long int bestValueItems[ITEMS_AVAILABLE]; // stores best possible knapsack binary
    unsigned long long int numStart = rank * (p/size);
    unsigned long long int numEnd = (rank+1) * (p/size);
    int bestValue = 0; // stores best possible knapsack value

    printf("Please wait, items are now being checked...\n"); // after ITEMS_AVAILABLE > 25 or so, takes awhile to finish

    int val;
    int bestIndex = 0; // stores best index for return

    for (unsigned long long int index = numStart; index < numEnd; index++) {
        int weightTaken = 0; // stores weight for each possible knapsack
        int valueTaken = 0; // stores total value for each possible knapsack
        short check = 0; // checks whether knapsack weighs too much
        int j = 0;

        bin(index);

        while (j < (ITEMS_AVAILABLE - 1)) {
            // if binary[j] == 1, we are taking the item
            if (binary[j] > 0) {
                // checks to make sure knapsack is not too heavy
                if ((weight[j] + weightTaken) <= MAX_WEIGHT) {
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
            	bestIndex = index;
		process_index[0] = bestValue;
		process_index[1] = bestIndex;
	    }
        }
    }

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Gather(&process_index, 2, MPI_UNSIGNED_LONG_LONG, &rcv, 2, MPI_UNSIGNED_LONG_LONG, 0, MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD);

    if (rank == 0)
    {
	int sizex = size*2;
	int allBestValue = 0;
	int allBestIndex = 0;

	for (int k = 0; k < sizex; k+=2)
	{
	    if (rcv[k] > allBestValue)
	    {
		allBestValue = rcv[k];
		allBestIndex = rcv[k+1];
	    }
	}

	bin(allBestIndex);

	int kk;
	printf("The best items to take are: ");
	while (kk < ITEMS_AVAILABLE)
	{
	    if (binary[kk] == 1)
	    {
		printf("%s ", items[kk]);
	    }
	
	    kk++;
	}

	printf("\nThese items will give a final value of %d.\n", allBestValue);

    }

    MPI_Finalize();
    return 0;
}
