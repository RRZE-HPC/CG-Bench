#!/bin/bash -l

declare -a matrices=(
    "/home/titan/unrz/unrz55/matrices/dlr1.mtx"
		"/home/titan/unrz/unrz55/matrices/HPCG-128-128-128.mtx"
		"/home/titan/unrz/unrz55/matrices/HPCG-192-192-192.mtx"
		"/home/titan/unrz/unrz55/matrices/Hamrle3.mtx"
		"/home/titan/unrz/unrz55/matrices/ML_Geer.mtx"
		"/home/titan/unrz/unrz55/matrices/RM07R.mtx"
		"/home/titan/unrz/unrz55/matrices/cant.mtx"
		"/home/titan/unrz/unrz55/matrices/cant_symm.mtx"
		"/home/titan/unrz/unrz55/matrices/com-Orkut/com-Orkut.mtx"
    "/home/titan/unrz/unrz55/matrices/consph.mtx"
		"/home/titan/unrz/unrz55/matrices/consph_symm.mtx"
		"/home/titan/unrz/unrz55/matrices/cop20k_A.mtx"
		"/home/titan/unrz/unrz55/matrices/cop20k_A_symm.mtx"
		"/home/titan/unrz/unrz55/matrices/dense2.mtx"
		"/home/titan/unrz/unrz55/matrices/hpccg-100.mtx"
		"/home/titan/unrz/unrz55/matrices/kkt_power.mtx"
		"/home/titan/unrz/unrz55/matrices/mac_econ_fwd500.mtx"
		"/home/titan/unrz/unrz55/matrices/mawi_201512020130.mtx"
    "/home/titan/unrz/unrz55/matrices/mc2depi.mtx"
		"/home/titan/unrz/unrz55/matrices/nlpkkt120.mtx"
		"/home/titan/unrz/unrz55/matrices/pdb1HYS.mtx"
		"/home/titan/unrz/unrz55/matrices/pdb1HYS_symm.mtx"
		"/home/titan/unrz/unrz55/matrices/pwtk.mtx"
		"/home/titan/unrz/unrz55/matrices/pwtk_symm.mtx"
		"/home/titan/unrz/unrz55/matrices/qcd5_4.mtx"
		"/home/titan/unrz/unrz55/matrices/rail4284.mtx"
		"/home/titan/unrz/unrz55/matrices/random2M20.mtx"
		"/home/titan/unrz/unrz55/matrices/random4M10.mtx"
		"/home/titan/unrz/unrz55/matrices/rgg_n_2_24_s0.mtx"
		"/home/titan/unrz/unrz55/matrices/rma10.mtx"
		"/home/titan/unrz/unrz55/matrices/rrze3.mtx"
		"/home/titan/unrz/unrz55/matrices/rrze3_rcm.mtx"
		"/home/titan/unrz/unrz55/matrices/rrze3_vv.mtx"
		"/home/titan/unrz/unrz55/matrices/scai1.mtx"
		"/home/titan/unrz/unrz55/matrices/scai2.mtx"
		"/home/titan/unrz/unrz55/matrices/scircuit.mtx"
		"/home/titan/unrz/unrz55/matrices/shipsec1.mtx"
		"/home/titan/unrz/unrz55/matrices/shipsec1_symm.mtx"
		"/home/titan/unrz/unrz55/matrices/sx-askubuntu/sx-askubuntu.mtx"
		"/home/titan/unrz/unrz55/matrices/vas_stokes_4M.mtx"
		"/home/titan/unrz/unrz55/matrices/webbase-1M.mtx"
)

for filepath in "${matrices[@]}"
do 
	matrix_name="${filepath##*/}"
	matrix_name="${matrix_name%.mtx}"
	touch data/${matrix_name}.par
	echo "#==============================================================================" >> data/${matrix_name}.par
  echo "#                              HPCG Matrix market                              " >> data/${matrix_name}.par
  echo "#==============================================================================" >> data/${matrix_name}.par
	echo "" >> data/${matrix_name}.par
	echo "filename ${filepath} #Space is required after string!" >> data/${matrix_name}.par
	echo "" >> data/${matrix_name}.par
	echo "itermax 150" >> data/${matrix_name}.par
	echo "eps 0.0" >> data/${matrix_name}.par
done