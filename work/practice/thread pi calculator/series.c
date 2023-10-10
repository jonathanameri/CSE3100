#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

#define DEFAULT_T 1
#define DEFAULT_N 100000000

typedef struct{
	int start;
	int end;
	double sum;
} thr_data;

void* threadApprox(void* arg)
{
	thr_data* x = (thr_data*) arg;

	int i;
	//int localSum = 0;
	for(i = x->start; i < x->end; i++) {
		//if(i%2==0) localSum += 1.0/(2*i+1);
		//else localSum -= 1.0/(2*i+1);
		if(i%2==0) x->sum += 1.0/(2*i+1);
		else x->sum -= 1.0/(2*i+1);
	}
	//x->sum += localSum;
	pthread_exit(NULL);
}

int main(int argc, char* argv[])
{
	int i;
	int t = (argc > 1 ? atoi(argv[1]) : DEFAULT_T);
	int n = (argc > 2 ? atoi(argv[2]) : DEFAULT_N);
	double total, my_pi, PI25 = 3.141592653589793238462643;
	unsigned int seed[t];
	pthread_t worker[t];
	thr_data data[t];

	printf("Summing first %d terms of the series using %d threads\n", n, t);
	for(i=0; i<t; i++) {
		data[i].start = (i==0 ? 0 : data[i-1].end);
		data[i].end = data[i].start + n/t + (i < n%t);
		data[i].sum = 0;
		int rc = pthread_create(&worker[i], NULL, threadApprox, &data[i]);
		if(rc) {
			printf("Could not create thread #%d, error code %d\n", i, rc);
			exit(-1);
		}
	}
	for(i=0; i<t; i++) {
		int rc = pthread_join(worker[i], NULL);
		if(rc) {
			printf("Could not join thread #%d, error code %d\n", i, rc);
			exit(-1);
		}
		total += data[i].sum;
	}

	my_pi = 4*total;
	printf("Pi approximation: %.16f Error: %.16f\n", my_pi, fabs(my_pi - PI25));
	return 0;
}
