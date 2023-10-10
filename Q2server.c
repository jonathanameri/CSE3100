#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <dirent.h>

/* prints the error that is encountered and terminate the program */
void checkError(int status,int line)
{
	if (status < 0) {
		printf("socket error(%d)-%d: [%s]\n",getpid(),line,strerror(errno));
		exit(-1);
	}
}

/* creates a server-side socket that binds to the given port number and listens for TCP connect requests */
int bindAndListen(int port)
{
	int sid = socket(PF_INET,SOCK_STREAM,0);
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port   = htons(port);
	addr.sin_addr.s_addr = INADDR_ANY;
	int status = bind(sid,(struct sockaddr*)&addr,sizeof(addr));
	checkError(status,__LINE__);
	status = listen(sid,10);
	checkError(status,__LINE__);
	return sid;
}

/* reaps dead children */
void cleanupDeadChildren()
{
	int status = 0;
	pid_t deadChild; // reap the dead children
	do {
		deadChild = waitpid(0,&status,WNOHANG);
		if (deadChild > 0)
			printf("Reaped %d\n",deadChild);
	} while (deadChild > 0);
}

int main(int argc,char* argv[])
{
	/* Create two sockets: one to receive SQL commands (port 9000) and another for service (port 9001)*/
	int sid = bindAndListen(9000);
	int srv = bindAndListen(9001);

	int max;
	if(sid > srv)
		max = sid;
	if(srv > sid)
		max = srv;
	fd_set afd;
	FD_ZERO(&afd);
	FD_SET(sid, &afd);
	FD_SET(srv, &afd);
	while(1) {
		int nbReady = select(max+1,&afd, NULL, NULL, NULL);
		if(nbReady > 0){
			if(FD_ISSET(sid, &afd)){
				execlp("sqlite3", "sqlite3", "foobar.db", NULL);
				cleanupDeadChildren();
			}
			if(FD_ISSET(srv, &afd)){
				break;
			}
		}
		/* TODO: Q2.3 
		 *  Listen for input on both sockets.
		 *  If a client connects to port 9000, run a unique instance of SQLite to respond to SQLite queries from the client. Reap dead children using cleanupDeadChildren.
		 *       The executable for SQLite is sqlite3 that takes as argument a database foobar.db.
		 *       Note that if you are coding this on your localhosts, you may need to install SQLite using 'sudo apt install sqlite3'.
		 *  If a client connects to port 9001, compare the received string with '$die!'. If it matches, terminate the server process.
		 */
	}
	close(srv);
	close(sid);
	cleanupDeadChildren();
	printf("terminated...\n");
	return 0;
}
