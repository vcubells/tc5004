#include <stdio.h>
#include <omp.h>

#define N 100
#define M 100

int main(int argc, char **argv)
{
	int i, j, tid, tidm;
	omp_set_nested(1);
	#pragma omp parallel for private(i, tidm)
		for(i=0; i < N; ++i)
		{
			tidm = omp_get_thread_num();
			#pragma omp parallel for private(j, tid) shared(tidm)
			for(j=0; j < M; ++j)
			{
				tid = omp_get_thread_num();
				printf("Hilo %d-%d hace %d - %d \n", tidm, tid, i, j);
			}
		}
	
}
