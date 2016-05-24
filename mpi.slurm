#!/bin/bash

#SBATCH --job-name=mpipi # Job name
#SBATCH --ntasks=2 # Total number of tasks
#SBATCH --nodes=2 # Total number of nodes requested
#SBATCH --ntasks-per-node=1 # Tasks per node
#SBATCH --cpus-per-task=1 # Threads per task(=1) for pure MPI
#SBATCH -t 00:10:00 # Run time (hh:mm:ss) - (max 48h)

# Load any necessary modules
module load intel
module load intelmpi

export I_MPI_FABRICS=shm:dapl

# Launch the executable
srun mpipi 
