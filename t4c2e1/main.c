/* Cálculo de factorial con OpenMP
 * utilizando pragma omp critical
 */
#include <stdio.h>
#include <omp.h>

int main(int argc, char **argv)
{
	
	int i;
	long int fact = 1;
	int numero = 10;
	
	#pragma omp parallel for private(i) shared(fact, numero)
	for (i=2; i <= numero; ++i)
	{	
		#pragma omp critical 
		{
			fact *= i; // fact * i = fact
		}
	}
	
	printf("El factorial de %d = %ld", numero, fact);
}
