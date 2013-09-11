#include <stdio.h>
#include <omp.h>
#define N 100000

int main(int argc, char **argv)
{
	int lista[N];
	int i;
	int encontrado = 0;
	int pos = -1;
	int valor, inicio, fin, iteraciones, tid, nh;
	
	srand(time(NULL));
	
	valor = rand() % N;
	
	#pragma omp parallel for private(i) shared(lista)
		for(i = 0; i < N; ++i)
			lista[i] = rand() % N;
	
	#pragma omp parallel private(i, inicio, fin, tid, iteraciones)
	{
		nh = omp_get_num_threads();
		tid = omp_get_thread_num();
		iteraciones = N / nh;
		
		inicio = tid * iteraciones;
		
		if (tid == nh -1) fin = N;
		else fin = inicio + iteraciones;
		
		for(i = inicio; i < fin && !encontrado; ++i)
		{
			if (lista[i] == valor)
			{
				encontrado = 1;
				pos = i;
				printf("!!!! Encontrado por Hilo %d en iteración = %d\n", tid, i);
			}
			printf("Hilo %d hace iteración = %d \n", tid, i);
		}
		
		#pragma omp flush (encontrado)
	}
	
	if (encontrado)
		printf("El valor %d encontrado en pos = %d \n", valor, pos);
	else
		printf("El valor %d no se encuentra en el arreglo\n", valor);
}
