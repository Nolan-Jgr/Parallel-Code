#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define N 2000

double A[N][N], B[N][N], C[N][N];

void initMatrix()
{
	int i, j = 0;
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			A[i][j] = rand() % 100 + 1;  //generate a number between [1, 100]
			B[i][j] = rand() % 100 + 1;  //generate a number between [1, 100]
		}
	}
}

void matrixMultiply() {
	int i, j, k = 0;
        for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			for (k = 0; k < N; k++) {
				C[i][j] = A[i][k] * B[k][j];
			}
		}
	}
}

int main()
{
	initMatrix();

	double time_spent = 0.0;
	clock_t begin = clock();

	matrixMultiply();

	clock_t end = clock();
	time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
	printf("Time elpased is %f seconds", time_spent);

	return 0;
}


