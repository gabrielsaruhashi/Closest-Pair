/* You will develop a tool to extract comments from C 
source code as the first part of this analysis 
(we will leave extraction of identifiers and 
all subsequent steps to someone else). */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define CHUNK 1024 /* read 1024 bytes at a time */

int getIndexOfContentStart(char line[CHUNK], int type) {
	// for type, 0 = "//" comment, and 1 == "/*" comment
	if (type == 0) {
		// strlen - 1 because I'm accessing i + 1
		for (int i = 0; i < strlen(line) - 1; i++) {
			// find index of either "//" or "/*"
			if (line[i] == '/' &&  
				line[i + 1] == '/') {

				int index = i + 2;
				while(line[index] == ' ') {
					index += 1;
				}

				return index;
			}
		}
		//TODO return something that indicate it was not found
		return CHUNK;
	} else if (type == 1) {
		return CHUNK;
	}
		
}

int main(int argc, char **argv) {
	// declare variables
	FILE *file;
	// location to store the bytes that get read from the file
	// where to put the bytes after it's read them
	
	char line[CHUNK];


	// check if number of arguments is correct
	if (argc != 2) {
		fprintf(stderr, "Usage: %s filename\n", argv[0]);
		exit(1);
	}

	// use standard I/O library to open input file
	// with reading permissions
	file = fopen(argv[1], "r");

	// check if input file is corrupted
	if (file == 0) {
		/* perror is a standard C library routine */
		/* that prints a message about the last failed library routine */
		/* prepended by its argument */
		perror(argv[0]);
		exit(2);
	}

	// get each line, and 
 	while (fgets(line, sizeof(line), file)) {
        /* note that fgets don't strip the terminating \n, checking its
           presence would allow to handle lines longer that sizeof(line) */

 		// check if it is a comment
 		if (strstr(line, "//")) {

 			// check if it is contained in a string or character literal
 			// type 0 is "//"
 			int indexStart = getIndexOfContentStart(line, 0);

 			char* output = malloc(strlen(line) - (indexStart + 1));

 			// char* strncpy(char* dest, char* src, int size)
 			// indexStart. + 1 because index starts at 0
 			output = strncpy(output, line + indexStart, strlen(line) - (indexStart + 1));

 			// add the terminating \n
 			output[strlen(output)] = '\n';

 			// strip comments
        	printf("%s", output); 
 		

 		}

 		
    }
	// close line
	 fclose(file);


	return 0;
}