#define BUFFER_SIZE 20
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
void write_message(char * message, int fd) {
	printf("here");
	write(fd, message, sizeof(*message));
}
char* read_message(int fd) {
	char *buffer = (char*)malloc(sizeof(char)*BUFFER_SIZE);
	int i = 0;
	while(read(fd, buffer + i, 1) != 0){
		i++;
		if (i == sizeof(buffer))
			buffer = (char*)realloc(buffer, sizeof(buffer)*2);
		if (buffer[i-1] == '\n')
			break;
	}
	buffer[i] = 0;
	return buffer;
}

void encrypt2(char * message) {
	for(int i=0;i<strlen(message);i++) {
		if(message[i] == '\n') break;
		message[i] += 1;
	}

}
void decrypt(char * message) {
	for(int i=0;i<strlen(message);i++) {
		if(message[i] == '\n') break;
		message[i] -= 1;
	}
}



int main() {
	// Set up pipes
	int pTOc1[2], c1TOc2[2], c2TOp[2];
	pipe(pTOc1);
	pipe(c1TOc2);
	pipe(c2TOp);

	// Create Pipes
	pid_t pid1 = fork();
	if (pid1 == 0) {
		// Child 1
		char* msg;

		close(pTOc1[1]);
		close(c1TOc2[0]);
		close(c2TOp[0]);
		close(c2TOp[1]);
		// TODO: Close Unneeded Pipes
		
		msg = read_message(pTOc1[0]);
		printf("Child 1 is Encrypting!\n");
		encrypt2(msg);
		write_message(msg,c1TOc2[1]);

		close(pTOc1[0]);
		close(c1TOc2[1]);
		// TODO: Close Remaining Pipes

		exit(0);
	} else {
		pid_t pid2 = fork();
		if (pid2 ==0) {
			// Child 2
			char* msg;

			close(c1TOc2[1]);
			close(c2TOp[0]);
			close(pTOc1[0]);
			close(pTOc1[1]);
			// TODO: Close Unneeded Pipes
			msg = read_message(c1TOc2[0]);
			printf("Child 2: %s", msg);
			write_message(msg, c2TOp[1]);

			close(c1TOc2[0]);
			close(c2TOp[1]);
			// TODO: Close Remaining Pipes
			exit(0);
		} else {
			// Parent
			char * msg = "This is a test.\n";

			close(pTOc1[0]);
			close(c2TOp[1]);
			close(c1TOc2[0]);
			close(c1TOc2[1]);
			//TODO: Close Unneeded Pipes
			printf("Parent: %s", msg);
			printf("here2");
			write_message(msg,pTOc1[1]);
			msg = read_message(c2TOp[0]);
			decrypt(msg);
			printf("Parent: %s", msg);
			printf("here3");

			close(pTOc1[1]);
			close(c2TOp[0]);
			free(msg);
			// TODO: Close Remaining Pipes and free the msg
			return 0;
		}

	}
}
