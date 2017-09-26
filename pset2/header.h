#ifndef __HEADER_H__
#define __HEADER_H__

#include <stdbool.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

#define SKIP_FIRST_VIOLATION 10
#define SKIP_STEP_VIOLATION 11
#define SKIP_GENERIC_VIOLATION 12

#define GREEDY 20
#define BACKWARD 21
#define SKIP 22
#define OPT 23


/** 
  * Writes the array to stdout
  * @param arr[] is the array to be printed
  * @param size is the size of the array to be printed
  * @param type is the type of the method
  * @param skipStart is the first step in skip, if any
  * @param skipJump is the step in skip, if any
  */
void printFinalArray(int arr[], int size, int type, int skipStart, int skipJump);

/** 
  * Prints skip error messages, if any
  * @param violationType is the type of violation that occurred
  * @param skipStart is the first step in skip
  * @param skipJump is the step in skip
  */
void printSkipErrorMessage(int violationType, int skipStart, int skipJump);

/** 
  * When the must have integers have an arithmetic progression,
  * this method is called to print -method: 0 []
  * @param *methods[] array of pointers with the names of the methods
  * @param size of array of pointers
  */
void printEmptyArrays(char *methods[], int numberOfMethods, bool anySkipViolation, 
	int violationType, int skipStart, int skipJump);

/** 
  * Uses the fuction strtol() to safely convert string arguments from the command line
  * to integers that will be used in main
  * @param string[] the command line argument
  * @param *dest pointer that stores the integer value, if it is a valid integer 
  */
bool stringToInt(char string[], int *dest);

/** 
 * Uses the fuction stringToInt() to extract the skip arguments in a safe way that protects
 * us against malicious inputs, such as int overflows or integers.
 * @param argStart[] the first user input (start)
 * @param argJump[] the second user input (step)
 * @param *skipstart pointer to the memory space that will save the skipStart
 * @param *skipJump pointer to the memory space that will save the skipJump
 * @param start the start value for the main function
 * @param range the n value for the main function
 * @param *anySkipViolation boolean that lets the main function know whether there were violations
 */
void extractSkipArguments(char argStart[], char argJump[], 
	int *skipStart, int *skipJump,
	int start, int range, bool *anySkipViolation, int *violationType);

/** 
 * Used in the skip metho to determine whether an integer was already added in
 * the no arithmetic progress array. 
 * @param val the value
 * @param *arr the no arithmetic progression array
 * @param size the size of the NoAP array
 */
bool isIntegerInArray(int val, const int *arr, int size);


/**
 * Calculates the next value in the skip by adding the *currentIndex and the skipJump
 * It also accounts for the case when it wraps
 * Do it for at least range amount of times 
 * @param range is the n element in the commnand line, the range of numbers from 0 ... n - 1
 * @param *currentIndex is the current value being analyzed in the skip method
 * @param skipJump is the value of the step
 * @param *loopCounter keeps track of the number of wraps (stops at range wraps)
 * @param start either the largest must have integer + 1 or zero
 */
void nextSkipIteration(int range, int *currentIndex, int skipJump, int *loopCounter, int start);

/**
 * Help function to swap the values of x and y
 * @param x is the first value
 * @param y is the second size
 */
bool isNumber(const char number[]);

/**
 * Help function to swap the values of x and y
 * @param x is the first value
 * @param y is the second size
 */
void swap(int *xp, int *yp);

/**
 * Bubble sort algorithm taken from http://www.geeksforgeeks.org/bubble-sort/
 * @param arr[] is the array to be sorted
 * @param n is the array size
 */
void bubbleSort(int arr[], int n);

/**
 * Analyzes if a set of three integers form an Arithmetic Progression
 * @param x, y and z are ints from the array
 * returns true if there is an AP
 * returns false, otherwise
 */
bool isAP(int x, int y, int z);

/**
 * Given a certain new integer, 
 * the function iterates through the array to check whether the new integer forms an arithmetic
 * progression with any of the existing memebrs of the NoAP array
 * @param prospectiveMember is the new integer to be analyzed
 * @sizeOfArray is the size of the array
 * *NoAPArray is the array free of arithmetic progressions
 */
bool anyAPViolation(int prospectiveMember, int sizeOfArray, const int *NoAPArray);

/**
 * BACKTRACK ALGORITHM: iterates through range, starting from lastChoice + 1 
 * in order to analyze all the different combinations of NoAP
 * Base Case: when the last choice is the base number that started the recursion
 * or an empty array (in case there were no must have ints)
 * Recursion Mechanism: When you finish iterating through all the possibilities
 * for the given starting array, remove your last choice made, and keep iterating
 */
void backtrackNoAP(int optArray[], int partialArray[],
	int *partialSize, int *optSize, 
	int *lastChoice, int baseNumber, int range);

#endif
