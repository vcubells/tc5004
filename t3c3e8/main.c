/*
  Solución al problema del productor-consumidor utilizando semáphoros POSIX (no son parte de Pthreads)
  - 1 productor y 1 consumidor
  - Se utiliza:
   * sem_get() - Es el DOWN, 
   * sem_post() - Es el UP
   * sem_init() - Inicializa un semáforo
   * sem_destroy() - Libera la memoria ocupada por el semáforo
   * sem_getvalue() - Devuelve el valor de un semáforo
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define NTHREADS 2
#define BSIZE 10
#define ITEMS 30

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
sem_t vacio, lleno;

int buffer[BSIZE];
int in = 0, out = 0, ocupados = 0;

void * productor(void *);
void * consumidor(void *);

int main(int argc, char **argv)
{
	pthread_t hilos[NTHREADS];
	int result, i;
	
	sem_init(&vacio,0,BSIZE);
	sem_init(&lleno,0,0);
	
	//Crear al productor
	result = pthread_create(&hilos[0], NULL, productor, NULL);
	if (result) {
		perror("Error al crear el productor");
		exit(-1);
	}
	
	//Crear al consumidor
	result = pthread_create(&hilos[1], NULL, consumidor, NULL);
	if (result) {
		perror("Error al crear el consumidor");
		exit(-1);
	}
	
	//Esperar a que ambos terminen
	for(i=0; i < 2; ++i)
	{
		result = pthread_join(hilos[i], NULL);
		if (result)
			perror("Error al al adjuntar el hilo");
	}
	
	sem_destroy(&vacio);
	sem_destroy(&lleno);
	
	return 0;
}

void * productor(void * p)
{
	int items[ITEMS], i = 0, valor;
	
	printf("Inicia el productor...\n");
	
	//Inicializar elementos a producir
	for(; i < ITEMS; ++i)
	{
		items[i] = i;
	}
	
	i=0;
	
	while (i < ITEMS) {
		sem_wait(&vacio);
		printf("Productor trabajando...");
		pthread_mutex_lock(&mutex);
		
		buffer[in] = items[i];
		printf("Se produjo el elemento: %d\n", buffer[in++]);
		in %= BSIZE;
		
		sem_post(&lleno);
		sem_getvalue(&vacio, &valor);
		if (valor == 0)
			printf("Buffer lleno, el productor tiene que esperar\n");

		pthread_mutex_unlock(&mutex);
		++i;
		sleep(rand()%5);
		
	}	
	
	printf("El productor ya terminó su trabajo\n");
	
	pthread_exit(0);
}

void * consumidor(void * p)
{
	int i = 0, valor;
	
	printf("Inicia el consumidor...\n");
	
	while (i < ITEMS) {
		sem_wait(&lleno);
		printf("Consumidor trabajando...");
		pthread_mutex_lock(&mutex);
		printf("Se consumió el elemento: %d\n", buffer[out++]);
		out %= BSIZE;
		
		sem_post(&vacio);
		sem_getvalue(&lleno, &valor);
		if (valor == 0)
			printf("Buffer vacío, el consumidor tiene que esperar\n");
		
		pthread_mutex_unlock(&mutex);	
		++i;
		
		sleep(rand()%5);

	}	
	
	printf("El consumidor ya terminó su trabajo\n");
	
	pthread_exit(0);
}
