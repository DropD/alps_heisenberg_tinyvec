import subprocess32 as sp, 
import sys, os, argparse, pyalps, re
from matplotlib import pyplot as plt
import numpy as np

def h5get(ar, meas):
    base_path = 'simulation/results/{}/mean'.format(meas)
    val = base_path + '/value'
    err = base_path + '/error'
    return np.array([ar[val], ar[err]], dtype=np.dtype([('value', np.float), ('error', np.float)]))

parser = argparse.ArgumentParser(description='Run and analyze heisenberg simulation experiment')
subparsers = parser.add_subparsers()

sp_run = subparsers.add_parser('run')
sp_analyze = subparsers.add_parser('anayze')

parser.add_argument('infile', default='param.txt')

sp_run.add_argument('-j')
sp_run.add_argument('--no-analysis', action='store_true')
sp_run.add_argument('program')
sp_run.set_defaults(func=run_exp)

sp_replot.set_defaults(func=plot)

def run_exp(args):
    sp.call(['parameter2xml', args.infile])
    runs = [f for f in os.listdir(os.getcwd()) if re.match('{}.task\d*.in.xml'.format(args.infile), f)]
    if args.j:
        prog_call = ['parallel', '-j', args.j, args.program, ':::']
        prog_call.extend(runs)
        run_out = sp.check_output(prog_call)
    else:
        for run_infile in runs:
            run_out = sp.check_output([args.program, run_infile])
            print '--- run {} ---'.format(run)
            print run_out
    if not args.no_analysis:
        analyze(args)

def get_chi(result_files)
    ar  = pyalps.hdf5.iArchive(run_outfile)
    T   = np.array([p['T'] for p in pyalps.loadProperties(result_files)])
    V   = np.array([p['L']**3 for p in pyalps.loadProperties(result_files)])
    mm  = np.array([mag[0].y[0].sq() for mag in pyalps.loadMeasurements(result_files, what = 'Magnetization')])
    m2  = np.array([msq[0].y[0] for mag in pyalps.loadMeasurements(result_files, what = 'magnetization^2')])

    beta = 1. / T
    chi = beta * V * (m2 - mm)

    return np.array(zip(T, chi), dtype = [('T', np.float), ('chi', np.float)])

def get_corr(result_file):
    ar  = pyalps.hdf5.iArchive(run_outfile)
    corr = h5get(ar, 'Correlations')
    dist = h5get(ar, 'Distances')

    corr_data = np.array(zip(dist, corr), 
                         dtype = [('dist', np.float), ('corr', np.float)])
    corr_data.sort(order='dist')
    
    g = np.array([(dist, 0., 0.) for dist in np.unique(corr_data['dist'])],
                 dtype = [('dist', np.float), ('corr', np.float), ('err', np.float)])

def analyze(args)
    runs = pyalps.getResultFiles(prefix = args.infile)

    chi_data = get_chi()
    T = chi_data['T']
    chi = [c.mean for c in chi_data['chi']]
    chi_err = [c.error for c in chi_data['chi']]

    plt.figure()
    plt.errorbar(T, chi, yerr = chi_err)
    plt.vline(1. / 0.693035)
    plt.xlabel(r'Temperature $\frac{T}{J}$')
    plt.ylabel(r'Magnetic Susceptibility $\chi$')
    plt.savefig('{}.plot_chi.pdf'.format(args.infile))

    plt.figure()
    corr = h5get(ar, 'Correlations')
    dist = h5get(ar, 'Distances')
    xc = []
    yc = []
    yc_e = []
    for d in dist[0]:
        if not d in xc:
            xc.append(d)
            cd = [corr[0][i] for i in range(len(corr[0])) if dist[0][i] == d]
            yc.append(np.mean(cd))
            yc_e.append(np.std(cd))
    c = np.array([(xc[i], abs(yc[i]), yc_e[i]) for i in range(len(xc))], dtype = [('dist', float), ('corr', float), ('err', float)])
    c.sort(order='dist')
    plt.errorbar(c['dist'], c['corr'], yerr = c['err'])
    plt.savefig(corr_file)

if __name__ == '__main__':
    parser.parse_args()
