 /* 
 * Ejemplo de utilización de TSD
 * Router con varias interfaces que contabiliza paquetes
 */
#include <stdio.h>
#include <pthread.h>

#define NHILOS 3

pthread_key_t paquetes;

void * interfaz(void *);

int main(int argc, char **argv)
{
	pthread_t hilos[NHILOS];
	
	int i, *res, suma = 0;
	
	char * interfaces[NHILOS] = {"Ethernet", "FDDI", "Token Ring" };
	
	// Variable de tipo atributo
	pthread_attr_t atrib;
	
	// Inicializar la variable de atributos
	pthread_attr_init(&atrib);
	
	//Asignar valores a los atributos
	pthread_attr_setdetachstate(&atrib, PTHREAD_CREATE_JOINABLE);
	
	//Crear TSD
	pthread_key_create(&paquetes, NULL);
	
	for (i = 0; i < NHILOS; ++i)
		pthread_create(&hilos[i], &atrib, interfaz, (void *) interfaces[i]);
	
	// Liberar memoria de los atributos
	pthread_attr_destroy(&atrib);
	
	// Join
	for (i = 0; i < NHILOS; ++i)
	{
		pthread_join(hilos[i], (void **) &res );
		printf("suma = %d\n", *res));
		suma += res;		
	}
	
	printf("Total de paquetes enrutados: %d \n", suma);
	
	pthread_exit(NULL);

}

void * interfaz(void * arg)
{
	char * nombre;
	int tiempo, i, *tmp, cero;
	
	nombre = (char *) arg;
	
	tiempo = rand() % 50;
	
	cero = 0;
	
	//Establecer valor de TSD
	pthread_setspecific(paquetes, &cero);
	
	for(i = 1; i <= tiempo; ++i)
	{
		printf("%s - Paquete %d \n", nombre, i );
		tmp = (int *) pthread_getspecific(paquetes);
		*tmp += 1;
		
		pthread_setspecific(paquetes, tmp);
		
	}
	tmp = (int *) pthread_getspecific(paquetes);
	printf("Total de paquetes enrutados en %s = %d \n", nombre, *tmp);
	
	pthread_exit( (void *) tmp );
}
