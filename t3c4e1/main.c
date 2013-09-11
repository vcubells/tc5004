/*
  Solución al problema del productor-consumidor utilizando semáforos
  - 1 productor y 1 consumidor
*/
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define NTHREADS 2
#define ITEMS 50
#define BSIZE 4

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
sem_t vacio, lleno;

int in = 0, out = 0;
int buffer[BSIZE];

void * consumidor(void *);
void * productor(void *);

int main(int argc, char **argv)
{
	pthread_t hilos[NTHREADS];
	int result, i;
	
	//Inicializar los semáforos
	sem_init(&vacio, 0, BSIZE);
	sem_init(&lleno, 0, 0);
	
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
	
	//Liberar memoria ocupada por semáforos
	sem_destroy(&vacio);
	sem_destroy(&lleno);
	
	//Garantizar que se liberen los recursos de los hilos
	pthread_exit(NULL);
}

void * productor(void * arg)
{
	//Producir elementos
	int items[ITEMS];
	int i = 0;
	int valor;
	
	printf("/// Productor inició .... \n");
	
	for(; i < ITEMS; ++i)
	{
		items[i] = i;
	}
	i = 0;
	while ( i < ITEMS)
	{
		sleep(rand() % 5); 
		
		sem_wait(&vacio);
		
		pthread_mutex_lock(&mutex);

		buffer[in] = items[i];
		printf("--- Se produjo el elemento %d \n", buffer[in]);
		
		++in;
		in %= BSIZE;
		
		pthread_mutex_unlock(&mutex);
		
		sem_post(&lleno);	
		
		++i;	
	}
}

void * consumidor(void * arg)
{
	int i = 0;
	int valor;
	
	printf("/// Consumidor inició .... \n");
	while ( i < ITEMS)
	{
		sleep(rand() % 5); 
		
		sem_wait(&lleno);
		
		pthread_mutex_lock(&mutex);
		
		printf("*** Se consumió el elemento %d \n", buffer[out]);
		++out;
		out %= BSIZE;
		
		pthread_mutex_unlock(&mutex);
		
		sem_post(&vacio);	
		
		++i;

		
	}	
}

