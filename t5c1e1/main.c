#include <mpi.h>
#include <stdio.h>

int main(int argc, char * argv[])
{
    int  numtasks, rank, rc; 

    rc = MPI_Init(&argc,&argv);

    if (rc != MPI_SUCCESS) {

        printf ("Error al iniciar MPI \n");

        MPI_Abort(MPI_COMM_WORLD, rc);

    }

    
    MPI_Comm_size(MPI_COMM_WORLD,&numtasks);

    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    printf ("Soy la tarea %d de %d\n", rank, 	numtasks);

    
    /*******  hacer algo *******/


    MPI_Finalize();
	
	return 0;

}


