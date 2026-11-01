#!/bin/bash
#SBATCH --job-name=solve13
#SBATCH --array=1,2,3,4
#SBATCH --time=7-00:00:00               # Max runtime (HH:MM:SS) - adjust if Minion takes longer
#SBATCH --mem=4G                       # RAM per job
#SBATCH --cpus-per-task=1
#SBATCH --output=logs/%a.out       # Standard output log (%a gets replaced by the ID 1-139)
#SBATCH --error=logs/%a.err        # Error log

# Create a logs directory if it doesn't exist so your folder doesn't get messy
mkdir -p logs

/usr/bin/time ./"$SLURM_ARRAY_TASK_ID" eq13_1527.txt 
