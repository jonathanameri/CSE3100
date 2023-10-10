#include <stdio.h>
#include <unistd.h>



int main(){
	pid_t value;
	value = fork();
	printf("value = %d\n", value);
	if (value == 0)
		printf("i am the child!\n");
	else
		printf("i am parent\n");
	return 0;
}
