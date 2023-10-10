#include <stdio.h>
#include <stdlib.h>

int main(){
	int* p = (int*)malloc(sizeof(int)*10);
	int w = 42;
	for(int i = 0; i<10;i++){
		printf("%p\n",(p+i));
	}
	printf("%p\n",&w);
	return 0;
}
