#include <stdio.h>
#include <iostream>
#include <algorithm>
using namespace std;

/* Constants */
const int ELEMENTS = 5;


unsigned int factorial(unsigned int n)
{
    if (n == 0)
    {
       return 1;
	}
    return n * factorial(n - 1);
}

int main()
{
	printf("Program is starting...\n");

	int item[ELEMENTS] = {1, 1, 0, 0, 0};
	int numperms = factorial(ELEMENTS);

	printf("Total possible permutations: %d\n", numperms);

	sort (item,item+ELEMENTS);

	do
	{
		printf("%d, %d, %d, %d, %d\n",item[0], item[1], item[2], item[3], item[4]);
	} while ( next_permutation(item,item+ELEMENTS) );

	return 0;
}
