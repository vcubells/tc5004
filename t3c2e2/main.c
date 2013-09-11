#include <stdio.h>
#include <pthread.h>

#define HILOS 2
#define NUM 100

int lista[NUM]; 

typedef struct {
		int inicio, fin;
} datos;

int valor = 0;

void * suma(void * param)
{
	datos * par = (datos *) param; 
	int i;
	for(i = par->inicio; i < par->fin; ++i)
	{
		valor = lista[i];
		sleep(1);
		printf("Valor = %d \n", valor);
	}
	pthread_exit(0);	
}

int main(int argc, char **argv)
{
	pthread_t hilos[HILOS];
	
	datos param1, param2;
	int result;
	int i = 0;
	
	for (; i < NUM; ++i)
		lista[i] = i;
		
	param1.inicio = 0;
	param1.fin = NUM / 2;
	
	param2.inicio = param1.fin;
	param2.fin = NUM;
	
	result = pthread_create(&hilos[0], NULL, suma, &param1);
	if (result) {
		printf("Error al crear el hilo 1");	
	}
	
	result = pthread_create(&hilos[1], NULL, suma, &param2);
	if (result) {
		printf("Error al crear el hilo 2");	
	}

	for(i=0; i < HILOS; ++i)
	{
		result = pthread_join(hilos[i], NULL);
		if (!result) {
			printf("Uniendo el hilo %d ------------ \n", i);
		}
	}
	
	
}