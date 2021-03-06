#include "mpi.h"
#include <stdio.h>

int main( int argc, char *argv[] )
{
	double t1, t2 = 0;

	MPI_Init( 0, 0 );
	t1 = MPI_Wtime();
	sleep(10);
	t2 = MPI_Wtime();
	printf("MPI_Wtime measured a 1 second sleep to be: %1.2f\n", t2-t1);fflush(stdout);
	MPI_Finalize( );
	return 0;
}
