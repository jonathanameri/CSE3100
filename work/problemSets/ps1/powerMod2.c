#include <stdio.h>


int help(int n, int e, int m){
	int result = 1;
	while(e>0){
		if(e%2==1){
			result = (result*n)%m;
		}
		e=e/2;
		n=(n*n)%m;
	}
	return result;
} 

int main(void){
	int n, e, m, ans;
	printf("Please enter n, e, and m: ");
	scanf("%d %d %d", &n, &e, &m);
	
	ans = help(n, e, m);
	printf("%d ** %d mod %d = %d\n", n, e, m, ans);
	return 0;
}
