#!/bin/bash

#SBATCH --job-name=pi# Job name
#SBATCH --ntasks=1 # Total number of tasks
#SBATCH --nodes=1 # Total number of nodes requested
#SBATCH --ntasks-per-node=1 # Tasks per node
#SBATCH --cpus-per-task=20 # Threads per task
#SBATCH -t 00:10:00 # Run time (hh:mm:ss) - (max 48h)

# Load any necessary modules
module load intel

export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK

# Launch the executable
srun omppi
