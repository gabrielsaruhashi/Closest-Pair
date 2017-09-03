/* You will develop a tool to extract comments from C 
source code as the first part of this analysis 
(we will leave extraction of identifiers and 
all subsequent steps to someone else). */


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

#define CHUNK 1024 /* read 1024 bytes at a time */

int 

int getIndexOfContentStart(char line[CHUNK]) {
	// strlen - 1 because I'm accessing i + 1
	for (int i = 0; i < strlen(line) - 1; i++) {
		// find index of either "//" or "/*"
		if (line[i] == '/' &&  
			(line[i + 1] == '/' || line[i + 1] == '*')) {

			// index starts after // or /*
			int index = i + 2;
			// disregard trailing spaces and asterisks
			while(line[index] == ' ' || line[index] == '*') {
				index += 1;
			}

			return index;
		}
	}

	//TODO return something that indicate it was not found
	return CHUNK;
}

int getIndexOfContentEnd(char line[CHUNK], int indexStart, int indexEndingDelimiter) {
	// support variable
	int i = 0;
	//TODO take care of inifite while loop
	while(line[indexEndingDelimiter - i] == ' ' || 
		line[indexEndingDelimiter - i] == '*') {
		//printf("current contentEndIndex: %i ,  with character %c\n", indexEndingDelimiter - i, line[indexEndingDelimiter - i]);
		i += 1;
	}
	// return index of last character that is not whitespace or '*'
	// i - 1 to move back to last 'invalid' char
	if (indexEndingDelimiter - i != indexStart) {
		return indexEndingDelimiter - (i - 1);
	} else {
		printf("No Content\n");
		return -1;
	}
}

/* for "//" and / * cases
	gets index of content start (discard trailing whitespace and *)
	and prints line */
void printCommentedLine(char* line) {

	// get index of content start
	int indexStart = getIndexOfContentStart(line);
	//printf("the indexStart of: \n%sis: %i, resulting in\n", line, indexStart);

	// check if there is any content
	if (indexStart != CHUNK) {
		char* output = malloc(strlen(line) - (indexStart + 1));

		// char* strncpy(char* dest, char* src, int size)
		// indexStart. + 1 because index starts at 0
		output = strncpy(output, line + indexStart, strlen(line) - (indexStart + 1));

		// check if output is more than just whitespace
		if (strlen(output) > 0) {
			// add the terminating \n
			output[strlen(output)] = '\n';

			// strip comments
			printf("%s", output); 
		}
	} // else don't print anything
	


}

// for /* xyz */ cases
void printOneLineComment(char *line, int indexEndMark) {
	int indexStart = getIndexOfContentStart(line);
	int indexEnd = getIndexOfContentEnd(line, indexStart, indexEndMark);

	//printf("line is: %s\n", line);
	//printf("PRINTONELINECOMMENT - start: %i, end: %i\n", indexStart, indexEnd);

	// in case there is no content, aka indexStart is same as indexENd
	if (indexEnd != -1) {
		char* output = malloc(indexEnd - indexStart);

		output = strncpy(output, line + indexStart, indexEnd - indexStart);

		// check if output is more than just whitespace
		if (strlen(output) > 0) {
			// add the terminating \n
			output[strlen(output)] = '\n';

			// strip comments
			printf("%s", output); 
		}
	}
	
	
}

int isEndOfMultilineComment(char* line) {
	// strlen - 1 because I'm accessing i + 1
	int size = strlen(line);
	for (int i = 1; i < size; i++) {
		// find index of either "//" or "/*"
		if (line[size - i] == '/' &&  
			line[size - i - 1] == '*') {
			// return index of last character
			//printf("the index of last character in multiline is:%i \n", size-i-1);
			return size - i - 1;
		}
	}
	// not end of multiline comment
	return -1;
}
// when it is a middle line in a multiline comment
void printMultiLineComment(char* line) {
	//printf("line is: %s\n", line );
	// clear whitespace and *
	for (int i = 0; i < strlen(line); i++) {
		if (line[i] != ' ' && line[i] != '*' && line[i] != '\n') {
			char* output = malloc(strlen(line) - (i + 1));
			output = strncpy(output, line + i, strlen(line) - (i + 1));

			if (strlen(output) > 0) {
				// add the terminating \n
				output[strlen(output)] = '\n';
				// strip comments
				printf("%s", output); 
			}

			break;
		}
	}

	// if it is an empty line, do not do anything
}

void printLastLineOfMultiline(char* line, int indexEndMark) {
	int indexStart = 0;
	int indexEnd = getIndexOfContentEnd(line, indexStart, indexEndMark);

	if (indexEnd != -1) {
		char* output = malloc(indexEnd - indexStart);

		output = strncpy(output, line + indexStart, indexEnd - indexStart);

		// check if output is more than just whitespace
		if (strlen(output) > 0) {
			// add the terminating \n
			output[strlen(output)] = '\n';

			// strip comments
			printf("%s", output); 
		}
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

	// auxiliary bool 
 	bool isMultiLineComment = false;

	/* note that fgets don't strip the terminating \n, checking its
           presence would allow to handle lines longer that sizeof(line) */
 	while (fgets(line, sizeof(line), file)) {
        if (isMultiLineComment) {
        	// in case it is end of line comment
        	if (isEndOfMultilineComment(line) != -1) {
        		//printf("TRUE - It is end of comment\n");
        		isMultiLineComment = false;
				printLastLineOfMultiline(line, isEndOfMultilineComment(line));
 			} else { // else it is not end of comment
 				// in case it is a multiline comment
 				//printf("TRUE - It is a multilinecomment\n");
 				printMultiLineComment(line);
 			}

        } else {
	        //TODO check if "//" or "/*" comes first
	 		// check if it is a comment
	 		if (strstr(line, "//")) {
	 			printCommentedLine(line);

	        	//TODO free ouput
	 		} else if (strstr(line, "/*")) {
	 			// in case it is a one line /* xyz */
	 			if (isEndOfMultilineComment(line) != -1) {
	 				//printf("FALSE - /*xyz*/ case\n");
	 				printOneLineComment(line, isEndOfMultilineComment(line));
	 			} else {
	 				//printf("FALSE - /* case\n");
	 				isMultiLineComment = true;
	 				printCommentedLine(line);
	 			}
	 		}
        }
 		
    }
	// close line
	fclose(file);

	return 0;
}
