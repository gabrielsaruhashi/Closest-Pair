#include <stdio.h>
#include <assert.h>

/* ignores all trailing spaces and asterisks*/
void removeTrailingStuff() {
	int ch;

	while ((ch = getchar()) != EOF) {
		if (ch != ' ' &&
			ch != '*') {
			// put last character back to be read by main function
			ungetc(ch, stdin);
			// break if
			break;
		}
	}
}

void removeTag() {
	int ch;

	while ((ch = getchar()) != EOF &&
		ch != ' ') {
		// do nothing
	}
	// put back space
	if (ch == ' ') {
		ungetc(ch, stdin);
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
int main()
{
  int ch;
  int nextChar;
  int commuteChar;
  int supportCommuteChar;

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
    			// write to stout until it reaches the end of commented line
    			while ((commuteChar = getchar()) != EOF) {
    				if (commuteChar != '\n' &&
    					commuteChar != '@') {
    					putchar(commuteChar);
    				} else if (commuteChar == '@') {
    					// check if next char is a word char, which indicates it is a tag
    					if ((supportCommuteChar = getchar()) != EOF &&
    						supportCommuteChar != ' ') {
    						removeTag();
    					// handles case when there is an isolated '@' in a comment
    					} else if (supportCommuteChar == ' ') {
    						putchar(supportCommuteChar);
    					}
    				} else { // if it reaches end of comment, break the while loop
    					putchar('\n');
    					break;
    				}
    				
    			}
    		} else if (nextChar == '*') {
    			removeTrailingStuff();
    		}
    	}

    }
}
