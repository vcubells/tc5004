/*
  Demostrar el problema de bloqueos cuando se invierten los mutexes
  para proteger dos variables globales
*/

#include <stdio.h>
#include <pthread.h>

#define NTHREADS 2
#define VECES 50

pthread_mutex_t mutex_c = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_p = PTHREAD_MUTEX_INITIALIZER;

int c, p;

void * consumidor(void *);
void * productor(void *);

int main(int argc, char **argv)
{
	pthread_t hilos[NTHREADS];
	int result, i;
	
	// Crear hilos
	result = pthread_create(&hilos[0], NULL, productor, NULL);
	if (result)
		printf("Error al crear el sumador \n");
	
	result = pthread_create(&hilos[1], NULL, consumidor, NULL);
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

void * productor(void * arg)
{
	int i;
	
	for(i = 0; i < VECES; ++i)
	{
		pthread_mutex_lock(&mutex_p);
		
		//Cambio de contexto
		sleep(rand()%5;
		
		pthread_mutex_lock(&mutex_c);
		
		p = c + 1;
		
		pthread_mutex_unlock(&mutex_c);
		pthread_mutex_unlock(&mutex_p);
	}
	
	pthread_exit(NULL);
}


void * consumidor(void * arg)
{
	int i;
	
	for(i = 0; i < VECES; ++i)
	{
		pthread_mutex_lock(&mutex_c);
		
		//Cambio de contexto
		sleep(rand()%5;
		
		pthread_mutex_lock(&mutex_p);
		
		p = c + 1;
		
		pthread_mutex_unlock(&mutex_p);
		pthread_mutex_unlock(&mutex_c);
	}
	
	pthread_exit(NULL);
}


