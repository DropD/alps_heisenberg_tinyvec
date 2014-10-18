import subprocess32, sys
sys.path.append('/opt/alps/lib')
import pyalps
from matplotlib import pyplot as plt
import numpy as np

def h5get(ar, meas):
    base_path = 'simulation/results/{}/mean'.format(meas)
    val = base_path + '/value'
    err = base_path + '/error'
    return np.array((ar[val], ar[err]))

NUM_RUNS = 12
parameter_files = ['param.txt.task{}.in.xml'.format(i) for i in range(1, NUM_RUNS + 1)]
result_files    = ['param.txt.task{}.in.out.h5'.format(i) for i in range(1, NUM_RUNS + 1)]
h5_T_path       = 'parameters/T'
h5_L_path       = 'parameters/L'
program         = '../../build/single'
plot_file       = 'mag_sus.pdf'

if __name__ == '__main__':
    if 'run' in sys.argv:
        subprocess32.call(['/opt/alps/bin/parameter2xml', 'param.txt'])
        for run in range(NUM_RUNS):
            run_out = subprocess32.check_output([program, parameter_files[run]])
            print '--- run {} ---'.format(run)
            print run_out

    if 'plot' in sys.argv:
        y_err = []
        y = []
        x = []

        for run in range(NUM_RUNS):
            ar  = pyalps.hdf5.iArchive(result_files[run])
            T   = ar[h5_T_path]
            L   = ar[h5_L_path]
            m   = h5get(ar, 'Magnetization')
            m2  = h5get(ar, 'Magnetization^2')

            beta = 1. / T
            V = L * L * L
            mm = m*m
            chi = beta * V * (m2 - mm)

            y.append(chi[0])
            y_err.append(chi[1])
            x.append(T)

        plt.plot(x, y)
        plt.xlabel(r'$\frac{T}{K}$')
        plt.ylabel(r'$\chi$')
        plt.savefig(plot_file)
        subprocess32.call(['open', plot_file])
