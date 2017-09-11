#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <ctype.h>

#define C_PLUS_COMMENT 0
#define C_ASTERISK_COMMENT 1

/* removes a tag */
void removeTag(int type) {
	int ch;
    int lastChar = '@';
    int lastLastChar = '@';

    // ignore all characters until you see and endofline or blank space
	while ((ch = getchar()) != EOF) {

		// if C asterisk comment, break out of the loop if */
        if (lastLastChar == '*' && lastChar == '/' && type == C_ASTERISK_COMMENT) {
             ungetc(lastChar, stdin);
             ungetc(lastLastChar,stdin);

             break;
        } 
        else if (ch == ' ' || ch == '\n') { // if you find a blank space or endofline, break loop and put back character
            ungetc(ch, stdin);
            break;
        } else {
            // just keep track of last chars, but do not write it to stdout
            lastLastChar = lastChar;
            lastChar = ch;
        }
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
				removeTag(type);
				continue;

			} else if (ch == '\n' && type == C_ASTERISK_COMMENT) { // in case it is a multiline comment, ignore empty line
                continue;
            } else {
                // unget last character and move back to main loop now that all the trailing shitespace is gone
                ungetc(ch, stdin);
                // break loop
                break;
            }
           
		} else if (ch == '*') { // for multiline comments
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
    int lastChar;
	// only stop when ch reaches EOF or end of string 
	while ((ch = getchar()) != EOF) {

        // break out of the loop whn you find the end of the string
         if (ch == '\"' && lastChar != '\\') {
            break;
        }

		// do nothing but keep track of last char 
        lastChar = ch;
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
                        removeTag(C_PLUS_COMMENT);
                    } else { // else, it is a regular character, just write to stdout
                        putchar(commuteChar);

                        // if commute char is a blank space
                        previousIsWhiteSpace = (commuteChar == ' ');
                    }
    				
    			}

                // if EOF while writing comment, make new line
                if (commuteChar == EOF) {
                    putchar('\n');
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

                         } else if (nextCommuteChar == '*') { // check again
                            putchar(commuteChar);
                            ungetc(nextCommuteChar, stdin);


                         } else { // it was not end of line
                            putchar(commuteChar);                          
                            ungetc(nextCommuteChar, stdin);

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
                        removeTag(C_ASTERISK_COMMENT);

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
