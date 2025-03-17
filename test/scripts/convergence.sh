#!/bin/bash -l
#SBATCH -J convergence_tests
#SBATCH -N 1
#SBATCH --cpus-per-task=1
#SBATCH -t 01:00:00
#SBATCH --output=./results/%j_%x.out 

unset SLURM_EXPORT_ENV 

module load intel intelmpi

export I_MPI_PIN=1
export I_MPI_PIN_PROCESSOR_LIST="allcores"

declare -a matrices=(
	# "data/cant.par"
	# "data/dense2.par"
	# "data/mac_econ_fwd500.par"
	# "data/pwtk.par"
	# "data/RM07R.par"
	# "data/scircuit.par"
	# "data/cant_symm.par"
	# "data/dlr1.par"
	# "data/mawi_201512020130.par"
	# "data/pwtk_symm.par"
	# "data/rma10.par"
	# "data/shipsec1.par"
	# "data/com-Orkut.par"
	# "data/Hamrle3.par"
	# "data/mc2depi.par"
	# "data/qcd5_4.par"
	# "data/rrze3.par"
	# "data/shipsec1_symm.par"
	# "data/consph.par"
	# "data/hpccg-100.par"
	# "data/ML_Geer.par"
	# "data/rail4284.par"
	# "data/rrze3_rcm.par"
	# "data/sx-askubuntu.par"
	# "data/consph_symm.par"
	# "data/HPCG-128-128-128.par"
	# "data/nlpkkt120.par"
	# "data/random2M20.par"
	"data/random4M10.par"
	# "data/rrze3_vv.par"
	# "data/vas_stokes_4M.par"
	# "data/cop20k_A.par"
	# "data/HPCG-192-192-192.par"
	# "data/pdb1HYS.par"
	# "data/andom4M10.par"
	# "data/scai1.par"
	# "data/webbase-1M.par"
	# "data/cop20k_A_symm.par"
	# "data/kkt_power.par"
	# "data/pdb1HYS_symm.par"
	# "data/rgg_n_2_24_s0.par"
	# "data/scai2.par"
)

for matrix in "${matrices[@]}"
do 
	matrix_name="${matrix##*/}"
	matrix_name="${matrix_name%.par}"

	mkdir -p att1/${matrix_name}_convergence

	# MPI Only
	export OMP_NUM_THREADS=1
	for proc_count in 1 2 18 36 72;
	do
		mpirun -n $proc_count ./../cgBench-ICC $matrix >> att1/${matrix_name}_convergence/MPI_${proc_count}_procs.txt
	done

	# OpenMP Only
	for thread_count in 1 2 18 36 72;
	do
		export OMP_NUM_THREADS=$thread_count
		mpirun -n 1 ./../cgBench-ICC $matrix >> att1/${matrix_name}_convergence/OPENMP_${OMP_NUM_THREADS}_threads.txt
	done

	# Hybrid
	for proc_count in 2 18 36;
	do
		export OMP_NUM_THREADS=$((72 / proc_count))
		mpirun -n $proc_count ./../cgBench-ICC $matrix >> att1/${matrix_name}_convergence/HYBRID_${proc_count}_procs_${OMP_NUM_THREADS}_threads.txt
	done
done