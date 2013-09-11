/*
  Solución al problema anterior utilizando variables de condición
  - Buena solución porque no tiene espera activa
  - Además brinda sincronización (a quien le corresponde el turno)
  - Funciones pthread_cond_wait() y pthread_cond_signal()
*/
#include <stdio.h>
#include <pthread.h>

#define NTHREADS 2
#define VECES 50

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_t = PTHREAD_COND_INITIALIZER;

int turno = 0, c, p;

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
	int a, i;
	
	for(i = 0; i < VECES; ++i)
	{
		
		pthread_mutex_lock(&mutex);
		if (turno == 0) {

			//pthread_mutex_lock(&mutex_c);
		
			p = c + turno;
			turno = 1;
			pthread_cond_signal(&cond_t);
		
			printf("Estoy en el productor, turno = %d \n", turno);
		}
		else {
			pthread_cond_wait(&cond_t, &mutex);
		}
		
		pthread_mutex_unlock(&mutex);
	}
	
	pthread_exit(NULL);
}


void * consumidor(void * arg)
{
	int a, i;
	
	for(i = 0; i < VECES; ++i)
	{
		pthread_mutex_lock(&mutex);
		if (turno == 1) {

			c = p + turno;
			turno = 0;
			pthread_cond_signal(&cond_t);
		
			printf("Estoy en el consumidor, turno = %d \n", turno);
		}
		else {
			pthread_cond_wait(&cond_t, &mutex);
		}

		pthread_mutex_unlock(&mutex);
	}
	
	pthread_exit(NULL);
}