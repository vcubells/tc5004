/* 
 * Ejemplo de hilo que recibe argumentos con un struct y 
 * se establecen sus parámetros
 */
#include <stdio.h>
#include <pthread.h>

typedef struct {
	int num;
	char * nombre;
} data;

void * hilo(void *);

int main(int argc, char **argv)
{
	pthread_t tid;
	data param;
	
	// Variable de tipo atributo
	pthread_attr_t atrib;
	
	// Inicializar la variable de atributos
	pthread_attr_init(&atrib);
	
	//Asignar valores a los atributos
	pthread_attr_setdetachstate(&atrib, PTHREAD_CREATE_JOINABLE);
	
	//Crear hilo con parámetros y argumentos a la función
	param.num = 1;
	param.nombre = "Hilo 1";
	
	pthread_create(&tid, &atrib, hilo, (void *) &param);
	
	// Liberar memoria de los atributos
	pthread_attr_destroy(&atrib);
	
	// Join
	pthread_join(tid, NULL);
	
	pthread_exit(NULL);

}

void * hilo(void * arg)
{
	data * param;
	param = (data *) arg;
	printf("Soy el hilo %s con id %d \n", param->nombre, param->num);
	
	pthread_exit(NULL);
}
