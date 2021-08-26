#include <stdio.h>
#include <omp.h>

int main(void)
{
	int i, acc = 0;
	double starttime, elapsedtime;

	starttime = omp_get_wtime();
// #pragma omp parallel
	// {
#pragma omp for
		for (i = 0; i < 100; i++)
		{
			#pragma omp critical
			acc++;
		}
	// }

	elapsedtime = omp_get_wtime() - starttime;

	printf("%d \n", acc);
	printf("%f \n", elapsedtime);
	return 0;
}