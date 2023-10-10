#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/select.h>
#include <assert.h>

void checkError(int status,int line)
{
	if (status < 0) {
		printf("socket error(%d)-%d: [%s]\n",getpid(),line,strerror(errno));
		exit(-1);
	}
}

int main(int argc,char* argv[]) 
{
	// Create a socket
	if (argc < 2) {
		printf("Usage is: rsh <hostname>\n");
		return 1;
	}
	int sid = socket(PF_INET,SOCK_STREAM,0);
	struct sockaddr_in srv;
	struct hostent *server = gethostbyname(argv[1]);
	if (server==NULL) {
		printf("Couldn't find a host named: %s\n",argv[1]);
		return 2;
	}
	srv.sin_family = AF_INET;
	srv.sin_port   = htons(8025);
	memcpy(&srv.sin_addr,server->h_addr_list[0],server->h_length);
	int status = connect(sid,(struct sockaddr*)&srv,sizeof(srv));
	checkError(status,__LINE__);

	fd_set afd;
	char buf[512];
	int done = 0;
	do {
		FD_ZERO(&afd);
		FD_SET(STDIN_FILENO,&afd);
		FD_SET(sid,&afd);
		int nbReady = select(sid+1,&afd,NULL,NULL,NULL);
		if (nbReady > 0) {
			if (FD_ISSET(0,&afd)) {
				int rc = read(STDIN_FILENO,buf,sizeof(buf));
				assert(rc > 0);
				int wc = write(sid,buf,rc);
				assert(rc > 0);
			} else if (FD_ISSET(sid,&afd)) {
				int rc = read(sid,buf,sizeof(buf));
				done = rc == 0;
				if (!done) {
					int wc = write(STDOUT_FILENO,buf,rc);
					assert(rc > 0);
				}
			}
		} else done = 1;
	} while(!done);
	return 0;
}

