#include "hamming.h"

/* Q3: Write a test program that reads two strings from the standard input (of arbitrary lengths)
       and compute their hamming distance. The user input is not guaranteed to give strings
       of the same length!
       
       Your code cannot have memory leaks or memory corruptions. We will check with valgrind.

   Example:
   input:
   qwerty uiop asdf
   qwerty ui0p a3df
   output:
   hd:2

   Don't forget to handle the case of inputs of different lengths.
*/

int main()
{
	char* string1 = readString();
	char* string2 = readString();

	printf("hd:%d\n", computeHD(string1, string2));
	free(string1);
	free(string2);
	
   return 0;
}
