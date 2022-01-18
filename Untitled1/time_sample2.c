#include "mpi.h"
#include <stdio.h>
#include <sys/time.h>

#define GET_TIME(now) { \
   struct timeval t; \
   gettimeofday(&t, NULL); \
   now = t.tv_sec + t.tv_usec/1000000.0; \
}

int main( int argc, char *argv[] )
{
	double t1, t2 = 0;

	MPI_Init( 0, 0 );
	sleep(10);
	printf("Elapsed time = %e\n", t2-t1);fflush(stdout);
	MPI_Finalize( );
	return 0;
}

