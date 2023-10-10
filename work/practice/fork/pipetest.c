#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){

	//fd AKA fildes means "file descriptor"
	int fd[2];
	pipe(fd);
	//fd[1] is the input side of the pipe
	//fd[0] is the output side of the pipe

	//pid_t is the ID returned by fork(),
	// it is either 0 to represent the child
	// or something else to represent the parent
	
	pid_t pid = fork();

	//what to do if you are the child
	if (pid < 0){
		fprintf(stderr, "failed to make fork");
		return -1;
	}
	else if (pid > 0){
		printf("I am the parent\n");
		close(fd[0]);
		write(fd[1], "hi", sizeof("hi"));
	}
	else{
		printf("I am the child\n");
		close(fd[1]);
		char buffer[20];
		read(fd[0], buffer, 2);
		printf("received: %s\n", buffer);
	}
	return 0;
}
