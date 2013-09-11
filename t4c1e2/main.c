#include <stdio.h>
#include <omp.h>

#define N 1000000
#define B 10

int main(int argc, char **argv)
{
	int i, tid, suma = 0;
	int vector[N];
	
	#pragma omp parallel private (i) shared(vector)
		for(i=0; i < N; ++i)
			vector[i] = rand() % 10;
			
	#pragma omp parallel private (i, tid) shared(vector) reduction(+:suma)
	{
		tid = omp_get_thread_num();
		for (i=0; i < N; ++i)
		{
			suma += vector[i];
			printf("Posición %d hilo %d \n", i, tid);
		}
	}
	
	printf("Suma total = %d\n", suma);
}
