

#include "header.h"


/* The first argument n is required and will be the decimal representation of a nonnegative integer; 
the range of values in the set to construct is then 0,…,n−10,…,n−1. You may assume 
that nn is small enough so that you can create several arrays of nn integers as necessary. */

int main(int argc, char *argv[])
{	
	// the n value
	int range;

	// array of must have integers
	int mustHaveIntegers[argc];
	int sizeOfMustHaveIntegers = 0;

	// keeps track of the largest must have integer to initiate the start variable
	int largestMustHaveInt = -1;

	// store the methods
	char *methods[argc];
	int numberOfMethods = 0;

	 // keep track of current argument index
	int argcHelper = 0;

	// keep track of whether it is a skip argument or a regular must have integer 
	int skipStart = 0;
	int skipJump = 0;
	bool anySkipViolation = false;
	int violationType;

	// keep track what kind of argument it is
	bool isMethodArgument = false;

	/**
	* Parse the arguments.
	* Allocate each argument to the appropriate variable 
	*/
	do
	{	
		// check for at least one argument
		if (argc < 2) 
		{
			fprintf(stderr, "Usage: NoAP n -methods\n");
			return 1;
		}
		// first argument is the range, ensure number is non-negative and valid
		else if (argcHelper == 1)
	    {
	    	if (!stringToInt(argv[argcHelper], &range)) {
	    		 fprintf(stderr, "NoAP: n is an invalid argument\n");
	    		 return 2;
	    	} else if (range <= 0) {
	    		fprintf(stderr, "NoAP: n must not be negative; was %i\n", range);
	       	 	return 2;
	    	}
	        
	    }
	    // add all must-have integers to the array
	    else if (argcHelper > 1 && isNumber(argv[argcHelper]) && isMethodArgument == false)
	    {
	    	int newMustHaveInt = atoi(argv[argcHelper]);

	    	if (newMustHaveInt > range - 1) 
	    	{
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
	    	isMethodArgument = true;
	    	if (strcmp(argv[argcHelper], "-skip") == 0) 
	    	{
	    		
	    		extractSkipArguments(argv[argcHelper + 1], argv[argcHelper + 2], 
	    			&skipStart, &skipJump, 
	    			largestMustHaveInt + 1, range, &anySkipViolation, &violationType);

	    		    		
				methods[numberOfMethods] = argv[argcHelper];
				numberOfMethods++;

				// if there are any violations, stop getting method arguments
	    		if (anySkipViolation) {
	    			break;
	    		}
				// else, update argcHelper and go to next iteration 
				argcHelper += 2;
	    		
	    	} 
	    	else 
	    	{
	    		// add method to method array
	    		methods[numberOfMethods] = argv[argcHelper];
	    		numberOfMethods++;
	    	}
	    	
	    } 

	    argcHelper++;
	} while (argcHelper < argc);

	// all the array variables
    int array[range];
	int sizeOfArray = 0;

	int backwardArray[range];
	int sizeOfBackwardArray = 0;

	int skipArray[range];
	int sizeOfSkipArray = 0;

	int optArray[range];
	int sizeOfOptArray = 0;
	int partialOptArray[range];
	int sizeOfPartial = 0;

	// go through must have integer array to make sure there are no PAs
	for (int i = 0; i < sizeOfMustHaveIntegers; i++) 
	{
		// iterate through the current array to see if any pair (x, y) makes AP with z 
		if (!anyAPViolation(mustHaveIntegers[i], sizeOfArray, array)) 
		{
				array[sizeOfArray] = mustHaveIntegers[i];
				backwardArray[sizeOfBackwardArray] = mustHaveIntegers[i];
				skipArray[sizeOfSkipArray] = mustHaveIntegers[i];
				optArray[sizeOfOptArray] = mustHaveIntegers[i];
				partialOptArray[sizeOfOptArray] = mustHaveIntegers[i];

				// keep array size updated
				sizeOfArray += 1;
				sizeOfBackwardArray += 1;
				sizeOfSkipArray += 1;
				sizeOfOptArray += 1;
				sizeOfPartial += 1;

		} 
		else 
		{	
			// print empty arrays, and error messages if any
			printEmptyArrays(methods, numberOfMethods, anySkipViolation,
			violationType, skipStart, skipJump);
			
			return 4;
		}
	}

   
   for (int i = 0; i < numberOfMethods; i++) {

   		/*********** GREEDY ***********/
   		if (strcmp(methods[i], "-greedy") == 0) 
   		{
			// initialize prospective member according to whether or not there is 
		    int prospectiveMember = largestMustHaveInt + 1;

		     /*********** GREEDY ***********/
		    // iterate through the set of numbers, starting with the largest must-have int
		    for (; prospectiveMember < range; prospectiveMember++) 
		    {
		    	
				// iterate through the current array to see if any pair (x, y) makes AP with z 
				if (!anyAPViolation(prospectiveMember, sizeOfArray, array)) 
				{
					array[sizeOfArray] = prospectiveMember;
					sizeOfArray += 1;
				}
				
			}

			bubbleSort(array, sizeOfArray);

			printFinalArray(array, sizeOfArray, GREEDY, 0, 0);

			
   		} 
   		/*********** BACKWARD ***********/
   		else if (strcmp(methods[i], "-backward") == 0) 
   		{
			int prospectiveBackWardMember = range - 1;
			for (; prospectiveBackWardMember > largestMustHaveInt; prospectiveBackWardMember--) 
			{
					// iterate through the current array to see if any pair (x, y) makes AP with z 
					if (!anyAPViolation(prospectiveBackWardMember, sizeOfBackwardArray, backwardArray)) 
					{
						backwardArray[sizeOfBackwardArray] = prospectiveBackWardMember;
						sizeOfBackwardArray += 1;
					}
			}

			// sortprospective backward memeber
			bubbleSort(backwardArray, sizeOfBackwardArray);


			// output array of integers 
			printFinalArray(backwardArray, sizeOfBackwardArray, BACKWARD, 0, 0);

   		} 
   		/*********** SKIP ***********/
   		else if (strcmp(methods[i], "-skip") == 0) 
   		{
   			int loopCounter = 0;

   			if (anySkipViolation) {
   				printSkipErrorMessage(violationType, skipStart, skipJump);
   				break;
   			}

   			for (int prospectiveSkipMember = skipStart; loopCounter < range;
   			 nextSkipIteration(range, &prospectiveSkipMember, skipJump, &loopCounter, largestMustHaveInt + 1)) 
   			{

					// iterate through the current array to see if any pair (x, y) makes AP with z 
					if (prospectiveSkipMember > largestMustHaveInt 
						&& !anyAPViolation(prospectiveSkipMember, sizeOfSkipArray, skipArray) 
						&& isIntegerInArray(prospectiveSkipMember, skipArray, sizeOfSkipArray) == false) 
					{
						skipArray[sizeOfSkipArray] = prospectiveSkipMember;
						sizeOfSkipArray += 1;
					}
				
   			}

   			// sortprospective backward memeber
			bubbleSort(skipArray, sizeOfSkipArray);

			printFinalArray(skipArray, sizeOfSkipArray, SKIP, skipStart, skipJump);
   		} 
   		
   		/*********** OPT ***********/
   		else if (strcmp(methods[i], "-opt") == 0) 
   		{
   			int baseNumber = largestMustHaveInt;
   			// set last choice to 1
   			int lastChoice = largestMustHaveInt;
		    
		    // iterate through the set of numbers, starting with the largest must-have int
		    backtrackNoAP(optArray, partialOptArray,
				&sizeOfPartial, &sizeOfOptArray, 
				&lastChoice, baseNumber, range);
   		}
   		else 
   		// if somehow user sneaks in an invalid method, just let him know it is not a valid method
   		{
   			printf("NoAP: invalid method; %s is not valid\n", methods[i]);
   		} 

   }
}
