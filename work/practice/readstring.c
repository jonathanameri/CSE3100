#include <stdio.h>
#include <stdlib.h>


char* readString()
{
        char* string = (char*)malloc(sizeof(char));
        char cc;
        int n = 0;
        while(scanf("%c", &cc) != -1){
                string[n] = cc;
                n++;
                string = (char*)realloc(string, sizeof(char)*(n*2));
        }
        return string;



}
int main(){
	printf("%s", readString());
	return 0;

}

