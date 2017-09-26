#include "header.h"

void printFinalArray(int arr[], int size, int type, int skipStart, int skipJump) {
	// print adequate header 
	if (type == GREEDY) {
		printf("-greedy: %i [", size);
	}
	else if (type == BACKWARD)
	{
		printf("-backward: %i [", size);
	}
	else if (type == SKIP)
	{
		printf("-skip %i %i: %i [", skipStart, skipJump, size);
	}
	else if (type == OPT)
	{
		printf("-opt: %i [", size);
	}
	// output array of integers
	for (int i = 0; i < size; i ++) 
	{
		printf("%i", arr[i]);

		if (i < size - 1) 
		{
			printf(", ");
		}
		
	}
	printf("]\n");
}

void printSkipErrorMessage(int violationType, int skipStart, int skipJump) 
{
	if (violationType == SKIP_FIRST_VIOLATION) {
		printf("NoAP: invalid first %i\n", skipStart);
	} 
	else if (violationType == SKIP_STEP_VIOLATION) 
	{
		printf("NoAP: invalid step %i\n", skipJump);
	}
	else 
	{
		printf("NoAP: either first or step are not valid\n");
	}
}

void printEmptyArrays(char *methods[], int numberOfMethods, bool anySkipViolation, 
	int violationType, int skipStart, int skipJump)
{

	for (int i = 0; i < numberOfMethods; i++) {

		if (strcmp(methods[i], "-greedy") == 0 || 
			strcmp(methods[i], "-backward") == 0 ||
			(strcmp(methods[i], "-skip") == 0 && anySkipViolation == false) ||
			strcmp(methods[i], "-opt") == 0) {

				printf("%s: 0 []\n", methods[i]);
		} else if (strcmp(methods[i], "-skip") == 0 && anySkipViolation == true) {
			printSkipErrorMessage(violationType, skipStart, skipJump);
		} 
	}

}

bool stringToInt(char string[], int *dest) 
{
	char *end;

	long lnum = strtol(string, &end, 10);        //10 specifies base-10
	if (end == string)     //if no characters were converted these pointers are equal
    {
    	fprintf(stderr, "ERROR: can't convert string to number\n");
    	return false;
    }

	//If sizeof(int) == sizeof(long), we have to explicitly check for overflows
	if ((lnum == LONG_MAX || lnum == LONG_MIN))
	{
	    fprintf(stderr, "ERROR: number out of range for LONG\n");
	    return false;
	}

	//Because strtol produces a long, check for overflow
	if ( (lnum > INT_MAX) || (lnum < INT_MIN) )
	{
		fprintf(stderr, "ERROR: number out of range for INT\n");
		return false;

	}

	//Finally convert the result to a plain int (if that's what you want)
	*dest = (int) lnum;
	return true;
}

void extractSkipArguments(char argStart[], char argJump[], 
	int *skipStart, int *skipJump,
	int start, int range, bool *anySkipViolation, int *violationType) 
{

	bool isValidStart = stringToInt(argStart, skipStart);
	bool isValidJump = stringToInt(argJump, skipJump);
	// in any case there should be no additional output beyond the first error message.
	if (isValidStart && isValidJump) {
		if (*skipStart >= range) {
			*anySkipViolation = true;
			*violationType = SKIP_FIRST_VIOLATION ;
			//printf("NoAP: invalid first %i\n", *skipStart);
		} else if (*skipJump < 1 || *skipJump > range - start) {
			*anySkipViolation = true;
			*violationType = SKIP_STEP_VIOLATION;
			//printf("NoAP: invalid step %i\n", *skipJump);
		}
	} else {
		*anySkipViolation = true;
		*violationType = SKIP_GENERIC_VIOLATION;
		//printf("NoAP: either first or step are not valid\n");
	}

}
bool isIntegerInArray(int val, const int *arr, int size) 
{
    for (int i = 0; i < size; i++) {

        if (arr[i] == val) {
            return true;
        }
    }
    return false;
}

