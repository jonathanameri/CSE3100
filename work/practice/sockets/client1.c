#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <dirent.h>
#include <netdb.h>

void checkError(int status, int line){
	if (status < 0){
		printf("Error: (%d)-%d: [%s]\n", getpid(), line, strerror(errno));
		exit(-1);
	}
}



int main(int argc, char *argv[]){
	//PF_INET means internet socket
	//SOCK_STREAM means TCP socket
	int sid = socket(PF_INET, SOCK_STREAM, 0);
	struct sockaddr_in srv;
	struct hostent *server = gethostbyname("localhost");
	srv.sin_len = sizeof(srv);
	srv.sin_family = AF_INET;
	srv.sin_port = htons(8080);
	memcpy(&srv.sin_addr.s_addr, server->h_addr, server->h_length);
	int status = connect(sid, (struct sockaddr*)&srv, sizeof(srv));
	checkError(status, __LINE__);
	char buf[] = "Hello server!";
	status = send(sid, buf, sizeof(buf), 0);
	checkError(status, __LINE__);
	char answ[256];
	status = recv(sid, answ, sizeof(answ), 0);
	printf("Response was: [%s]\n", answ);

	return 0;
}
