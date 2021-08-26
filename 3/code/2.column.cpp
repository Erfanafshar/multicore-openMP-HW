#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <omp.h>

double starttime, elapsedtime;

typedef struct {
	int *A, *B, *C;
	int l, n, m;
} DataSet;

void fillDataSet(DataSet *dataSet);
void mul(DataSet dataSet);
void printDataSet(DataSet dataSet);
void printElapsedTime();
void closeDataSet(DataSet dataSet);

int main() {
	DataSet dataSet;

	printf("enter matrix dimension : ");
	scanf("%d %d %d", &dataSet.l, &dataSet.n, &dataSet.m);

	fillDataSet(&dataSet);
	mul(dataSet);
	// printDataSet(dataSet);
	printElapsedTime();
	closeDataSet(dataSet);
	system("PAUSE");
	return EXIT_SUCCESS;
}

void fillDataSet(DataSet *dataSet) {
	int i, j, k;

	dataSet->A = (int *)malloc(sizeof(int)* dataSet->n * dataSet->m * dataSet->l);
	dataSet->B = (int *)malloc(sizeof(int)* dataSet->n * dataSet->m * dataSet->l);
	dataSet->C = (int *)malloc(sizeof(int)* dataSet->n * dataSet->m * dataSet->l);

	srand(time(NULL));

	for (k = 0; k < dataSet->l; k++) {
		for (j = 0; j < dataSet->m; j++) {
			for (i = 0; i < dataSet->n; i++) {
				dataSet->A[k * dataSet->m * dataSet->n + j * dataSet->n + i] = rand() % 10;
				dataSet->B[k * dataSet->m * dataSet->n + j * dataSet->n + i] = rand() % 10;
				dataSet->C[k * dataSet->m * dataSet->n + j * dataSet->n + i] = 0;
			}
		}
	}
}

void mul(DataSet dataSet) {
	int k, i, j, f;
	starttime = omp_get_wtime();
	for (k = 0; k < dataSet.l; k++) {
#pragma omp parallel for private(i, f) num_threads(16)
		for (j = 0; j < dataSet.m; j++) {
			for (i = 0; i < dataSet.n; i++) {

					for (f = 0; f < dataSet.m; f++) {
						dataSet.C[k * dataSet.m * dataSet.n + i * dataSet.m + j] +=
							(dataSet.A[k * dataSet.m * dataSet.n + i * dataSet.n + f] *
							dataSet.B[k * dataSet.m * dataSet.n + f * dataSet.n + j]);
					}
				}
			}
	}
	elapsedtime = omp_get_wtime() - starttime;
}

void printDataSet(DataSet dataSet) {
	int k, i, j;

	printf("Matrix A\n");
	for (k = 0; k < dataSet.l; k++) {
		for (i = 0; i < dataSet.n; i++) {
			for (j = 0; j < dataSet.m; j++) {
				printf("%d ", dataSet.A[k * dataSet.m * dataSet.n + i * dataSet.n + j]);
			}
			putchar('\n');
		}
		printf("&\n");
	}

	printf("Matrix B\n");
	for (k = 0; k < dataSet.l; k++) {
		for (i = 0; i < dataSet.n; i++) {
			for (j = 0; j < dataSet.m; j++) {
				printf("%d ", dataSet.B[k * dataSet.m * dataSet.n + i * dataSet.n + j]);
			}
			putchar('\n');
		}
		printf("&\n");
	}

	printf("Matrix C\n");
	for (k = 0; k < dataSet.l; k++) {
		for (i = 0; i < dataSet.n; i++) {
			for (j = 0; j < dataSet.m; j++) {
				printf("%d ", dataSet.C[k * dataSet.m * dataSet.n + i * dataSet.n + j]);
			}
			putchar('\n');
		}
		printf("&\n");
	}
}

void printElapsedTime() {
	printf("Time Elapsed: %f Secs\n", elapsedtime);
}

void closeDataSet(DataSet dataSet) {
	free(dataSet.A);
	free(dataSet.B);
	free(dataSet.C);
}

