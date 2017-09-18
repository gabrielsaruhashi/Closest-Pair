
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Function to discover whether integers x,y,z form a AP in a set
x > y so options for an AP are xyz, zxy, xzy */
bool isAP(int x, int y, int z) {
	
	// check for PA xyz
	if (y - x == z - x) {

		return true;
	} 
	// check zxy
	else if (x - z == y - x) {
		return true;
	}
	// check for xzy
	else if (y - x == z - y) {
		return true;
	}
	// not an AP
	else {
		return false;
	}

}

bool anyAPViolation(int prospectiveMember, int sizeOfArray, const int *NoAPArray) {
	// iterate through the current array to see if any pair (x, y) makes AP with z 
	for (int j = 0; j < sizeOfArray - 1; j++) {
		for (int k = j + 1; k < sizeOfArray; k++) {
			if (isAP(NoAPArray[j], NoAPArray[k], prospectiveMember)) {
				return true;
			}
		}
	}

	return false;
}

/* The first argument n is required and will be the decimal representation of a nonnegative integer; 
the range of values in the set to construct is then 0,…,n−10,…,n−1. You may assume 
that nn is small enough so that you can create several arrays of nn integers as necessary. */

int main(int argc, char *argv[])
{	

	int range;
	
	 // check for correct number of args AND a positive range
    if (argc < 1 || 
    	(range = atoi(argv[1])) < 0)
    {
        printf("Usage: NoAP n -methods\n");
        return 1;
    }

   	while 




    int array[range];
	int sizeOfArray = 0;

    /* GREEDY */
    // iterate through the set of numbers
    for (int prospectiveMember = 0; prospectiveMember < range; prospectiveMember++) {
    	
		// just add the first two numbers
		if (sizeOfArray < 2) 
		{ 
			array[sizeOfArray] = prospectiveMember;
			// keep array size updated
			sizeOfArray += 1;
		} 
		else 
		{
			// iterate through the current array to see if any pair (x, y) makes AP with z 
			if (!anyAPViolation(prospectiveMember, sizeOfArray, array)) {
				array[sizeOfArray] = prospectiveMember;
				sizeOfArray += 1;
			}
		}
	}

	for (int i = 0; i < sizeOfArray; i ++) {
		printf("%i", array[i]);
		printf("%c", ',');
	}


	// format string 
		

}


// only jhave AP if there is 
// start from 0, see if adding next number creates AP


// for each number z to consider
	// if any pair x,y already selected makes AP xyz zxy xzy
		// dont add 
	// else 
		// add z


// have an array that stores all numbers already selected

// function to check if three numbers are an arithmetic progression (return bool)
