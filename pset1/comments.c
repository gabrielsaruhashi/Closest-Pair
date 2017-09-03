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

/* ignores all trailing spaces and asterisks*/
void removeTrailingStuff() {
	int ch;

	while ((ch = getchar()) != EOF) {
		if (ch != ' ' &&
			ch != '*') {
			// check if char is not a tag
			if (ch == '@') {
				removeTag();
				continue;

			}
			// put last character back to be read by main function
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
int main()
{
  int ch;
  int nextChar;
  int supportCommuteChar;
  int commuteChar;

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
    		} else if (nextChar == '*') {
    			// remove trailing stuff
    			removeTrailingStuff();
    		}
    	}

    }
}
