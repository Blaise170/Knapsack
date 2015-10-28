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

/* Arrays */
char *items[100]; // store item names
int value[100]; // store item value
int weight[100]; // store item weight
char *sack[100]; // the stolen items
int total; // total value of items

/* Iterators */
int k = 0;
int ss = 0;

/* Variables */
int ELEMENTS = 0;
int ssk;

/* Constants */
static const int MAX_WEIGHT = 400; // how much the knapsack can hold

void read(void)
{
	FILE *data = fopen("data.txt", "r");

	if (data != NULL)
	{
		char line[256]; // sets max line length to 256
		while (fgets(line, sizeof line, data) != NULL)
		{
			// WARNINGS: this will break if the data file has more than
			// one space between each section and this will also break if
			// the correct format of NAME VALUE WEIGHT is not followed

			items[k] = strdup(strtok(line, " "));
			value[k] = atoi(strtok(NULL, " "));
			weight[k] = atoi(strtok(NULL, " "));

			k++;
		}

		fclose(data); // close file
	}

	else
	{
		printf("Error reading file, check to make sure it is not locked and that it exists.");
	}

	ELEMENTS = k;
}

void printitems(void)
{
	ssk = sizeof(sack)/sizeof(int);

	printf("\n\nItems in knapsack: ");

	for (ss = 0; ss < ssk; ss++)
	{
		if (ss == ssk)
		{
			printf("%s. Total value of sack: %d", sack[ss], total);
		}

		else
		{
			printf("%s, ", sack[ss]);
		}
	}
}

int main( void )
{
	read();
	printitems();

	return 0;
}