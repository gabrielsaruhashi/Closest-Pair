
bool stringToInt(char string[], int *dest) {
	char *end;
	lnum = strtol(string, &end, 10);        //10 specifies base-10
	if (end == in_str)     //if no characters were converted these pointers are equal
    {
    	fprintf(stderr, "ERROR: can't convert string to number\n");
    	return false;
    }

	//If sizeof(int) == sizeof(long), we have to explicitly check for overflows
	if ((lnum == LONG_MAX || lnum == LONG_MIN) && errno == ERANGE)
	{
	    fprintf(stderr, "ERROR: number out of range for LONG\n");
	    return false;
	}

	//Because strtol produces a long, check for overflow
	if ( (lnum > INT_MAX) || (lnum < INT_MIN) )
	{
		fprintf(stderr, "ERROR: number out of range for INT\n");
		return false

	}

	//Finally convert the result to a plain int (if that's what you want)
	*dest = (int) lnum;
	return true;
}
void extractSkipArguments(char argStart[], char argJump[], 
	int *skipStart, int *skipJump,
	int start, int range, bool *anySkipViolation) {

	bool isValidStart = stringToInt(argStart, skipStart);
	bool isValidJump = stringToInt(argJump, skipJump);

	// in any case there should be no additional output beyond the first error message.
	if (isValidStart && isValidJump) {
		if (*skipstart >= range) {
			*anySkipViolation = true;
			printf("NoAP: invalid first %i\n", skipStart);
		} else if (*skipJump < 1 || *skipJump > range - start) {
			*anySkipViolation = true;
			printf("NoAP: invalid step %i\n", *skipJump);
		}
	} else {
		*anySkipViolation = true;
	}

}
bool isIntegerInArray(int val, const int *arr, int size){
    for (int i = 0; i < size; i++) {

        if (arr[i] == val) {
            return true;
        }
    }
    return false;
}

void nextSkipIteration(int range, int *currentIndex, int skipJump, int *loopCounter) {
	/*TODO BE ABLE TO RECOGNIZE WHEN YOU'RE REPEATING THE LOOP */
	int flatSum = *currentIndex + skipJump;
	if (flatSum >= range - 1) {

		//*currentIndex = flatSum - (range - 1);
		*currentIndex = flatSum % range;
		*loopCounter += 1;
	} else {
		*currentIndex = flatSum;

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
