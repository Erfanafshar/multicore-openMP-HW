using namespace std;
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <omp.h>

#define N 12

double starttime, elapsedtime;


void getCofactor(int mat[N][N], int temp[N][N], int p, int q, int n){
	int i = 0, j = 0;
	for (int row = 0; row < n; row++){
		for (int col = 0; col < n; col++){
			if (row != p && col != q){
				temp[i][j++] = mat[row][col];
				if (j == n - 1){
					j = 0;
					i++;
				}
			}
		}
	}
}

unsigned long long int determinantOfMatrix(int mat[N][N], int n){
	unsigned long long int D = 0; 
	if (n == 1)
		return mat[0][0];
	int temp[N][N];
	int sign = 1; 

#pragma omp parallel private(val)
	for (int f = 0; f < n; f++){
		getCofactor(mat, temp, 0, f, n);
#pragma omp task
		unsigned long long val = determinantOfMatrix(temp, n - 1);
		D += sign * mat[0][f] * val;
		sign = -sign;
	}
	return D;
}


int main()
{
	int A[N][N];
	int i, j;
	srand(time(NULL));

	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			A[i][j] = rand() % 10;
		}
	}

	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			printf("%d ", A[i][j]);
		}
		putchar('\n');
	}

	starttime = omp_get_wtime();

	determinantOfMatrix(A, N);

	elapsedtime = omp_get_wtime() - starttime;
	printf("Time Elapsed: %f Secs\n", elapsedtime);
	return 0;
}
