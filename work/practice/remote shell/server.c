#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <dirent.h>

void checkError(int status)
{
	if (status < 0) {
		printf("socket error(%d): [%s]\n",getpid(),strerror(errno));
		exit(-1);
	}
}

void spawnWorker(int sid);

int main(int argc,char* argv[]) 
{
	// Create a socket
	int sid = socket(PF_INET,SOCK_STREAM,0);

	// Make the **server-side** socket non-blocking
	int flags = fcntl(sid, F_GETFL, 0);
	checkError(flags);
	flags = flags | O_NONBLOCK;
	int status = fcntl(sid, F_SETFL, flags);
	checkError(status);
	int enable = 1;
	status = setsockopt(sid, SOL_SOCKET,
			SO_REUSEADDR, &enable, sizeof(int));
	checkError(status);

	// setup our address -- will listen on 8025 --
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port   = htons(8025);
	addr.sin_addr.s_addr = INADDR_ANY;
	//pairs the newly created socket with the requested address.
	status = bind(sid,(struct sockaddr*)&addr,sizeof(addr));
	checkError(status);
	// listen on that socket for "Let's talk" message. No more than 10 pending at once
	status = listen(sid,10);
	checkError(status);
	while(1) {
		fd_set afd;
		FD_ZERO(&afd);
		FD_SET(STDIN_FILENO,&afd);
		FD_SET(sid,&afd);
		int nbReady = select(sid+1,&afd,NULL,NULL,NULL);
		printf("SELECT: %d\n",nbReady);fflush(stdout);
		if (nbReady > 0) {
			if (FD_ISSET(STDIN_FILENO,&afd)) {
				char buf[512];
				scanf("%s",buf);
				if (strcmp(buf,"die!") == 0)
					break;
			}
			if (FD_ISSET(sid,&afd)) {
				spawnWorker(sid);
			} else {
				printf("oopsies... %d\n",nbReady);
			}
		}      
	}
	close(sid);
	return 0;
}

void spawnWorker(int sid)
{
	struct sockaddr_in client;
	socklen_t clientSize = sizeof(client);
	printf("Call accept...\n");fflush(stdout);
	int rshSocket = accept(sid,(struct sockaddr*)&client,&clientSize);
	checkError(rshSocket);
	printf("We accepted a socket: %d\n",rshSocket);
	pid_t child = fork();
	if (child == 0) {
		dup2(rshSocket,STDIN_FILENO);
		dup2(rshSocket,STDOUT_FILENO);
		dup2(rshSocket,STDERR_FILENO);
		close(rshSocket);
		int error = execlp("sqlite3","sqlite3",NULL);
		checkError(error);
	} else if (child > 0) {
		printf("Created a child: %d\n",child);
		close(rshSocket);		
		int status = 0;
		pid_t deadChild; // reap the dead (as long as we find some)
		do {
			deadChild = waitpid(0,&status,WNOHANG);
			checkError(deadChild);
			if (deadChild > 0)
				printf("Reaped %d\n",deadChild);
		} while (deadChild > 0);
		printf("Done reaping...\n");fflush(stdout);
	} 
}
