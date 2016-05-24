#ARIS Exercises

## Login to ARIS

### Get your login credentials

1. Obtain your training username and account.
    
2. Download private ssh key : [link](http://events.hpc.grnet.gr/event/16/)

### Login with SSH
ARIS supercomputer uses login nodes for interactive access and the submission of batch jobs.

Connect to ARIS login nodes via SSH :
#### Linux/Mac

Open a terminal and run

```bash
$ ssh -i /path/to/ssh/key -X <USERNAME>@login.aris.grnet.gr

# -X enables X11 forwarding 

#in case of problems confirm your ssh key permissions
$ chmod 600 /path/to/ssh/key
```

where `<USERNAME>` is your ARIS training account.

#### Windows

Microsoft Windows do not have a built-in SSH client. We recommend downloading the following software:

* SSH client - [PUTTY](http://www.chiark.greenend.org.uk/~sgtatham/putty/)
	  * [configuration instructions for ARIS](http://doc.aris.grnet.gr/login/#putty)
* SSH client - [MobaXterm](http://mobaxterm.mobatek.net/)
* SSH client - [Bitvise](http://doc.aris.grnet.gr/login/#bitvise)
	  * [configuration instructions for ARIS](http://doc.aris.grnet.gr/login/#bitvise)
* File client - [WinSCP](http://winscp.net/eng/index.php)
	  
<!--
Q1. Login enable X11 forwarding
-->

For more information on how to login please read our documentation site [http://doc.aris.grnet.gr/login/#login-to-aris](http://doc.aris.grnet.gr/login/#login-to-aris)

<!--
## [Transfer files](http://doc.aris.grnet.gr/login/#data-transfer)

Terminal: 
```
#send a file
$ scp myimage.png <USERNAME>@login.aris.grnet.gr

#get a file
$ scp <USERNAME>@login.aris.grnet.gr:myimage.png
```
-->

## [User Environment](http://doc.aris.grnet.gr/environment/)

1. Check the available software.

		$ module avail

1. Check the loaded modules.

		$ module list

1. Which is the default GNU compiler ?

1. Load the `gnuplot` tool. We will need this in order to make plots for Ex.2 

	    $ module load gnuplot

1. Inspect the environment changes when loading the `gnuplot` module

		$ module show gnuplot

1. Check the available partitions.

	    $ sinfo -s		

1. Check your account information.

	    $ mybudget
		
		$ myreport		

1. What are the limits for your account ?		

1. Inspect ARIS	file systems
	  
	    $ mmlsquota --block-size 1G

1. Switch to your working directory in order to run the following exercises.		

	    $ cd $WORKDIR

		$ pwd
	    # /work/training/<USERNAME>

1. Check your disk usage

	    # HOME file system
	    $ du -chs $HOME

	    # WORK file system
		$ du -chs $WORKDIR


## Running jobs


In order to run jobs on ARIS you need an account to charge compute hours.
Replace the `<TRAINING_PROJECT>` with your given training project account in the following examples.

### Prepare a SLURM script file

1. Create a sample SLURM script named `my_script.slurm`

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

1. Submit your script to execute on ARIS.

		$ sbatch my_script.slurm
        # Submitted batch job <JOBID> 

1. Check your running jobs.

		$ squeue -u <USERNAME>

1. Inspect the output files.

	    $ cat my_script-<JOBID>.out

1. If you want to cancel your running job.

		$ scancel <JOBID>

	    # or cancel all your running jobs 
		$ scancel -u <USERNAME>

1. Accounting information for completed jobs (current day)

		$ sacct 

1. Try to execute the sample script on multiple nodes

1. Create the same simple SLURM script using the online ARIS script-template: [http://doc.aris.grnet.gr/scripttemplate/](http://doc.aris.grnet.gr/scripttemplate/)

1. For more details about running parallel job on ARIS please read: [http://doc.aris.grnet.gr/run/](http://doc.aris.grnet.gr/run/)

## Ex.1 Application Execution

Examine a simple program that computes π by Monte-Carlo integration of a quarter of a unit circle.
Given is the source code in `C` language, in four different runtime models.

* Serial program: `serialpi.c`
* Multi-threaded program (with OpenMP): `omppi.c`
* Multi-process program (with MPI): `mpipi.c`
* Hybrid program (with MPI+OpenMP): mpiomppi.c

Consult the documentation how to submit jobs for your programming model. [http://doc.aris.grnet.gr/run/#runtime-models](http://doc.aris.grnet.gr/run/#runtime-models)
Following we will create a batch script for each runtime model.  

<!-- dont delete me comment -->
1. Get the source using `git`.
		
		$ git clone https://github.com/hpc-grnet-gr/aris_exercises.git 
		$ cd aris_exercises

1. Build the code using `make`.

		 $ make

		 # Check that you got all the executables
		 # serialpi, omppi, mpipi, mpiomppi

### Serial job execution

Run the serial program using 1 processor.

1. Inspect the file `serial.slurm` 

	    #!/bin/bash
	    
	    #SBATCH --job-name=pi# Job name
	    #SBATCH --ntasks=1 # Total number of tasks
	    #SBATCH --nodes=1 # Total number of nodes requested
	    #SBATCH --ntasks-per-node=1 # Tasks per node
	    #SBATCH --cpus-per-task=1 # Threads per task
	    #SBATCH -t 00:10:00 # Run time (hh:mm:ss) - (max 48h)
	    
	    # Load any necessary modules
	    module load intel
	    
	    # Launch the executable
	    ./serialpi

1. Submit your serial job.

		$ sbatch serial.slurm
	
1. Check the output files.

### OpenMP job execution

Run the OpenMP program using 20 threads.

1. Inspect the file `openmp.slurm`.

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

1. Submit your openmp job.

	    $ sbatch openmp.slurm

### MPI job execution

Run the MPI program using 2 nodes.

1. Inspect the file `mpi.slurm`.

          #!/bin/bash
          
          #SBATCH --job-name=mpipi # Job name
          #SBATCH --ntasks=2 # Total number of tasks
          #SBATCH --nodes=1 # Total number of nodes requested
          #SBATCH --ntasks-per-node=1 # Tasks per node
          #SBATCH --cpus-per-task=1 # Threads per task(=1) for pure MPI
          #SBATCH -t 00:10:00 # Run time (hh:mm:ss) - (max 48h)
          
          # Load any necessary modules
          module load intel
          module load intelmpi
          
          export I_MPI_FABRICS=shm:dapl
          
          # Launch the executable
          srun mpipi

1. Submit your `mpi` job.

	    $ sbatch mpi.slurm

### Hybrid job execution

Run the hybrid program using 2 nodes and 20 threads per node.

1. Correct the following script file `hybrid.slurm`.

        #!/bin/bash
        
        #SBATCH --job-name=mpiomppi # Job name
        #SBATCH --ntasks=40 # Total number of tasks
        #SBATCH --nodes=2 # Total number of nodes requested
        #SBATCH --ntasks-per-node=1 # Tasks per node
        #SBATCH --cpus-per-task=20 # Threads per task(=1) for pure MPI
        #SBATCH -t 00:10:00 # Run time (hh:mm:ss) - (max 48h)
        
        # Load any necessary modules
        module load intel
        module load intelmpi
        
        export I_MPI_FABRICS=shm:dapl
        export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK
        
        # Launch the executable
        srun mpiomppi 

1. Submit your `hybrid` job.

	    $ sbatch hybrid.slurm

## Ex.2 See how well your application scales.

>  Scalability is defined as the ability to handle more work as the size of the computer or application grows.

<!--
Ideal a problem would scale in a linear fashion, that is, the program would speed up by a factor of
N when it runs on a machine having N nodes.
-->

* *Strong scaling* : the problem size remains fixed while the number of nodes increases. (work per node decrease)
* *Weak scaling*: the problem gets bigger and bigger as the number of processors increases. (work per node same)


Given the code in the previous exercise above we shall test how well this application scales.

### *Strong scaling test:* 

1. Keeping the problem size constant, run MPI on only one processor. Compare to the serial calculation to get the overhead associated with MPI.
1. Keeping the problem size run the MPI code for 1, 2, 4, 8 computing nodes.

	Run the the `strong_scale.sh` script to get the timing results.

		$ bash strong_scale.sh

	Check the status or your submitted jobs, output results will be saved in the `mpipi-strong*.log` files.

	    $ squeue -i 5 -u <USERNAME>
	    # press Ctrl + C to exit

1. Make a plot of run time versus number of nodes.

	 You can use `gnuplot` to plot your results.

		# Gather result timings in one file
		$ cat mpipi-strong*.log | grep -v '^#' | sort -n -k 1 > mpipi-strong.dat

		# plot 
		$ gnuplot strong_plot.gnuplot

	You can view the output plot image `mpipi-strong.png`

	    # If you have enabled X11 forwarding in SSH (-X) you can view the output
		$ display mpipi-strong.png

		# or from your laptop download the image file to view it localy
	    # use the path to your ssh key
		$ scp -i /path/to/ssh/key <USERNAME>@login.aris.grnet.gr:/work/training/<USERNAME>/aris_exercises/mpipi-strong.png .


1. Strong scalability would yield a straight line graph. Comment.

### *Weak scaling test:* 
<!--
 Increasing the problem size simultaneously with the number of nodes beeing used.
-->

1. Run the MPI code for 1, 2, 4, 8 computing nodes, with proportionally larger values in each case (2000, 4000, ...)

	Run the `weak_scale.sh` script to get the timing results.

		$ bash weak_scale.sh
	
	Check the status or your submitted jobs, output results will be saved in the mpipi-weak*.log files.

1. Make a plot of the run time versus number of computing nodes.

		$ cat mpipi-weak*.log | grep -v '^#' | sort -n -k 1 > mpipi-weak.dat
		$ gnuplot weak_plot.gnuplot

	Output plot `mpipi-weak.png`

	    # If you have enabled X11 forwarding in SSH (-X) you can view the output
		$ display mpipi-weak.png

		# or from your laptop download the image file to view it localy
		$ scp -i /path/to/ssh/key  <USERNAME>@login.aris.grnet.gr:/work/training/<USERNAME>/aris_exercises/mpipi-weak.png .

1. Weak scaling would imply that the run time remains constant as the problem size and the nummber of compute nodes increase in proportion. Comment.
1. Is this problem more appropriate for weak or strong scaling ?

