#include <stdio.h>
#include <time.h>
#include <stdlib.h>

static double get_second (void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (double)tv.tv_sec + (double)tv.tv_usec / 1000000.0;
}

int main(int argc, char* argv[])
{
    long int i,count = 0,niter = 100000;
    double x,y,z,pi;
    char *endptr;
    double start,stop;

    if (argc == 2 ){
        niter = strtol(argv[1],&endptr,10);
    }

start = get_second();
    unsigned int seed =(unsigned)time(NULL);
    for (i=0; i<=niter; i++)
    {
        x = (double)rand_r(&seed)/(double)RAND_MAX;
        y = (double)rand_r(&seed)/(double)RAND_MAX;
        z = ((x*x)+(y*y));
        if (z<=1) count++;
    }
    pi = ((double)count/(double)niter)*4.0;
stop = get_second();

    printf("# Pi: %f\n", pi);         
    printf("# Processors Iterations Time(s)\n");
    printf("%d\t%ld\t%f\n",1,niter,stop-start);

    return 0;
}
