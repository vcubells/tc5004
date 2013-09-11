#include <mpi.h>
#include <stdio.h>
#include <omp.h>

#define N 1000

int main(int argc, char * argv[])
{
    int  numprocs, idproc, rc, fragmento, inicio, fin;
	int i, contador = 0;
	double hi, hf;
	int suma = 0;
	int lista[N];
	char hostname[MPI_MAX_PROCESSOR_NAME];
	int longitud;
	int  nhilos, tid;

    rc = MPI_Init(&argc,&argv);
    
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);

    MPI_Comm_rank(MPI_COMM_WORLD,&idproc);

    MPI_Get_processor_name(hostname, &longitud);

	//Inicializar el vector
	if (idproc == 0)
	{
		hi = MPI_Wtime();
		
		#pragma omp parallel for private(i) shared(lista)
		for (i = 0; i < N; ++i)
		{
			lista[i] = 1;
		}
		
	}
	
	//Enviar por boroadcast a todos los procesadores
	MPI_Bcast(lista, N, MPI_INT, 0, MPI_COMM_WORLD);
	
	//Trabajo de cada procesador
	fragmento = N / numprocs;
	inicio = idproc * fragmento;
	fin = inicio + fragmento;
	
	#pragma omp parallel private(i) default(shared)
	{
		nhilos = omp_get_num_threads();
		tid = omp_get_thread_num();
		#pragma omp for reduction(+:contador)
		for(i = inicio; i < fin; ++i)
		{
			contador += lista[i];
			printf("--- Soy el procesador %d (%s). Soy el hilo %d de un total de %d y proceso la posición %d \n", idproc, hostname, tid, nhilos, i);
		}
	}
	
	MPI_Reduce(&contador, &suma, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

	if (idproc == 0)
	{
		printf("*** La suma total es %d \n", suma);
		hf = MPI_Wtime();
		printf("Tiempo de paralelismo = %f\n", hf-hi);
	}
	
    MPI_Finalize();
	
	return 0;

}


