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
#include "analyze.h"

void checkError(int status,int line)
{
	if (status < 0) {
		printf("socket error(%d)-%d: [%s]\n",getpid(),line,strerror(errno));
		exit(-1);
	}
}

char* readResponse(int sid)
{
	size_t sz = 8;
	char* buf = malloc(sizeof(char)* sz);
	int done = 0,received = 0;  
	while (!done) {
		int nbb = read(sid,buf + received,sz - received);
		if (nbb > 0)
			received += nbb;
		else if (nbb == 0)
			done = 1;
		if (received == sz) {
			buf = realloc(buf,sz * 2);
			sz  *= 2;
		}
	}
	if (received == sz)
		buf = realloc(buf,sz + 1);
	buf[received] = 0;
	return buf;
}

int main(int argc,char* argv[])
{
	// Create a socket
	if (argc < 2) {
		printf("Usage is: wgettext <url>\n");
		return 1;
	}
	char host[512];
	int  port = 80;
	char url[512];
	analyzeURL(argv[1],host,&port,url);
	printf("[%s] [%d] [%s]\n",host,port,url);
	



	//PF_INET means internet socket
	//SOCK_STREAM means TCP socket
	int sid = socket(PF_INET, SOCK_STREAM, 0);
	struct sockaddr_in srv;
	struct hostent *server = gethostbyname(host);
	srv.sin_family = AF_INET;
	srv.sin_port = htons(port);
	memcpy(&srv.sin_addr.s_addr, server->h_addr, server->h_length);
	int status = connect(sid, (struct sockaddr*)&srv, sizeof(srv));
	checkError(status, __LINE__);

	int offset = 6;
	int urlLen = strlen(url);
	char buf[urlLen + offset];
	char gs[] = "GET ";
	for(int i = 0; i < strlen(gs); i++)
		buf[i] = gs[i];
	for(int i = 0; i < urlLen; i++){
		buf[i + strlen(gs)] = url[i];
	}
	buf[urlLen + offset - 2] = '\n';
	buf[urlLen + offset - 1] = '\0';

	status = send(sid, buf, sizeof(buf), 0);
	checkError(status, __LINE__);

	char* response = readResponse(sid);

	printf("%s\n", response);

	return 0;



	
	// TODO: Finish the function!
	/* Namely: send the request via a GET (see PDF)
	   retrieve the response 
	   display it on the standard output
	   */
	return 0;
}


