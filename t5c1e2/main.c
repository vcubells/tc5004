#include <mpi.h>
#include <stdio.h>


int main(argc,argv) 
int argc;
char *argv[];  {

    int numtasks, rank, dest, source, rc, count, tag=1;  
    char inmsg, outmsg='x';
    MPI_Status Stat;
    char hostname[MPI_MAX_PROCESSOR_NAME];
    int  longitud;
    
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Get_processor_name(hostname, &longitud);
    
    if (rank == 0) {
        dest = 1;
        source = 1;

        rc = MPI_Send(&outmsg, 1, MPI_CHAR, dest, tag, MPI_COMM_WORLD);
        rc = MPI_Recv(&inmsg, 1, MPI_CHAR, source, tag, MPI_COMM_WORLD, &Stat);
    } 

    else if (rank == 1) {
        dest = 0;
        source = 0;

        rc = MPI_Recv(&inmsg, 1, MPI_CHAR, source, tag, MPI_COMM_WORLD, &Stat);
        rc = MPI_Send(&outmsg, 1, MPI_CHAR, dest, tag, MPI_COMM_WORLD);
    }

    rc = MPI_Get_count(&Stat, MPI_CHAR, &count);

    printf("Task %d: Received %d char(s) from task %d (%s) with tag %d \n",
	rank, count, Stat.MPI_SOURCE, hostname, Stat.MPI_TAG);

    MPI_Finalize();
	
	return 0;

}


