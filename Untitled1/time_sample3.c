#include "mpi.h"
#include <stdio.h>
#include <time.h>

int main( int argc, char *argv[] )
{
	struct timespec t1, t2;

	MPI_Init( 0, 0 );
	sleep(10);

	double diff = 0;

	printf("Time = %llu nanoseconds\n", (long long unsigned int)diff) ; fflush(stdout);
	MPI_Finalize( );
	return 0;
}


