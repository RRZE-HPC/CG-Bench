

declare -a matrices=(
	"/home/CG-Bench/test/data/myBigMat.mtx"
	"/home/CG-Bench/test/data/myBigMat_mod1.mtx"
	"/home/CG-Bench/test/data/myBigMat_mod2.mtx"
	"/home/CG-Bench/test/data/myBigMat_mod3.mtx"
	# "/home/CG-Bench/test/data/myBigMat_mod4.mtx"
	# "/home/CG-Bench/test/data/myBigMat_mod5.mtx"
	# "/home/CG-Bench/test/data/myBigMat_mod6.mtx"
	# "/home/CG-Bench/test/data/myBigMat_mod7.mtx"
	# "/home/CG-Bench/test/data/myBigMat_mod8.mtx"
	# "/home/CG-Bench/test/data/myBigMat_mod9.mtx"
	# "/home/CG-Bench/test/data/myBigMat_mod10.mtx"
)

for matrix in "${matrices[@]}";
do 
	matrix_name="${matrix##*/}"
	matrix_name="${matrix_name%.mtx}"
	sed -i "/filename/c\filename ${matrix} " ../../mtx.par
	for num_procs in 2;
	do
		mpirun -n $num_procs ./../../cgBench-ICC ../../mtx.par >> /home/CG-Bench/test/results/reported/${matrix_name}_${num_procs}_ranks_CRS_splits.txt
	done
done
