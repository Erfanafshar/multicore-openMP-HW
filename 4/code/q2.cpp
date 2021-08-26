#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <omp.h>

#define N 100000
#define thrd_num 2
double starttime, elapsedtime;
omp_lock_t lock1, lock2;

int main() {
	
#pragma omp parallel num_threads(thrd_num)
	{
		int ID = omp_get_thread_num();
		printf("id = %d\n", ID);
		if (ID == 0) {
			omp_init_lock(&lock1);
			omp_set_lock(&lock1);

			printf("0 calc start\n");
			int i, j, k, res;
			for (i = 0; i < N; i++) {
				for (j = 0; j < N; j++) {
					for (k = 0; k < N; k++) {
						res = i * j + k * i + i * i;
					}
				}
			}
			printf("0 calc end\n");

			// while (1) {
			//	 printf("from 0 -> %d\n", omp_test_lock(&lock2));
			// }

			printf("from 0 -> %d\n", omp_test_lock(&lock2));
			printf("from 0 -> %d\n", omp_test_lock(&lock2));
			printf("from 0 -> %d\n", omp_test_lock(&lock2));
			printf("from 0 -> %d\n", omp_test_lock(&lock2));
			printf("from 0 -> %d\n", omp_test_lock(&lock2));
			printf("from 0 -> %d\n", omp_test_lock(&lock2));
			printf("from 0 -> %d\n", omp_test_lock(&lock2));
			printf("from 0 -> %d\n", omp_test_lock(&lock2));

			omp_unset_lock(&lock1);

		}
		else {
			if (ID == 1) {
				omp_init_lock(&lock2);
				omp_set_lock(&lock2);

				printf("1 calc start\n");
				int ii, jj, kk, resres;
				for (ii = 0; ii < N; ii++) {
					for (jj = 0; jj < N; jj++) {
						for (kk = 0; kk < N; kk++) {
							resres = ii * jj + kk * ii + ii * ii;
						}
					}
				}
				printf("1 calc end\n");

				// while (1){
				//	 printf("from 1 -> %d\n", omp_test_lock(&lock1));
				// }

				printf("from 1 -> %d\n", omp_test_lock(&lock1));
				printf("from 1 -> %d\n", omp_test_lock(&lock1));
				printf("from 1 -> %d\n", omp_test_lock(&lock1));
				printf("from 1 -> %d\n", omp_test_lock(&lock1));
				printf("from 1 -> %d\n", omp_test_lock(&lock1));
				printf("from 1 -> %d\n", omp_test_lock(&lock1));
				printf("from 1 -> %d\n", omp_test_lock(&lock1));
				printf("from 1 -> %d\n", omp_test_lock(&lock1));

				omp_unset_lock(&lock2);
			}
		}
	}

	omp_destroy_lock(&lock1);
	omp_destroy_lock(&lock2);
}