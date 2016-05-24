#!/bin/bash

# STRONG SCALING TEST
# keep the problem size constant, scale nodes

export SIZE=100000000000
#for NPROCS in 20 40 80 160;
for NPROCS in 20 40 80 160;
do
    sbatch -n ${NPROCS} \
           -J mpipi-strong \
           -o mpipi-strong-%j.${SIZE}.${NPROCS}.out \
           -e mpipi-strong-%j.${SIZE}.${NPROCS}.err \
           mpipi.run
    sleep 1 # pause to be kind to the scheduler
done
