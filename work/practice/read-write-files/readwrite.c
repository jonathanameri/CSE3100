#include <stdio.h>
#include <stdlib.h>


int main(int argc,char *argv[])
{
	if (argc < 4){
		printf("Usage: <input-filename> <output-filename> <n>\n");
		exit(EXIT_FAILURE);
	}
	//open files and set variables from standard input
	FILE *input, *output;
	input = fopen(argv[1], "r");
	output = fopen(argv[2], "w");
	int n = atoi(argv[3]);
	int n4 = 4*n;

	//read from input file into str
	char str[n4];
	fread(str, sizeof(char), n4, input);
	printf("%s\n", str);

	//write from str to output file
	fwrite(str, sizeof(char), n4, output);


	fclose(input);
	fclose(output);
	return 0;
}
