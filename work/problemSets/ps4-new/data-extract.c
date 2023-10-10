#include <stdlib.h>
#include <stdio.h>

void my_error(char *s)
{
	// print our own error message to standard error output
	fprintf(stderr, "Error:%s\n", s);
	// Use perror() to print the descriptive message about the error
	perror("errno");
	exit(EXIT_FAILURE);
}

/* This function copy integers from file infp to file outfp.
 * The integers copied are specified by start and end.  
 *
 * For example, 
 * start is 0, end is 0. 
 *      The first int in infp is copied to outfp. 
 * start is 10, end is 20. 
 *      11 integers are copied from infp to outfp, starting from integer 10.
 *
 * Functions that may be used in this function include
 * fseek(), fread(), fwrite(). 
 *
 * Check the return values of function calls.
 *
 * Return values:
 * 0:   success
 * -1:  function calls failed
 * */
int copy_integers(FILE *outfp, FILE *infp, int start, int end)
{
	//CODE FROM LOCAL TEST
	//read from input file into str
//	char str[n4];
//	fread(str, sizeof(char), n4, input);
//
	//write from str to output file
//	fwrite(str, sizeof(char), n4, output);
	//END LOCAL TEST CODE



	int intsz = sizeof(int);
	if (fseek(infp, start*intsz, SEEK_SET) != 0)
		return -1;
	int n = end-start+1;
	int str[n];

	if(fread(str, intsz, n, infp) != n)
		return -1;
	if(fwrite(str, intsz, n, outfp) != n)
		return -1;

	return 0;
}

int main(int argc, char *argv[])
{
	if (argc < 4) {
		fprintf(stderr, "Usage: %s <input-filename> <output-filename> range [range ..]\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	FILE    *infp, *outfp;
	infp = fopen(argv[1], "r");
	if (infp == NULL)
		my_error("Cannot open input file.");
	outfp = fopen(argv[2], "w");
	if (outfp == NULL)
		my_error("Cannot open output file.");


	for (int i = 3; i < argc; i ++) {
		int start, end;

		// example of using sscanf()
		if (sscanf(argv[i], "%d-%d", &start, &end) != 2) {
			if (sscanf(argv[i], "%d", &start) != 1) 
				my_error("Invalid range");
			end = start;
		}

		if (start < 0 || end < 0 || end < start) 
			my_error("start and end must be >= 0 and start must be <= end");
		if (copy_integers(outfp, infp, start, end)) 
			my_error("copy_integers() reteurned a non-zero value.");
	} 

	if (fclose(infp) != 0)
		my_error("Cannot close input file.");
	if (fclose(outfp) != 0)
		my_error("cannot close output file.");
	
	return 0;
}
