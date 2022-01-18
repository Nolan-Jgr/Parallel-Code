/*
 * compile: gcc trapezoidal-serial.c -o trapezoidal-serial.o -lm
 */

#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include <unistd.h>
#include <omp.h>
#include <stdlib.h>

double Size;

double f(double x)
{
	return sin(x) + 2;
}

double Trap(double a, double b, int n)
{
	double h = (b-a)/n;
	int i;

	double local_a;
        int local_n;
	double local_Size;

        int my_thread_ID = omp_get_thread_num();
        int thread_count = omp_get_num_threads();

	local_n = n/thread_count;
	local_a = a + (n/thread_count)*h*my_thread_ID;

	for (i = 0; i < local_n; i++) {
		double x_i = local_a + i*h;
		local_Size = local_Size + f(x_i) * h;
	}

//	printf("%d, %d, %d, %lf, %lf\n", my_thread_ID, thread_count, local_n, local_a, local_Size);

#pragma omp critical
	Size = Size + local_Size;

	return Size;
}

int main(int argc, char* argv[]) {
	double a, b, Size;
	int n;
	struct timeval tvs,tve;

	gettimeofday(&tvs,NULL);  //get start time

	a = 1, b = 10;
	n = 1000;

        /* Get number of threads from command line */
        int thread_count = strtol(argv[1], NULL, 10);
#pragma omp parallel num_threads( thread_count )
	Size = Trap(a, b, n);

	printf("Size = %.2lf\n", Size);

	gettimeofday(&tve,NULL);   //get end time
        double span = tve.tv_sec-tvs.tv_sec + (tve.tv_usec-tvs.tv_usec)/1000000.0;
        printf("Time: %.12f\n", span);

	return 0;
}


