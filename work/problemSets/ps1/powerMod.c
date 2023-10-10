#include <stdio.h>


int help(int n, int e, int m){
	if (e==1)
		return n%m;
	else if (e%2==0)
		return help((n*n)%m, e/2, m);
	else 
		return (help((n*n)%m, e/2, m)*n)%m;
} 

int main(void){
	int n, e, m, ans;
	printf("Please enter n, e, and m: ");
	scanf("%d %d %d", &n, &e, &m);
	
	ans = help(n, e, m);
	printf("%d ** %d mod %d = %d\n", n, e, m, ans);
	return 0;
}
