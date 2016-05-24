#!/bin/bash
#SBATCH --job-name=my_script    # Job name
#SBATCH --ntasks=1              # Number of tasks
#SBATCH --time=00:01:00         # Run time (hh:mm:ss) - 1 minute 
#SBATCH --account=<TRAINING_PROJECT>

module load gnu intel intelmpi        #load any needed modules

echo "Start at `date`"

# Job steps
srun hostname
srun sleep 30

echo "End at `date`"
