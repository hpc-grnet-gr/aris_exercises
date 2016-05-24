CC=icc
MPICC=mpiicc

all: serial mpi omp hybrid

serial:
	$(CC) serialpi.c -o serialpi

omp: 
	$(CC) -openmp omppi.c -o omppi

mpi:
	$(MPICC) mpipi.c -o mpipi

hybrid:
	$(MPICC) -openmp mpiomppi.c -o mpiomppi	

clean:
	rm -f serialpi mpipi omppi mpiomppi
