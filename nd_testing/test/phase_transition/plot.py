import subprocess32, sys
sys.path.append('/opt/alps/lib')
import pyalps
from matplotlib import pyplot as plt

NUM_RUNS = 12
parameter_files = ['param.txt.task{}.in.xml'.format(i) for i in range(1, NUM_RUNS + 1)]
result_files    = ['param.txt.task{}.in.out.h5'.format(i) for i in range(1, NUM_RUNS + 1)]
h5_chi_path     = 'simulation/results/Magnetic Susceptibility/mean'
h5_T_path       = 'parameters/T'
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
            ar = pyalps.hdf5.iArchive(result_files[run])
            y.append(ar[h5_chi_path+'/value'])
            y_err.append(ar[h5_chi_path+'/error'])
            x.append(ar[h5_T_path])

        plt.plot(x, y)
        plt.xlabel(r'$\frac{T}{K}$')
        plt.ylabel(r'$\chi$')
        plt.savefig(plot_file)
        subprocess32.call(['open', plot_file])
