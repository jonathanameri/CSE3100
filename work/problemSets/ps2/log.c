#include <stdio.h>


double approxLog(double a, int n)
{
	double dx = (a - 1)/n;
	double x0 = 1;
	double xn = 1 + n*dx;
	double sum = 0;
	double t1;
	for(int k = 1; k <= n - 1; k++){
		sum+= 1.0/(1+k*dx);
	}
	t1 = ((1.0/xn)+(1.0/x0))/2;
	return (dx*(t1+sum));
}

int main(int argc, char* argv[])
{
  
  double a;
  int n;
  printf("Enter a: ");
  scanf("%lf", &a);
  printf("Enter n: ");
  scanf("%d", &n);
  double logarithm = approxLog(a, n);
  printf("Natural logarithm: %lf\n", logarithm);
  return 0;
}
