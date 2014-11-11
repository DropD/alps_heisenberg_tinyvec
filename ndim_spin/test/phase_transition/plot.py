import subprocess32, sys
sys.path.append('/opt/alps/lib')
import pyalps
from matplotlib import pyplot as plt
import numpy as np
#~ sys.path.append('/Users/ricoh/Prog/python/mdebug/')
#~ from mdebug import mdebug
#~ from analyzer import name_analyzer
#~ DBG = mdebug(analyzer = name_analyzer())

def h5get(ar, meas):
    base_path = 'simulation/results/{}/mean'.format(meas)
    val = base_path + '/value'
    err = base_path + '/error'
    return np.array((ar[val], ar[err]))

NUM_RUNS = 13
parameter_files = ['param.txt.task{}.in.xml'.format(i) for i in range(1, NUM_RUNS + 1)]
result_files    = ['param.txt.task{}.in.out.h5'.format(i) for i in range(1, NUM_RUNS + 1)]
h5_T_path       = 'parameters/T'
h5_L_path       = 'parameters/L'
program         = '../../build-release/single'
plot_file       = 'mag_sus.pdf'
corr_file       = 'corr.pdf'

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
            T   = float(ar[h5_T_path])
            L   = float(ar[h5_L_path])
            m   = h5get(ar, 'Magnetization')
            m2  = h5get(ar, 'Magnetization^2')

            beta = 1. / T
            V = L * L * L
            mm = [np.dot(m[i,:], m[i,:]) for i in [0,1]]
            chi = beta * V * (m2 - mm)

            y.append(chi[0])
            y_err.append(chi[1])
            x.append(T)

        x = np.array(x)
        y = np.array(y)
        y_err = np.array(y_err)

        plt.figure()
        plt.fill_between(x, y+y_err, y-y_err)
        plt.xlabel(r'$\frac{T}{K}$')
        plt.ylabel(r'$\chi$')
        plt.savefig(plot_file)
        subprocess32.call(['open', plot_file])

        plt.figure()
        corr = h5get(ar, 'Correlations')
        dist = h5get(ar, 'Distances')
        plt.plot(dist[0], corr[0], 'x')
        plt.savefig(corr_file)
        subprocess32.call(['open', corr_file])
