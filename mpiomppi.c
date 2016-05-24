#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "mpi.h"

int main(int argc, char* argv[])
{
    long int i,count = 0,niter = 100000;
    long int local_count = 0, local_niter = 0;
    double x,y,z,pi;
    char *endptr;
    double start,stop;
    int numthreads;
    int rank,size;


    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (argc == 2 ){
        niter = strtol(argv[1],&endptr,10);
    }

    if(rank == 0) { start = MPI_Wtime(); }

    if (rank == 0) {
        local_niter = niter - (size-1)*(niter/size);
    } else {
        local_niter = niter/size;
    }

#pragma omp parallel firstprivate(local_niter) private(x, y, z, i) reduction(+:local_count)
    {
        numthreads = omp_get_num_threads();
        unsigned int seed = (unsigned)time(NULL)^omp_get_thread_num();
        #pragma omp for
        for (i=0; i<=local_niter; i++)
        {
            x = (double)rand_r(&seed)/(double)RAND_MAX;
            y = (double)rand_r(&seed)/(double)RAND_MAX;
            z = ((x*x)+(y*y));
            if (z<=1) local_count++;
        }
    }

    MPI_Reduce(&local_count, &count, 1, MPI_LONG, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&local_niter, &niter, 1, MPI_LONG, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {      
        pi = ((double)count/(double)niter)*4.0;   
        stop = MPI_Wtime();

        printf("# Pi: %f\n", pi);
        printf("# Processors Iterations Time(s)\n");
        printf("%d\t%ld\t%f\n",size*numthreads,niter,stop-start);
    }
    MPI_Finalize();
    return 0;
}
