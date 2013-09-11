/*
  Solución al problema del productor-consumidor utilizando variables de condición
  - NP productores y NC consumidores
  - Se utiliza pthread_cond_broadcast()
*/
#include <stdio.h>
#include <pthread.h>

#define NTHREADS 2
#define ITEMS 50
#define BSIZE 4
#define NC 3
#define NP 2

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t consume = PTHREAD_COND_INITIALIZER;
pthread_cond_t produce = PTHREAD_COND_INITIALIZER;

int in = 0, out = 0, count = 0;
int buffer[BSIZE];

void * consumidor(void *);
void * productor(void *);

int main(int argc, char **argv)
{
	pthread_t hilos[NC+NP];
	int result, i, nh;
	
	// Crear hilos
	for (i=0; i < NP; ++i)
	{
		result = pthread_create(&hilos[i], NULL, productor, (void *)i);
		if (result)
			printf("Error al crear el sumador \n");
	}
	
	for (i=0; i < NC; ++i)
	{
		result = pthread_create(&hilos[NP+i], NULL, consumidor, (void *)i);
		if (result)
			printf("Error al crear el restador \n");
	}
	
	// Esperar que terminen los hilos
	nh = NP + NC;
	for(i = 0; i < nh; ++i)
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
	//Producir elementos
	int items[ITEMS];
	int i = 0;
	int id = (int) arg;
	
	printf("/// Productor %d inició .... \n", id);
	
	for(; i < ITEMS; ++i)
	{
		items[i] = i;
	}
	i = 0;
	while ( i < ITEMS)
	{
		sleep(rand() % 5); 
		pthread_mutex_lock(&mutex);
		if (count < BSIZE)
		{
			buffer[in] = items[i];
			printf("P%d --- Se produjo el elemento %d \n", id, buffer[in]);
			++in;
			in %= BSIZE;
			++count;
			if (count == 1) pthread_cond_broadcast(&consume);	
			++i;
		}
		else {
			while (count >= BSIZE)
			{
				printf("---------Productor %d se durmió ----------\n", id);
				pthread_cond_wait(&produce, &mutex);
				printf("---------Productor %d se despertó ----------\n", id);
			}
		}
		pthread_mutex_unlock(&mutex);
	}
}

void * consumidor(void * arg)
{
	int i = 0;
	int id = (int) arg;
	
	printf("/// Consumidor %d inició .... \n", id);
	while ( i < ITEMS)
	{
		sleep(rand() % 5); 
		pthread_mutex_lock(&mutex);
		if (count > 0)
		{
			printf("C%d *** Se consumió el elemento %d \n", id, buffer[out]);
			++out;
			out %= BSIZE;
			--count;
			if (count == (BSIZE-1)) pthread_cond_broadcast(&produce);	
			++i;
		}
		else {
			
			while (count == 0)
			{
				printf("---------Consumidor %d se durmió ----------\n", id);
				pthread_cond_wait(&consume, &mutex);
				printf("---------Consumidor %d se despertó ----------\n", id);
			}
		}
		pthread_mutex_unlock(&mutex);
	}	
}
