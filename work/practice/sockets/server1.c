#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <dirent.h>

void checkError(int status){
	if (status < 0){
		printf("Error: [%s]\n", strerror(errno));
		exit(-1);
	}
}

void handleNewConnection(int chatSocket);

int main(int argc, char *argv[]){
	//sid is a file descriptor
	int sid = socket(PF_INET, SOCK_STREAM, 0);	

	//addr that we want to bind the socket to
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8080);
	addr.sin_addr.s_addr = INADDR_ANY;
	
	//bind socket sid to the address
	int status = bind(sid, (struct sockaddr*)&addr, sizeof(addr));
	checkError(status);

	//listen to the socket for incoming requests
	//up to 10 clients to talk to at a time
	//anything past 10 clients will be rejected
	status = listen(sid, 10);
	checkError(status);

	while(1){
		struct sockaddr_in client;
		socklen_t clientSize;
		int chatSocket = accept(sid, (struct sockaddr*)&client, &clientSize);
		checkError(chatSocket);
		printf("Accepted socket: %d\n", chatSocket);

		//We need to fork so that the server can go back
		//to listening for more clients
		pid_t child = fork();
		if (child == 0){
			handleNewConnection(chatSocket);
			close(chatSocket);
			return 1;
		}
		else if(child > 0){
			printf("Created a chi;d: %d\n", child);
			close(chatSocket);
			int status = 0;
			pid_t deadChild;
			do {
				deadChild = waitpid(0, &status, WNOHANG);
				checkError(deadChild);
				if (deadChild > 0)
					printf("Reaped %d\n", deadChild);
			} while (deadChild > 0);
		}
	}
	return 0;
}



void handleNewConnection(int chatSocket){
	//child process
	int done = 0;
	char buf[256];
	char msg[] = "Howdy!";
	int status = recv(chatSocket, &buf, sizeof(buf), 0);
	checkError(status);
	printf("Client said   : [%s]\n", buf);
	printf("I'm responding: [%s]\n", msg);
	//length must be strlen(msg)+1 to ensure that the
	//null character is included: '\0'
	status = send(chatSocket, msg, strlen(msg)+1,0);
	checkError(status);
}
