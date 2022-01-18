#include <mpi.h>
#include <stdio.h>
#include <string.h>

const int MAX_STRING = 100;

int main(int argc, char** argv) {
    char greeting[MAX_STRING];
    int comm_sz;  //number of process
    int my_rank;  //my process rank

    // Initialize the MPI environment
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    // Get the name of the processor
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);


    if (my_rank != 0) {
        sprintf(greeting, "hello ksu\n");
        MPI_Send(greeting, strlen(greeting)+1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
    } else {
        for (int q = 1; q < comm_sz; q++) {
            MPI_Recv(greeting, MAX_STRING, MPI_CHAR, q, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); 
            printf("%s", greeting);
        }
    }

    // Print off a hello world message
    //printf("Hello world from processor %s, rank %d out of %d processors\n",
    //       processor_name, my_rank, comm_sz);

    // Finalize the MPI environment.
    MPI_Finalize();
}

