bin=/cluster/home/ricoh/work/heisenberg/tinivec/build
wrk=/cluster/home/ricoh/experiments/tinivec

bsub -J bm_plus $bin/plus $wrk/bm_plus.dat 20
bsub -J bm_minus $bin/minus $wrk/bm_minus.dat 20
bsub -J bm_divide $bin/divide $wrk/bm_divide.dat 20
bsub -J bm_multiply $bin/multiply $wrk/bm_multiply.dat 20
