#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <errno.h>

void checkError(int status,int line)
{
   if (status < 0) {
      printf("socket error(%d)-%d: [%s]\n",getpid(),line,strerror(errno));
      exit(-1);
   }
}

char* readString(int sid);

int main(int argc,char* argv[]) 
{
   if (argc < 2) {
      printf("usage is: rup <hostname>\n");
      return 1;
   }
   char* hostname = argv[1];
   int sid = socket(PF_INET,SOCK_STREAM,0);
   struct sockaddr_in srv;
   struct hostent *server = gethostbyname(hostname);
   srv.sin_family = AF_INET;
   srv.sin_port   = htons(9000);
   memcpy(&srv.sin_addr.s_addr,server->h_addr,server->h_length);
   int status = connect(sid,(struct sockaddr*)&srv,sizeof(srv));
   checkError(status,__LINE__);

   char* str = readString(sid);
   printf("%s\n",str);
   free(str);
             
 
   return 0;
}


char* readString(int sid)
{
   int   l = 1; 
   char* s = malloc(l * sizeof(char));
   int i = 0;
   char ch;
   int status = read(sid,&ch,1);
   while (status != 0) {
      if (i == l) {
         s = realloc(s,l*2*sizeof(char));
         l *= 2;
      }
      s[i++] = ch;
      status = read(sid,&ch,1);
   }
   if (i == l) {
      s = realloc(s,l*2*sizeof(char));
      l *= 2;
   }
   s[i] = 0;
   return s;
}
