#include <stdio.h>

int bang(int x){
	int factorial=1;
	for (int i = 1; i <= x; i++){
		factorial*=i;
	}
	return factorial;
}

int main(void) {
       	int n;
       	float e=0.0;
	printf("n = ");
	scanf("%d", &n);
	while(n>=0){
		e+=(1.0/bang(n));
		n--;
	}	
	printf("e = %f\n", e);
  	return 0;

}
