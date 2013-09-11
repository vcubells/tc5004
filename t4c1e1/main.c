#include <stdio.h>
#include <omp.h>

#define N 100000

int tp = 10;
	
#pragma omp threadprivate(tp)

int main(int argc, char **argv)
{
	int i = 10;
	int j = 5;
	int c = 0;
	int s = 0;
	int tid;
	
	omp_set_dynamic(0);
	
	printf("i = %5d j = %5d c = %5d s = %5d tp = %5d \n", i, j, c, s, tp);
	
	#pragma omp parallel private(i) firstprivate(j) shared(c) 
						{
							tid = omp_get_thread_num();
							printf("Soy el hilo %d\n", tid);
							printf("Valor con que entran las variables al hilo %d\n", tid);
							printf("i = %5d j = %5d c = %5d s = %5d tp = %5d \n", i, j, c, s, tp);
							i = rand() % 1000;
							j = rand() % 1000;
							c = rand() % 1000;
							s = rand() % 1000;
							tp = rand() % 1000;
							printf("Valor con que salen las variables al hilo %d\n", tid);
							printf("i = %5d j = %5d c = %5d s = %5d tp = %5d \n", i, j, c, s, tp);
						}
	printf("Valor de las variables después de la 1ra sección paralela\n");
	printf("i = %5d j = %5d c = %5d s = %5d tp = %5d \n", i, j, c, s, tp);
	
	#pragma omp parallel private(i) firstprivate(j) shared(c) 
						{
							tid = omp_get_thread_num();
							printf("Soy el hilo %d\n", tid);
							printf("Valor con que entran las variables al hilo %d\n", tid);
							printf("i = %5d j = %5d c = %5d s = %5d tp = %5d \n", i, j, c, s, tp);
							i = rand() % 1000;
							j = rand() % 1000;
							c = rand() % 1000;
							s = rand() % 1000;
							tp = rand() % 1000;
							printf("Valor con que salen las variables al hilo %d\n", tid);
							printf("i = %5d j = %5d c = %5d s = %5d tp = %5d \n", i, j, c, s, tp);
						}
						
	printf("Valor de las variables después de la 2ra sección paralela\n");
	printf("i = %5d j = %5d c = %5d s = %5d tp = %5d \n", i, j, c, s, tp);
}
