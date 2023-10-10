#include "hamming.h"

/* Q1: read a string of arbitrary length from the standard input. The string is linefeed (\n)
   terminated. Think carefully of where memory is coming from as there is no upper 
   bound on the string length.
input: none
ouput: a pointer to a buffer container the string read. It ought to be a valid string
(\0 terminated)
*/
char* readString()
{
	int mlen = 1;
	char* s = (char*)malloc(sizeof(char)*mlen);
	char c = getchar();
	int i = 0;
	while(c != '\n')
	{
		s[i] = c;
		c = getchar();
		i++;
		if (i > mlen)
		{
			mlen *= 2;
			s = (char*)realloc(s, sizeof(char)*mlen);
		}
	}
	s[i] = 0;
	return s;
}

/* Q2: compute the hamming distance between two strings. The strings are expected to be the 
   same length. The hamming distance is the number of indices where the string differ. 
input: s1 : pointer to string 1
s2 : pointer to string 2
output: integer: the number of indices where the string disagree
Note: 1. this should work for strings of any length. 
2. You can assume that s1 and s2 have the same length.
*/

int computeHD(char* s1,char* s2)
{
	int len1 = strlen(s1);
	int len2 = strlen(s2);
	int sum = 0;
	if(len1 < len2){
		sum++;
		for(int n = 0; n < len1; n++)
			sum += s1[n] != s2[n];
	}
	else if(len2 < len1){
		sum++;
		for(int n = 0; n < len2; n++)
			sum += s1[n] != s2[n];
	}
	else{
		for(int n = 0; n < len1; n++)
			sum += s1[n] != s2[n];
	}
	return sum; 
}
