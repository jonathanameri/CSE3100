#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <dirent.h>

void checkError(int status)
{
   if (status < 0) {
      printf("socket error(%d): [%s]\n",getpid(),strerror(errno));
      exit(-1);
   }
}

int main(int argc,char* argv[])
{
   // Create a socket
   int sid = socket(PF_INET,SOCK_STREAM,0);
   // setup our address -- will listen on 8080 --
   struct sockaddr_in addr;
   addr.sin_family = AF_INET;
   addr.sin_port   = htons(9000);
   addr.sin_addr.s_addr = INADDR_ANY;
   int status = bind(sid,(struct sockaddr*)&addr,sizeof(addr));
   checkError(status);
   status = listen(sid,10);
   checkError(status);

   while(1) {
      struct sockaddr_in client;
      socklen_t clientSize = sizeof(client);
      int chatSocket = accept(sid,(struct sockaddr*)&client,&clientSize);
      checkError(chatSocket);
      printf("We accepted a socket: %d\n",chatSocket);

      int id = fork();
      if (id == 0) {
         close(fileno(stdout));
         dup(chatSocket);
         close(chatSocket);
         execl("/usr/bin/who","/usr/bin/who",NULL);
         
      } else {
         // I'm the parent...
         close(chatSocket);
         pid_t theChild = wait(&status);
      }
      // TODO!!!!!
      
   }
   return 0;
}