void nextSkipIteration(int range, int *currentIndex, int skipJump, int *loopCounter, int start) 
{
	/*TODO BE ABLE TO RECOGNIZE WHEN YOU'RE REPEATING THE LOOP */
	int flatSum = *currentIndex + skipJump;

	if (flatSum >= range) {
		//*currentIndex = flatSum - (range - 1);
		*currentIndex = (flatSum % range) + start;
		//printf("It's a wrap! New index is %i; flatsum is %i of start %i\n", *currentIndex, flatSum, start);

		*loopCounter += 1;
	} else {
		*currentIndex = flatSum;
		//printf("Next index is %i\n", *currentIndex);


	}
}

bool isNumber(const char number[])
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
	int modulo1 = abs(x - y);
	int modulo2 = abs(x - z);
	int modulo3 = abs(y - z);

	// check for PA xyz
	if (modulo1 == modulo2) {

		return true;
	} 
	// check zxy
	else if (modulo1 == modulo3) {
		return true;
	}
	// check for xzy
	else if (modulo2 == modulo3) {
		return true;
	}
	// not an AP
	else {
		return false;
	}

}

bool anyAPViolation(int prospectiveMember, int sizeOfArray, const int *NoAPArray) 
{
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


void backtrackNoAP(int optArray[], int partialArray[],
	int *partialSize, int *optSize, 
	int *lastChoice, int baseNumber, int range) {

	//printf("New Recursion starting at %i \n", *lastChoice);

	int initialChoice = *lastChoice + 1;

	// (range - *prospectiveOpt) < *optSize
	for (int prospectiveOpt = initialChoice; prospectiveOpt <= range; prospectiveOpt++) 
    {	
		// end backtracking when 
		if (baseNumber == prospectiveOpt)
		{
			// print
			printf("-opt: %i [", *optSize);

			for (int i = 0; i < *optSize; i++) {
				printf("%i", optArray[i]);

				if (i < *optSize - 1) {
					printf("%c", ',');
				} else {
					printf("]\n");
				}
			}
			// copy the content of partial to official array
			return;
		}
		// when finishes going over the entire range
		else if (prospectiveOpt == range) 
		{
			//printf("End of iteration will remove %i since initial choice was %i\n", partialArray[*partialSize - 1], initialChoice);
			//printf("partialSize is %i , optSize is %i\n, lastChoice is %i", *partialSize, *optSize, *lastChoice);
			// update array
			if (*partialSize > *optSize) 
			{
				//printf("/*NEW LONGEST*/\n");
				// copy content of partial to official array
				for (int i = 0; i < *partialSize; i++) {
					optArray[i] = partialArray[i];
				}
				// update size counter
				*optSize = *partialSize;
			}

			/*printf("current partial array of size %i is", *partialSize);
			for (int i = 0; i < *partialSize; i++) {
				printf(" %i ", partialArray[i]);
			}
			printf("and the sixth element is %i", partialArray[5]);
			printf("\n"); */

			*lastChoice = partialArray[*partialSize - 1];
			//printf("last choice is %i\n", *lastChoice);

			// remove last choice
			*partialSize -= 1;

			// exit if it reaches baseNumber or empty array
			if (*lastChoice == baseNumber || *partialSize == 0) {
				// print
				printf("-opt: %i [", *optSize);

				for (int i = 0; i < *optSize; i++) {
					printf("%i", optArray[i]);

					if (i < *optSize - 1) {
						printf(", ");
					} else {
						printf("]\n");
					}
				}
				// copy the content of partial to official array
				return;
			}
			//printf("before recursive call\n");
			// the first lastChoice is just to keep track of numerical value for next prospective opt
			backtrackNoAP(optArray, partialArray, 
				partialSize, optSize, 
				lastChoice, baseNumber, range);
		}
		
		else 
		{
			if (!anyAPViolation(prospectiveOpt, *partialSize, partialArray)) 
			{	
				*lastChoice = prospectiveOpt;
				partialArray[*partialSize] = prospectiveOpt;
				*partialSize += 1;
				/*printf("ADDED %i, current partial array of size %i is", prospectiveOpt, *partialSize);
				for (int i = 0; i < *partialSize; i++) {
					printf(" %i ", partialArray[i]);
				}
				printf("\n"); */
			} else {
				//printf("IGNORED %i\n", prospectiveOpt);
			}
		}
	}

}
