#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


#include <string.h>

#define READEND 0
#define WRITEEND 1

int main(int argc,char* argv[])
{
	int fd[2];
	pipe(fd);
	int fd2[2];
	pipe(fd2);
	pid_t child = fork();
	if(child == 0){
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		pid_t child2 = fork();
		if(child2 == 0){
			close(fd2[0]);
			dup2(fd2[1], STDOUT_FILENO);
			close(fd2[1]);
			//exec first command
			execlp("ls", "ls", "/dev", NULL);
		}
		if(child2 > 0){
			close(fd2[1]);
			//exec second command
			execlp("xargs", "xargs", NULL);
		}
	}
	if(child > 0){
		printf("in parent\n");
		close(fd[1]);
		close(fd2[0]);
		close(fd2[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		//exec third command
//		char* f = (char*)malloc(20);
		char f[4096];
		for(int i = 0; i < 4096; i ++)
			f[i] = 0;
//		memset(f, 0, 20);
		f[0] = '-';
		f[1] = 'f';
		int offset = strlen(f);
		for(int i = 0; i < strlen(argv[1]); i++){
			f[i+offset] = argv[1][i];
		}
		offset = strlen(f);
		f[offset] = '-';
		offset = strlen(f);
		for(int i = 0; i < strlen(argv[1]); i++){
			f[i+offset] = argv[2][i];
		}

		printf("%s\n", f);
		execlp("cut", "cut", "-d", " ", f, NULL);
//		free(f);
	}
	/* TODO: Q1
	   Implement "ls /dev | xargs | cut -d ' ' -f<a>-<b>" 
	   where <a> and <b> are from the command line
	   The use of system is prohibited.
	   */
	return 0;
}


