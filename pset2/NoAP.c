
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


bool isIntegerInArray(int val, int *arr, int size){
    for (int i = 0; i < size; i++) {

        if (arr[i] == val) {
            return true;
        }
    }
    return false;
}

void nextSkipIteration(int range, int *currentIndex,  int skipJump, int *loopCounter) {
	/*TODO BE ABLE TO RECOGNIZE WHEN YOU'RE REPEATING THE LOOP */
	int flatSum = *currentIndex + skipJump;
	if (flatSum >= range - 1) {

		*currentIndex = flatSum - (range - 1);
		*loopCounter += 1;
	} else {
		*currentIndex = flatSum;

	}
}
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
	if (sizeOfArray < 2) {
		return false;
	}

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
	// store the methods
	char *methods[4];
	int numberOfMethods = 0;

	 // helper variables to go through all the arguments
	int argcHelper = 0;

	// keep track of whether it is a skip argument or a regular must have integer 
	bool isSkipArgument;
	int skipStart;
	int skipJump;

	/**
	* Parse the arguments.
	* Allocate each argument to the appropriate variable 
	*/
	do
	{	
		// check for at least one argument
		if (argc < 2) {
			fprintf(stderr, "Usage: NoAP n -methods\n");
			return 1;
		}
		// first argument is the range, ensure number is non-negative
		else if (argcHelper == 1 && 
			(!isNumber(argv[argcHelper]) ||
			(range = atoi(argv[argcHelper])) < 0))

	    {
	        fprintf(stderr, "NoAP: n must not be negative; was %i\n", range);
	        return 2;
	    }
	    // add all must-have integers to the array
	    else if (argcHelper > 1 && isNumber(argv[argcHelper]) && isSkipArgument == false)
	    {
	    	int newMustHaveInt = atoi(argv[argcHelper]);

	    	if (newMustHaveInt > range - 1) {
	    		fprintf(stderr, "NoAP: integer out of range %i\n", newMustHaveInt);
	    		return 3;
	    	}

	    	// add to must have integers array
	    	mustHaveIntegers[sizeOfMustHaveIntegers] = newMustHaveInt ;

	    	// update largest must have integer
	    	if (newMustHaveInt > largestMustHaveInt) {
	    		largestMustHaveInt = newMustHaveInt;
	    	}

	    	// update size
	    	sizeOfMustHaveIntegers++; 
	    } 
	    else if (argcHelper > 1 && argv[argcHelper][0] == '-')
	    // add method to method array
	    {	
	    	   			/*TODO SAFER WAY EXTRACT SKIP ARGUMENTS */

	    	if (strcmp(argv[argcHelper], "-skip") == 0) {
	    		isSkipArgument = true;
	    		skipStart = atoi(argv[argcHelper + 1]);
	    		skipJump = atoi(argv[argcHelper + 2]);
	    	}
	    	methods[numberOfMethods] = argv[argcHelper];
	    	numberOfMethods++;
	    } 

	    argcHelper++;
	} while (argcHelper < argc);

    int array[range];
	int sizeOfArray = 0;

	int backwardArray[range];
	int sizeOfBackwardArray = 0;

	int skipArray[range];
	int sizeOfSkipArray = 0;

	int hasInvalidMustHaveIntegers = false;



	// go through must have integer array to make sure there are no PAs
	for (int i = 0; i < sizeOfMustHaveIntegers; i++) 
	{
		// iterate through the current array to see if any pair (x, y) makes AP with z 
		if (!anyAPViolation(mustHaveIntegers[i], sizeOfArray, array)) {
				array[sizeOfArray] = mustHaveIntegers[i];
				backwardArray[sizeOfBackwardArray] = mustHaveIntegers[i];
				skipArray[sizeOfSkipArray] = mustHaveIntegers[i];

				// keep array size updated
				sizeOfArray += 1;
				sizeOfBackwardArray += 1;
				sizeOfSkipArray += 1;

		} else {
			hasInvalidMustHaveIntegers = true;
			printf("0 []\n");
			break;
		}
	}

   
   for (int i = 0; i < numberOfMethods; i++) {

   		if (strcmp(methods[i], "-greedy") == 0) {
   			// initialize prospective member according to whether or not there is 
		    int prospectiveMember = largestMustHaveInt + 1;

		     /*********** GREEDY ***********/
		    // iterate through the set of numbers, starting with the largest must-have int
		    for (; prospectiveMember < range; prospectiveMember++) {
		    	
				// iterate through the current array to see if any pair (x, y) makes AP with z 
				if (!anyAPViolation(prospectiveMember, sizeOfArray, array)) {
					array[sizeOfArray] = prospectiveMember;
					sizeOfArray += 1;
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
					// iterate through the current array to see if any pair (x, y) makes AP with z 
					if (!anyAPViolation(prospectiveBackWardMember, sizeOfBackwardArray, backwardArray)) {
						backwardArray[sizeOfBackwardArray] = prospectiveBackWardMember;
						sizeOfBackwardArray += 1;
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
   		else if (strcmp(methods[i], "-skip") == 0) {
   			int loopCounter = 0;
   			for (int prospectiveSkipMember = skipStart; loopCounter < range;
   			 nextSkipIteration(range, &prospectiveSkipMember, skipJump, &loopCounter)) {

					// iterate through the current array to see if any pair (x, y) makes AP with z 
					if (prospectiveSkipMember > largestMustHaveInt 
						&& !anyAPViolation(prospectiveSkipMember, sizeOfSkipArray, skipArray) 
						&& isIntegerInArray(prospectiveSkipMember, skipArray, sizeOfSkipArray) == false) {
						skipArray[sizeOfSkipArray] = prospectiveSkipMember;
						sizeOfSkipArray += 1;
					}
				
   			}

   			// sortprospective backward memeber
			bubbleSort(skipArray, sizeOfSkipArray);

			// output array of integers 
			printf("-skip %i %i: %i [", skipStart, skipJump, sizeOfSkipArray);
			for (int i = 0; i < sizeOfSkipArray; i ++) {
				printf("%i", skipArray[i]);

				if (i < sizeOfSkipArray - 1) {
					printf("%c", ',');
				} else {
					printf("]\n");
				}
				
			}	
   		} else {
   			printf("NoAP: invalid method; %s is not valid\n", methods[i]);
   		} 

   }
}
