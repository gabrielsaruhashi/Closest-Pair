#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

/* removes a tag */
void removeTag() {
	int ch;

    // ignore all characters until you see and endofline or blank space
	while ((ch = getchar()) != EOF) {

		// if you find a blank space or endofline, break loop and put back character
        if (ch == ' ' || ch == '\n') {
            ungetc(ch, stdin);
            break;
        }
        // else, do nothing with the character
	}
    


}

/* ignores all trailing spaces, asterisks, tags, and tabs until you find a valid character */
void removeTrailingStuff() {
	int ch;
    // ignores blank spaces, asterisks, and 
	while ((ch = getchar()) != EOF) {
		if (ch != ' ' &&
			ch != '*' &&
            ch != '\t') {
			// if char indicates beginning of a tag, remove tag and continue loop
			if (ch == '@') {
				removeTag();
				continue;

			}

            /* DANGEREUX FIX, a blank CC comment might break this 
            * only do it for multiline comment */ 
            // if it is the end of line character, move to next line
            if (ch == '\n') {
                continue;
            } else {
                ungetc(ch, stdin);
            }
           
            
			
			// break loop
			break;
		}

	
	}
}

/* in case we find a string outside of a comment, ignore all its characters, eg: "// dummy comment" */
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
    }
}
int main()
{
  int ch;
  int nextChar;
  int supportCommuteChar;
  int commuteChar;
  int nextCommuteChar;
  // boolean to track white space in case of tag
  bool isWhiteSpace;

  while ((ch = getchar()) != EOF)
    {
    	// CASE: string - recognize beginning of string
    	if (ch == '\"') {
    		// ignore everything until end of string
    		ignoreString();
    	}
    	// recognize a possible beginning of a comment
    	if (ch == '/') {

    		// CASE C++ Comment - if "//", just print everything until the end of the line
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
    		} else if (nextChar == '*') { // CASE - Asterisk C comment
    			// remove trailing stuff
    			removeTrailingStuff();

                // handles the case when it is an empty comment
                if ((supportCommuteChar = getchar()) == EOF ||
                    supportCommuteChar == '/') {
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
