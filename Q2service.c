#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <errno.h>
#include <assert.h>

/* prints the error that is encountered and terminate the program */
void checkError(int status,int line)
{
	if (status < 0) {
		printf("socket error(%d)-%d: [%s]\n",getpid(),line,strerror(errno));
		exit(-1);
	}
}

int main(int argc,char* argv[]) 
{
	if (argc < 2) {
		printf("usage is: Q2service <hostname>\n");
		return 1;
	}

	/* Connect to the server hosted on <hostname> (read as command line argument) on port 9001. */
	char* hostname = argv[1];
	int sid = socket(PF_INET,SOCK_STREAM,0);
	struct sockaddr_in srv;
	struct hostent *server = gethostbyname(hostname);
	srv.sin_family = AF_INET;
	srv.sin_port   = htons(9001);
	memcpy(&srv.sin_addr.s_addr,server->h_addr,server->h_length);
	int status = connect(sid,(struct sockaddr*)&srv,sizeof(srv));
	checkError(status,__LINE__);

	char buf[] = "$die!";
	write(sid, buf, strlen(buf)); 
	/* TODO: Q2.1 
	 * Send the string '$die!' to the server.
	 */

	return 0;
}
