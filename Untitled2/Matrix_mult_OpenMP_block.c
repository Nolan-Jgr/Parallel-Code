#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <stdlib.h>

#define N 1024
#define BLOCK_NUM 32
#define BLOCK_SZ N/BLOCK_NUM
#define FactorIntToDouble 1.1; 
int thread_count;

double firstMatrix [N] [N] = {0.0};
double secondMatrix [N] [N] = {0.0};
double matrixMultiResult [N] [N] = {0.0};


void matrixMulti()
{
	int i, i2, j, j2, k, k2;

	#pragma omp parallel for num_threads(thread_count) private(i, i2, j, j2, k, k2) shared(firstMatrix, secondMatrix, matrixMultiResult)
	for (k2 = 0; k2 < N; k2+=BLOCK_SZ) {
		for (i2 = 0; i2 < N; i2+=BLOCK_SZ) {
			for (j2 = 0; j2 < N; j2+=BLOCK_SZ) {
				for (k = k2; k < k2+BLOCK_SZ; k++) {
					for (i = i2; i < i2+BLOCK_SZ; i++) {
						for (j = j2; j < j2+BLOCK_SZ; j++) {
							matrixMultiResult[i][j] = firstMatrix[i][k] * secondMatrix[k][j];
						}
					}
				}

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
    	int thread_count = strtol(argv[1], NULL, 10);
    	clock_t t1 = clock(); 
    	matrixMulti();
    	clock_t t2 = clock(); 
    	printf("time: %ld", t2-t1);
    	return 0;
}
