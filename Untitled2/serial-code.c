#include <stdio.h>
#include <time.h>
#include <omp.h>

void SumForNumber()
{
        int a = 0;
        for (int i = 0; i<10000000; i++)
                a++;
}

int main()
{
        struct timespec start, end;
        clock_gettime(CLOCK_MONOTONIC, &start);

	#pragma omp parallel for
        for (int i = 0; i<100; i++)
                SumForNumber();

        clock_gettime(CLOCK_MONOTONIC, &end);

        double diff = 1000000000L * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
        printf("time: %lf\n", diff);
        return 0;
}


