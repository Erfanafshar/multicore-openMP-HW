#include <stdio.h>
#include <omp.h>

int main(void)
{
	int E[300][300];
	int i, j;
	double starttime, elapsedtime;

	starttime = omp_get_wtime();
#pragma omp parallel for private(j)
	for (i = 0; i < 250; i++)
	{
		for (j = 0; j < 250; j++)
		{
			E[j][i] += i;
		}
	}
	
	elapsedtime = omp_get_wtime() - starttime;

	for (int i = 0; i < 250; i++)
	{
		for (int j = 0; j < 250; j++)
		{
			printf("%d ", E[j][i]);
		}
		printf("\n");
	}

	
	printf("%f \n", elapsedtime);
	return 0;
}