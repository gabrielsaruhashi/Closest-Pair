
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

bool isNumber(char number[])
{
    int i = 0;

    //checking for negative numbers
    if (number[0] == '-')
        i = 1;
    for (; number[i] != 0; i++)
    {
        //if (number[i] > '9' || number[i] < '0')
        if (!isdigit(number[i]))
            return false;
    }
    return true;
}

void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
 
// A function to implement bubble sort
void bubbleSort(int arr[], int n)
{
   int i, j;
   for (i = 0; i < n-1; i++)      
 
       // Last i elements are already in place   
       for (j = 0; j < n-i-1; j++) 
           if (arr[j] > arr[j+1])
              swap(&arr[j], &arr[j+1]);
}
 

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
	// just add the first two numbers 

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
	int mustHaveIntegers[argc];
	int sizeOfMustHaveIntegers = 0;
	int largestMustHaveInt = 0;

	char *methods[4];
	int numberOfMethods = 0;

	 // helper variables to go through all the arguments
	int argcHelper = 0;
	bool isMustHaveInteger = true;

	// parse the arguments, and allocating each argument to the appropriate variable
	do
	{	
		// check for at least one argument
		//TODO change it to 2
		if (argc == 0) {
			printf("Usage: NoAP n -methods\n");
		}

		// first argument is the range, ensure number is non-negative
		if (argcHelper == 1 && (range = atoi(argv[argcHelper])) < 0)
	    {
	        printf("NoAP: n must not be negative; was value where value is replaced by the value of nn\n");
	        return 1;
	    }

	    // add all must-have integers to the array
	    //if (isdigit(atoi(argv[argcHelper])))
	    if (argcHelper > 1 && isNumber(argv[argcHelper]))
	    {
	    	int newMustHaveInt = atoi(argv[argcHelper]);
	    	mustHaveIntegers[sizeOfMustHaveIntegers] = newMustHaveInt ;

	    	// update largest must have integer
	    	if (newMustHaveInt > largestMustHaveInt) {
	    		largestMustHaveInt = newMustHaveInt;
	    	}
	    	sizeOfMustHaveIntegers++; 
	    } else if ((argcHelper > 1 && argv[argcHelper][0] == '-')) 
	    // add method to method array
	    {
	    	methods[numberOfMethods] = argv[argcHelper];
	    	numberOfMethods++;
	    }

	    argcHelper++;
	} while (argcHelper < argc);

    int array[range];
	int sizeOfArray = 0;
	int backwardArray[range];
	int sizeOfBackwardArray = 0;

	int hasInvalidMustHaveIntegers = false;



	// go through must have integer array to make sure there are no PAs
	for (int i = 0; i < sizeOfMustHaveIntegers; i++) 
	{

		// just add the first two numbers
		if (sizeOfArray < 2) 
		{ 
			array[sizeOfArray] = mustHaveIntegers[i];
			backwardArray[sizeOfBackwardArray] = mustHaveIntegers[i];
			// keep array size updated
			sizeOfArray += 1;
			sizeOfBackwardArray += 1;
		} else {
			// iterate through the current array to see if any pair (x, y) makes AP with z 
			if (!anyAPViolation(mustHaveIntegers[i], sizeOfArray, array)) {
					array[sizeOfArray] = mustHaveIntegers[i];
					backwardArray[sizeOfBackwardArray] = mustHaveIntegers[i];
					// keep array size updated
					sizeOfArray += 1;
					sizeOfBackwardArray += 1;


			} else {
				hasInvalidMustHaveIntegers = true;
				printf("0 []\n");
				break;
			}
		}

	}

   
   for (int i = 0; i < numberOfMethods; i++) {

   		if (strcmp(methods[i], "-greedy") == 0) {
   			// initialize prospective member according to whether or not there is 
		    int prospectiveMember = largestMustHaveInt + 1;

		     /*********** GREEDY ***********/
		    // iterate through the set of numbers, starting with the largest must-have int
		    for (; prospectiveMember < range; prospectiveMember++) {
		    	
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

			// output array of integers 
			printf("-greedy: %i [", sizeOfArray);
			for (int i = 0; i < sizeOfArray; i ++) {
				printf("%i", array[i]);

				if (i < sizeOfArray - 1) {
					printf("%c", ',');
				} else {
					printf("]\n");
				}
				
			}
   		} else if (strcmp(methods[i], "-backward") == 0) {
   			/*********** BACKWARD ***********/

			int prospectiveBackWardMember = range - 1;
			for (; prospectiveBackWardMember > largestMustHaveInt; prospectiveBackWardMember--) {

				// just add the first two numbers
				if (sizeOfBackwardArray < 2) 
				{ 
					backwardArray[sizeOfBackwardArray] = prospectiveBackWardMember;
					// keep array size updated
					sizeOfBackwardArray += 1;
				} 
				else 
				{
					// iterate through the current array to see if any pair (x, y) makes AP with z 
					if (!anyAPViolation(prospectiveBackWardMember, sizeOfBackwardArray, backwardArray)) {
						backwardArray[sizeOfBackwardArray] = prospectiveBackWardMember;
						sizeOfBackwardArray += 1;
					}
				}
			}

			// sortprospective backward memeber
			bubbleSort(backwardArray, sizeOfBackwardArray);


			// output array of integers 
			printf("-backward: %i [", sizeOfBackwardArray);
			for (int i = 0; i < sizeOfBackwardArray; i ++) {
				printf("%i", backwardArray[i]);

				if (i < sizeOfBackwardArray - 1) {
					printf("%c", ',');
				} else {
					printf("]\n");
				}
				
			}

   		}
   	

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
