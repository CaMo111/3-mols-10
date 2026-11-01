#!/bin/bash
#SBATCH --job-name=minion_array
#SBATCH --array=107,139
#SBATCH --time=2-00:00:00               
#SBATCH --mem=4G                       
#SBATCH --cpus-per-task=4              
#SBATCH --output=logs/job_%a.out       
#SBATCH --error=logs/job_%a.err        

mkdir -p logs

bash ./findsinglesol.sh $SLURM_ARRAY_TASK_ID