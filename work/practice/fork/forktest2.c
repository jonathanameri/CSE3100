#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>


int main(){
	pid_t child = fork();
	if (child == 0){
		printf("I am the child!\n");
		//for execl, you must include the executable twice
		//because the executable is technically the first
		//argument in the standard input
		execl("./adder","./adder","1","2","3","4",NULL);
	}
	else{
		printf("I am the parent!\n");
		execl("./adder","./adder","100","200","300",NULL);
	}
	return 0;

}
