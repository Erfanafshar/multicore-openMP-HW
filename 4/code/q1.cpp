#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <omp.h>

#define N 64
#define thrd_num 4
double starttime, elapsedtime;

typedef struct {
	int *A, *B, *C, *R;
} DataSet;

void fillDataSet(DataSet *dataSet);
void draw_mat(int* mat);

void calculate(DataSet dataSet);
int* mul_s(int mat1[N], int mat2[N]);
int* add_s(int mat1[N], int mat2[N]);
int* transpose_s(int mat[N]);
int* mul_p(int mat1[N], int mat2[N]);
int* add_p(int mat1[N], int mat2[N]);
int* transpose_p(int mat[N]);

void printDataSet(DataSet dataSet);
void printElapsedTime();
void closeDataSet(DataSet dataSet);

int main() {
	DataSet dataSet;
	fillDataSet(&dataSet);
	// printDataSet(dataSet);
	calculate(dataSet);
	printElapsedTime();
	closeDataSet(dataSet);
	system("PAUSE");
	return EXIT_SUCCESS;
}

void fillDataSet(DataSet *dataSet) {
	int i, j, k;

	dataSet->A = (int *)malloc(sizeof(int)* N * N);
	dataSet->B = (int *)malloc(sizeof(int)* N * N);
	dataSet->C = (int *)malloc(sizeof(int)* N * N);
	dataSet->R = (int *)malloc(sizeof(int)* N * N);

	srand(time(NULL));

	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			dataSet->A[i * N + j] = rand() % 10;
			dataSet->B[i * N + j] = rand() % 10;
			dataSet->C[i * N + j] = rand() % 10;
			dataSet->R[i * N + j] = 0;
		}
	}
}

void calculate(DataSet dataSet) {
	starttime = omp_get_wtime();
	int* tmp1 = transpose_p(dataSet.A);
	// printf("At \n");
	// draw_mat(tmp1);
	int* tmp2 = mul_p(tmp1, dataSet.A);
	// printf("At * A \n");
	// draw_mat(tmp2);
	int* tmp3 = mul_p(dataSet.B, dataSet.A);
	// printf("B * A \n");
	// draw_mat(tmp3);
	int* tmp4 = add_p(tmp2, tmp3);
	// printf("At * A + B * A \n");
	// draw_mat(tmp4);
	int* tmp5 = transpose_p(dataSet.C);
	// printf("Ct \n");
	// draw_mat(tmp5);
	dataSet.R = mul_p(tmp4, tmp5);
	// printf("R \n");
	// draw_mat(dataSet.R);
	elapsedtime = omp_get_wtime() - starttime;
}

int* mul_s(int mat1[N], int mat2[N]) {
	int i, j, k;
	int* res = (int *)malloc(sizeof(int)* N * N);
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			res[i * N + j] = 0;
		}
	}

	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			for (k = 0; k < N; k++) {
				res[i * N + j] += mat1[i * N + k] * mat2[k * N + j];
			}
		}
	}
	return res;
}

int* mul_p(int mat1[N], int mat2[N]) {
	int i, j, k;
	int* res = (int *)malloc(sizeof(int)* N * N);
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			res[i * N + j] = 0;
		}
	}

#pragma omp parallel for private(j, k) num_threads(thrd_num)
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			for (k = 0; k < N; k++) {
				res[i * N + j] += mat1[i * N + k] * mat2[k * N + j];
			}
		}
	}
	return res;
}

int* add_s(int mat1[], int mat2[]) {
	int i, j;
	int* res = (int *)malloc(sizeof(int)* N * N);

	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			res[i * N + j] = mat1[i * N + j] + mat2[i * N + j];
		}
	}
	return res;
}

int* add_p(int mat1[], int mat2[]) {
	int i, j;
	int* res = (int *)malloc(sizeof(int)* N * N);

#pragma omp parallel for private(j) num_threads(thrd_num)
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			res[i * N + j] = mat1[i * N + j] + mat2[i * N + j];
		}
	}
	return res;
}

int* transpose_s(int mat[N]) {
	int i, j, k;
	int* res = (int *)malloc(sizeof(int)* N * N);

	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			res[i * N + j] = mat[j * N + i];
		}
	}
	return res;
}

int* transpose_p(int mat[N]) {
	int i, j, k;
	int* res = (int *)malloc(sizeof(int)* N * N);

#pragma omp parallel for private(j) num_threads(thrd_num)
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			res[i * N + j] = mat[j * N + i];
		}
	}
	return res;
}

void draw_mat(int* mat) {
	int i, j;
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			printf("%d ", *(mat + i * N + j));
		}
		putchar('\n');
	}
	printf("\n");
}

void printDataSet(DataSet dataSet) {
	int i, j;

	printf("Matrix A\n");
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			printf("%d ", dataSet.A[i * N + j]);
		}
		putchar('\n');
	}
	printf("\n");

	printf("Matrix B\n");
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			printf("%d ", dataSet.B[i * N + j]);
		}
		putchar('\n');
	}
	printf("\n");

	printf("Matrix C\n");
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			printf("%d ", dataSet.C[i * N + j]);
		}
		putchar('\n');
	}
	printf("\n");
}

void printElapsedTime() {
	printf("Time Elapsed: %f Secs\n", elapsedtime);
}

void closeDataSet(DataSet dataSet) {
	free(dataSet.A);
	free(dataSet.B);
	free(dataSet.C);
	free(dataSet.R);
}

