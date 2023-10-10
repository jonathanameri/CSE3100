#include <stdio.h>

int main(void){
	double min, max, cur, x=0;
	while(scanf("%lf", &cur)==1){
		if(x==0){
			min = cur;
			max = cur;
			x++;
		}
		if(cur < min){
			min = cur;
		}
		if(cur > max){
			max = cur;
		}
		printf("Min=%lf Max=%lf\n", min, max);
	}

}

