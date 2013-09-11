/*
  Demostrar el problema que surge al no proteger la región crítica (variable global suma)
  cuando los procesos se ejecutan en un orden arbitrario.
   - Solución no determinista
*/
#include <stdio.h>
#include <pthread.h>

#define NTHREADS 2
#define VECES 50

int suma = 0;

void * sumar(void *);
void * restar(void *);

int main(int argc, char **argv)
{
	pthread_t hilos[NTHREADS];
	int result, i;
	
	// Crear hilos
	result = pthread_create(&hilos[0], NULL, sumar, NULL);
	if (result)
		printf("Error al crear el sumador \n");
	
	result = pthread_create(&hilos[1], NULL, restar, NULL);
	if (result)
		printf("Error al crear el restador \n");
	
	// Esperar que terminen los hilos
	for(i = 0; i < NTHREADS; ++i)
	{
		result = pthread_join(hilos[i], NULL);
		if (result)
			printf("Error al adjuntar el hilo %d \n", i);
	}
	
	//Garantizar que se liberen los recursos de los hilos
	pthread_exit(NULL);
}

void * sumar(void * arg)
{
	int a, i;
	
	for(i = 0; i < VECES; ++i)
	{
		a = suma;
		++a;		
		// Cambio de contexto
		sleep(rand()%5);
		suma = a;
		printf("(Sumador) Suma = %d \n", suma);
	}
	
	pthread_exit(NULL);
}

void * restar(void * arg)
{
	int a, i;
	
	for(i = 0; i < VECES; ++i)
	{
		a = suma;
		--a;
		// Cambio de contexto
		sleep(rand()%5);
		suma = a;
		printf("(Restador) Suma = %d \n", suma);
	}
	
	pthread_exit(NULL);
}