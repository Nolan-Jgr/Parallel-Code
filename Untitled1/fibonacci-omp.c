//gcc -fopenmp fibonacci.c -o fibonacci.o

#include <stdio.h>
#include <omp.h>

int main()
{
	int fibo[10];
	fibo[0] = fibo[1] = 1;
	int i;

	printf("%d\n", fibo[0]);
	printf("%d\n", fibo[1]);

#pragma omp parallel for num_threads(2)
	for (i = 2; i < 10; i++)
	{
		fibo[i] = fibo[i-1] + fibo[i-2];
		printf("%d\n", fibo[i]);
	}

	return 0;
}


