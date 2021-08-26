#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(void)
{
	int E = 0;
	int i;
	omp_set_num_threads(4);
	int arr_size = 929;
	int *arr = (int*)malloc(sizeof(int)*arr_size);
	double starttime, elapsedtime;

	starttime = omp_get_wtime();
#pragma omp parallel private(workload_size, start, end)
	{
		int workload_size = arr_size / 4;
		int start = omp_get_thread_num()*workload_size;
		int end = start + workload_size;
		printf("\n%d-%d\n", start, end);
		for (i = start; i < end; i++)
		{
			arr[i] = 2;
		}
	}

	elapsedtime = omp_get_wtime() - starttime;

	for (i = 0; i < arr_size; i++)
	{
		printf("%d ", arr[i]);
	}

	printf("\n%f\n", elapsedtime);
	return 0;
}