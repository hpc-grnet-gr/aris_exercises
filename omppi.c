#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char* argv[])
{
    long int i,count = 0,niter = 100000;
    double x,y,z,pi;
    char *endptr;
    double start,stop;
    int numthreads;

    if (argc == 2 ){
        niter = strtol(argv[1],&endptr,10);
    }

    start = omp_get_wtime();
#pragma omp parallel firstprivate(niter) private(x, y, z, i) reduction(+:count)
    {
        numthreads = omp_get_num_threads();
        unsigned int seed = (unsigned)time(NULL)^omp_get_thread_num();
        #pragma omp for
        for (i=0; i<=niter; i++)
        {
            x = (double)rand_r(&seed)/(double)RAND_MAX;
            y = (double)rand_r(&seed)/(double)RAND_MAX;
            z = ((x*x)+(y*y));
            if (z<=1) count++;
        }
    }
    pi = ((double)count/(double)niter)*4.0;
    stop = omp_get_wtime();

    printf("# Pi: %f\n", pi);         
    printf("# Processors Iterations Time(s)\n");
    printf("%d\t%ld\t%f\n",numthreads,niter,stop-start);

    return 0;
}
