/*compile: gcc -fopenmp -o omp-helloworld.o omp-helloworld.c */

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

void Hello(void)
{
        int my_thread_ID = omp_get_thread_num();
        int thread_count = omp_get_num_threads();
        printf( "Hello from thread %d of %d\n", my_thread_ID , thread_count );
}

int main (int argc, char *argv[]) {

#pragma omp parallel
	Hello();

	return 0;
}




