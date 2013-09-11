/* Determinar cantidad de 0's y 1's con OpenMP
 * utilizando reduction
 */
#include <stdio.h>
#include <omp.h>
#define N 100

int main(int argc, char **argv)
{
	
	int i, tid;
	int numero[N];
	int unos = ceros = tunos = tceros = 0;
	
	srand(time(NULL));
	
	#pragma omp parallel for private(i)
	{
		for(i=0; i < N; ++i)
		{
			#pragma omp critical
			numero[i] = rand()%2;
		}
	}
	
	#pragma omp parallel private(i, tid)
	{
		tid = omp_get_thread_num();
		procs = omp_get_num_threads();
		bloque = N / procs;
		ini = tid * bloque;
		fin = ini + bloque;
		
		#pragma omp for reduction(+:tceros,tunos)
		for (i=ini; i < fin; ++i)		
		{	
			if (numero[i] == 0) ++ceros
			else ++unos;
		}
		printf("Hilo %d con %d ceros y %d unos \n", tid, ceros, unos);
	}
	printf("El factorial de %d = %lld", numero, fact);
}