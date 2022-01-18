#include <mpi.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define NUMSTEPS 1000000

int main(int argc, char* argv[]){
	int my_rank;
	int comm_sz;
	int error,i;
	double pi = 0.0, result = 0.0, total = 0.0;
	struct timespec start, end;
	
	error = MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	MPI_Barrier(MPI_COMM_WORLD);
	clock_gettime(CLOCK_MONOTONIC, &start);
	double h = 1.0/(double) NUMSTEPS;
	double x = 0.5 * h;
	for(i = my_rank; i < NUMSTEPS; i += comm_sz){
		result += 1.0 / (1.0 + x*x);
		x += h;
	}
	
	MPI_Reduce(&result, &total, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

	MPI_Barrier(MPI_COMM_WORLD);
	clock_gettime(CLOCK_MONOTONIC, &end);
	u_int64_t diff = 1000000000L * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
	
	if(my_rank==0){
		pi = 4.0 * h * total;
		printf("PI is %.20f\n",pi);
		printf("elapsed time = %llu nanoseconds\n", (long long unsigned int) diff);
	}
	error = MPI_Finalize();
	return 0;
}
