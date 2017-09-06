#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

void removeTag() {
	int ch;

	// handles the case when it is an isolated tag
	if ((ch = getchar()) == ' ') {
		putchar('@');
		putchar(ch);

	} else {
		while ((ch = getchar()) != EOF &&
			ch != ' ') {
			// do nothing
		}

		// put back space
		if (ch == ' ') {
			ungetc(ch, stdin);
		}
	}

}

/* ignores all trailing spaces, asterisks, tags, and tabs until you find a valid character */
void removeTrailingStuff() {
	int ch;

	while ((ch = getchar()) != EOF) {
		if (ch != ' ' &&
			ch != '*' &&
            ch != '\t') {
			// check if char is not a tag
			if (ch == '@') {
				removeTag();
				continue;

			}
            

            ungetc(ch, stdin);
            
			
			// break loop
			break;
		}

	
	}
}

void ignoreString() {
	int ch;
	// only stop when ch reaches EOF or end of string 
	while ((ch = getchar()) != EOF &&
		ch != '\"' ) {
		// do nothing
	}
}

void writeMultilineComment() {
    int ch;
    putchar('\n');
    removeTrailingStuff();
    // handle case when it is an empty multiline comment
    if ((ch = getchar()) != '\n') { // ignore newline if empty comment
        ungetc(ch, stdin);
    } else {
        printf("It is an empty line\n");
    }
}
int main()
{
  int ch;
  int nextChar;
  int supportCommuteChar;
  int commuteChar;
  int nextCommuteChar;

  while ((ch = getchar()) != EOF)
    {
    	// recognize beginning of string
    	if (ch == '\"') {
    		// ignore everything until end of string
    		ignoreString();
    	}
    	// recognize a possible beginning of a comment
    	if (ch == '/') {

    		// if "//", just print everything until the end of the line
    		if ((nextChar = getchar()) == '/') {
    			// remove trailing spaces and *
    			removeTrailingStuff();
    			// handle case when comment is empty OR only with leading spaces
    			if ((supportCommuteChar = getchar()) == EOF ||
    				supportCommuteChar == '\n') {
    				continue;
    			} else {
    				ungetc(supportCommuteChar, stdin);
    			}

    			// write to stout until it reaches the end of commented line
    			while ((commuteChar = getchar()) != EOF) {
    				if (commuteChar != '\n' &&
    					commuteChar != '@') {
    					putchar(commuteChar);
    				} else if (commuteChar == '@') {
    					// check if next char is a word char, which indicates it is a tag
    					removeTag();
    				} else { // if it reaches end of comment, break the while loop
    					putchar('\n');
    					break;
    				}
    				
    			}
    		} else if (nextChar == '*') { // beginning of comment
    			// remove trailing stuff
    			removeTrailingStuff();

                // handles the case when it is an empty comment
                if ((supportCommuteChar = getchar()) == EOF ||
                    supportCommuteChar == '/') {
                    printf("Empty Comment in Main \n");
                    continue;
                } else { // else put it back de
                    ungetc(supportCommuteChar, stdin);
                }
                // write to stoout until it reaches the end of commented line
                while ((commuteChar = getchar()) != EOF) {
                    
                    if (commuteChar == '*') { // it might be the end of line
                         if ((nextCommuteChar = getchar()) == '/') { // end of comment
                            // newline
                            putchar('\n');
                            //TODO remove trailing spaces
                            break;
                         } else if (nextCommuteChar == EOF) { // protect yourself against EOF
                            continue; 
                         } else if (nextCommuteChar == '\n') {
                            writeMultilineComment();
                         } else { // it was not end of line
                            putchar(commuteChar);
                            putchar(nextCommuteChar);
                         }
                    // if it reaches end of line, remove trailing of new line
                    } else if (commuteChar == '\n') { 
                        putchar(commuteChar);
                        // remove trailing stuff of new line
                        removeTrailingStuff();

                        // if new line is an empty comment, with end of comment
                        // eg: *****/
                         if ((nextCommuteChar = getchar()) == '/' ||
                         nextCommuteChar == EOF) { // ignore char and break loop
                            break;
                         } else {
                            ungetc(nextCommuteChar, stdin);
                         }
                        //writeMultilineComment();

                    } else { // just keep writing to stdout
                        putchar(commuteChar);
                    }
                }
    		}
    	}

    }
}
