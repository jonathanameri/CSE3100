#include <stdio.h>

double relError(double x, double s){
	double num = x*x-s;
       	if (num < 0)
		num*=-1;
	return num/s;
}

int main(int argc, char* argv[]){
	double s;
	printf("Enter S to take square root of: ");
	scanf("%lf", &s);
	double guess = 1;
	while(guess*guess<s){
		guess++;
	} 
	while(relError(guess,s)>=0.001){
		guess=0.5*(guess+(s/guess));
	}

	printf("Square root: %f\n", guess);
  
}
