/* You will develop a tool to extract comments from C 
source code as the first part of this analysis 
(we will leave extraction of identifiers and 
all subsequent steps to someone else). */

#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv) {
	// declare variables
	FILE *file;
	// location to store the bytes that get read from the file
	// where to put the bytes after it's read them
	//TODO find out what should be buffer size
	#define CHUNK 1024 /* read 1024 bytes at a time */
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
        
        if (ferror(file)) {
        	/* deal with error */
        	printf("Error reading");
    	}
        printf("%s", line); 
    }
	// close line
	 fclose(file);


	return 0;
}