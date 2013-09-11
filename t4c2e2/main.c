/* Cálculo de factorial con OpenMP
 * utilizando reduction
 */
#include <stdio.h>
#include <omp.h>

int main(int argc, char **argv)
{
	
	int i, tid;
	long long int fact = 1;
	int numero;
	
	printf("Entra el número para calcularle el factorial: ");
	scanf("%d", &numero);
	
	#pragma omp parallel private(i, tid) shared(numero) num_threads(8) if (numero > 100)
	{
		tid = omp_get_thread_num();
		#pragma omp for reduction(*:fact) schedule(dynamic, 1) 
		for (i=2; i <= numero; ++i)		
		{	
			fact *= i; // fact * i = fact
			printf("Hilo %d hace iteración %d \n", tid, i);
		}
	}
	printf("El factorial de %d = %lld", numero, fact);
}
