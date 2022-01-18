#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <stdlib.h>

#define N 1024
#define FactorIntToDouble 1.1; 

double firstMatrix [N] [N] = {0.0};
double secondMatrix [N] [N] = {0.0};
double matrixMultiResult [N] [N] = {0.0};
int thread_count;

void matrixMulti()
{
	int i, j, k;
	#pragma omp parallel for num_threads(thread_count) private(i, j, k) shared(firstMatrix, secondMatrix, matrixMultiResult)
	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			for(k = 0; k < N; k++){
				matrixMultiResult[i][j] += firstMatrix[i][k] * secondMatrix[k][j]; 
			}
		}
	}
}


void matrixInit()
{
	#pragma omp parallel for num_threads(thread_count)
	for(int row = 0 ; row < N ; row++ ) {
     		for(int col = 0 ; col < N ;col++){
           	srand(row+col);
            	firstMatrix [row] [col] = ( rand() % 10 ) * FactorIntToDouble;
            	secondMatrix [row] [col] = ( rand() % 10 ) * FactorIntToDouble;
        	}
    	}
}



int main(int argc, char *argv[])
{
	matrixInit();	
	thread_count = strtol(argv[1], NULL, 10);
    	clock_t t1 = clock(); 
    	matrixMulti();
    	clock_t t2 = clock(); 
    	printf("time: %ld", t2-t1);

    	return 0;
}
