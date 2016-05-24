#!/bin/bash

# WEAK SCALING TEST
# scale the problem size along with the nodes 

#for NPROCS in 20 40 80 160;
for NPROCS in 20 40 80;
do
    SIZE=100000000000
    export SIZE=$(( (NPROCS / 20) * SIZE))
    sbatch -n ${NPROCS} \
           -J mpipi-weak \
           -o mpipi-weak-%j.${SIZE}.${NPROCS}.out \
           -e mpipi-weak-%j.${SIZE}.${NPROCS}.err \
           mpipi.run
    sleep 1 # pause to be kind to the scheduler
done
