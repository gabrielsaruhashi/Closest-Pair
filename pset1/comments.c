#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

#define C_PLUS_COMMENT 0
#define C_ASTERISK_COMMENT 1
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
bool removeTrailingStuff(int type) {
	int ch;
    bool lastCharIsAsterisk;
    // TEST 12 PROBLEM, PUT BACK CHECK FOR EMPTY COMMENT? SOLUTION: HAVE TOW TYPES OF REMOVE TRAILING STUFF
    // ignores blank spaces, asterisks, and 
	while ((ch = getchar()) != EOF) {
		if (ch != ' ' &&
			ch != '*' &&
            ch != '\t') {
			// if char indicates beginning of a tag, remove tag and continue loop
			if (ch == '@') {
                lastCharIsAsterisk = false;
				removeTag();
				continue;

			} else if (ch == '\n' && type == C_ASTERISK_COMMENT) { // in case it is a multiline comment, ignore empty line
                continue;
            } else {
                // unget last character and move back to main loop now that all the trailing shitespace is gone
                ungetc(ch, stdin);
                // break loop
                break;
            }
           
		} else if (ch == '*') {
            lastCharIsAsterisk = true;
        } else {
            lastCharIsAsterisk = false;
        }
	}
     
    return lastCharIsAsterisk;
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



int main()
{
  int ch;
  int nextChar; // only used to check for a '*' or '/' after a '/' is seen
  int supportCommuteChar; // only used to check if it an empty comment
  int commuteChar; // variable used to store characters after beginning of comment is identified
  int nextCommuteChar;
  int lastChar;

  while ((ch = getchar()) != EOF)
    {
    	// CASE: string - recognize beginning of string
    	if (ch == '\"') {
    		// ignore everything until end of string
    		ignoreString();
    	}
    	// recognize a possible beginning of a comment
    	if (ch == '/') {

            bool previousIsWhiteSpace;

    		// CASE C++ Comment - if "//", just print everything until the end of the line
    		if ((nextChar = getchar()) == '/') {
    			// remove trailing spaces and *
    			removeTrailingStuff(C_PLUS_COMMENT);

    			// handle case when comment is empty OR only with leading spaces
    			if ((supportCommuteChar = getchar()) == EOF ||
    				supportCommuteChar == '\n') {
    				continue;
    			} else {
    				ungetc(supportCommuteChar, stdin);
    			}

    			// write to stout until it reaches the end of commented line
    			while ((commuteChar = getchar()) != EOF) {

                    // if it reaches end of comment, break the while loop
                    if (commuteChar == '\n') {
                        putchar(commuteChar);
                        break;
                    } else if (commuteChar == '\\') {
                        if ((nextCommuteChar = getchar()) == '\n') { // ignore the the backlash newline
                            continue;
                        } else {
                            putchar(commuteChar);
                            ungetc(nextCommuteChar, stdin);
                        }
                    } else if (commuteChar == '@' && previousIsWhiteSpace == true) { // remove tag
                        removeTag();
                    } else { // else, it is a regular character, just write to stdout
                        putchar(commuteChar);

                        // if commute char is a blank space
                        previousIsWhiteSpace = (commuteChar == ' ');
                    }
    				
    			}
    		} else if (nextChar == '*') { // CASE - Asterisk C comment
    			// remove trailing stuff
    			bool lastCharIsAsterisk = removeTrailingStuff(C_ASTERISK_COMMENT);

                // handles the case when it is an empty comment
                if ((supportCommuteChar = getchar()) == EOF ||
                    (lastCharIsAsterisk && supportCommuteChar == '/')) {
                    continue;
                } else { // else unread character from stdin
                    ungetc(supportCommuteChar, stdin);
                }

                // write to stoout until it reaches the end of commented line
                while ((commuteChar = getchar()) != EOF) {
                    
                    if (commuteChar == '*') { // it might be the end of comment
                         if ((nextCommuteChar = getchar()) == '/') { // end of comment
                            // newline
                            putchar('\n');
                            break;
                         } else if (nextCommuteChar == EOF) { // protect yourself against EOF
                            putchar(commuteChar);
                            continue; 
                         } else if (nextCommuteChar == '\n') { // remove trailing space from newline
                            putchar(commuteChar);
                            putchar(nextCommuteChar);
                            removeTrailingStuff(C_ASTERISK_COMMENT);

                            // handle case when it is an empty multiline comment
                            if ((ch = getchar()) != '\n') { // ignore newline if empty comment
                                ungetc(ch, stdin);
                            }

                            continue;

                         } else { // it was not end of line
                            putchar(commuteChar);
                            putchar(nextCommuteChar);
                         }

                         // update last char
                         lastChar = nextCommuteChar;
                    // if it reaches end of line, remove trailing of new line
                    } else if (commuteChar == '\\') {
                        if ((nextCommuteChar = getchar()) == '\n') { // ignore the the backlash newline
                            continue;
                        } else {
                            putchar(commuteChar);
                            ungetc(nextCommuteChar, stdin);
                        }
                    } else if (commuteChar == '\n') { 
                      
                        putchar(commuteChar);
                        // remove trailing stuff of new line
                        bool lastCharIsAsterisk = removeTrailingStuff(C_ASTERISK_COMMENT);

                        // if new line is an empty comment, with end of comment
                        // eg: *****/
                        if (((nextCommuteChar = getchar()) == '/' && lastCharIsAsterisk) ||
                        nextCommuteChar == EOF) { // ignore char and break loop
                            break;
                        } else {
                            ungetc(nextCommuteChar, stdin);
                        }
                    
                         // update last char
                         lastChar = nextCommuteChar;

                    } else if (commuteChar == '@' && lastChar == ' ') {
                        removeTag();
                        continue;

                    } else { // just keep writing to stdout
                        putchar(commuteChar);

                        // remember last char used
                        lastChar = commuteChar;
                    }
                }
    		}
    	}

    }
}
