#include <stdio.h>
#include <assert.h>

/* ignores all trailing spaces */
void removeTrailingStuff() {
	int ch;

	while ((ch = getchar()) != EOF) {
		if (ch != ' ' &&
			ch != '*') {
			// put character back to be read by main function
			ungetc(ch, stdin);
			// break if
			break;
		}
	}
}
int main()
{
  int ch;
  int nextChar;
  int commuteChar;
  while ((ch = getchar()) != EOF)
    {
    	// recognize the beginning of a comment
    	if (ch == '/') {
    		// determine which type of comment it is

    		// if "//", just print everything until the end of the line
    		if ((nextChar = getchar()) == '/') {
    			// remove trailing spaces and *
    			removeTrailingStuff();
    			// write to stout until it reaches the end of commented line
    			while ((commuteChar = getchar()) != EOF) {
    				if (commuteChar != '\n') {
    					putchar(commuteChar);
    				} else { // if it reaches end of comment, break the while loop
    					putchar('\n');
    					break;
    				}
    				
    			}
    		}
    	}

    }
}
