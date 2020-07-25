#!/bin/bash
# This file test.sh is a sample script to run the many jobs by making use of multiple cores
# To have output file defined as output.txt, run your script with sbatch -o slurm-%A_%a.out test.sh
# command where %A is the id of the submitted jobs and %a is {0..ntasks}
# To have one output file for all simultaneous task, run your script with sbatch test.sh

# set the partition where the job will run
#SBATCH --partition=halley

# The following line defines the name of the submitted job
#SBATCH --job-name=find_max

# The default output file if we run the script with the command sbatch test.sh
#SBATCH --output=output.txt

# set the number of nodes and processes per node
# That is, we will run this many tasks simultaneously
#SBATCH --nodes=16

# mail alert at start, end and abortion of execution
# The user will be mailed when the job starts and stops or aborts
# --mail-type=<type> where <type> may be BEGIN, END, FAIL, REQUEUE or ALL (for any change of job state)
#SBATCH --mail-type=ALL

# send mail to this address
#SBATCH --mail-user=e2098739@ceng.metu.edu.tr

# Launch the command/application
mpiexec -n 16 ./summer input.txt 1000000
