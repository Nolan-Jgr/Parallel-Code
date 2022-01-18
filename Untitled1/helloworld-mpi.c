#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    // Initialize the MPI environment
    MPI_Init(NULL, NULL);

    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // Get the name of the processor
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);

    // Print off a hello world message
    if(world_size ==4){
	if(world_rank == 0){
	printf("000000");
	}
	else if(world_rank == 1 || world_rank == 2){
	printf("121212");
	}
	else{
	printf("333333");
	}
	}
    else{
	printf("Hello World\n");
	}


    // Finalize the MPI environment.
    MPI_Finalize();
}



