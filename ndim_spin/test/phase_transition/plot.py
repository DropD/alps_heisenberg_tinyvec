import subprocess32 as sp
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
sp_analyze = subparsers.add_parser('analyze')

parser.add_argument('infile', default='param.txt')

sp_run.add_argument('-j')
sp_run.add_argument('--no-analysis', action='store_true')
sp_run.add_argument('program')

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
            print '--- run {} ---'.format(run_infile)
            print run_out
    if not args.no_analysis:
        analyze(args)

def get_chi(result_files):
    T   = np.array([p['T'] for p in pyalps.loadProperties(result_files)])
    V   = np.array([p['L']**3 for p in pyalps.loadProperties(result_files)])
    mag  = pyalps.loadMeasurements(result_files, what='Magnetization')
    mag2 = pyalps.loadMeasurements(result_files, what='Magnetization^2')
    from pyalps.alea import MCScalarData as msd
    mm  = np.array([np.sum([msd(i.mean, i.error).sq() for i in j[0].y]) for j in mag])
    m2  = np.array([msd(i[0].y[0].mean, i[0].y[0].error) for i in mag2])

    beta = 1. / T
    chi = beta * V * (m2 - mm)

    result = np.array(zip(T, chi), dtype = [('T', np.float), ('chi', 'object')])
    result.sort(order='T')
    return result

def get_corr(result_files):
    T    = np.array([p['T'] for p in pyalps.loadProperties(result_files)])
    corr = pyalps.loadMeasurements(result_files, what = 'Correlations')
    dist = pyalps.loadMeasurements(result_files, what = 'Distances')

    corr_data = [np.array(zip(dist[i][0].y.mean, corr[i][0].y), 
                         dtype = [('dist', np.float), ('corr', 'object')])
                 for i in range(len(dist))
                ]
    cbins = [{i:[] for i in np.unique(j['dist'])} for j in corr_data]
    for i in range(len(corr_data)):
        for cj in corr_data[i]:
            cbins[i][cj['dist']].append(cj['corr'])

    ct = [('dist', 'f8'), ('corr', 'object')]
    result = [np.array([(j, np.abs(np.sum(cbi[j]) / float(len(cbi[j])))) for j in cbi], dtype=ct) for cbi in cbins]
    for r in result:
        r.sort(order='dist')
    return result, T

def analyze(args):
    print 'running analysis'
    runs = pyalps.getResultFiles(prefix = args.infile)

    chi_data = get_chi(runs)
    T = chi_data['T']
    chi = [c.mean for c in chi_data['chi']]
    chi_err = [c.error for c in chi_data['chi']]

    plt.figure()
    plt.errorbar(T, chi, yerr = chi_err)
    yl = plt.ylim()
    plt.vlines(1. / 0.693035, yl[0], yl[1])
    plt.ylim(yl)
    xl =(min(T), max(T))
    plt.xlim(xl)
    plt.xlabel(r'Temperature $T$')
    plt.ylabel(r'Magnetic Susceptibility $\chi$')
    plt.savefig('{}.plot_chi.pdf'.format(args.infile))

    idx = [1, len(runs)/3, -2]
    T = np.array([p['T'] for p in pyalps.loadProperties(runs)])
    runsorted = np.array(zip(T, runs), dtype=[('T', 'f8'), ('run', object)])
    runsorted.sort(order = 'T')
    corr_data, T = get_corr([runsorted[i]['run'] for i in idx])

    plt.figure()
    for i in range(len(corr_data)):
        temp = T[i]
        corr = corr_data[i]
        x = corr['dist']
        y = [i.mean for i in corr['corr']]
        ye = [i.error for i in corr['corr']]
        plt.errorbar(x, y, yerr = ye, label = 'T = {}'.format(temp))
    plt.ylim((-0.01, 1.01))
    plt.xlabel(r'Distance $r$ in Lattice Units')
    plt.ylabel(r'Pair Correlation Function $g(r)$')
    plt.legend()
    plt.savefig('{}.plot_corr.pdf'.format(args.infile))

sp_run.set_defaults(func=run_exp)
sp_analyze.set_defaults(func=analyze)

if __name__ == '__main__':
    args = parser.parse_args()
    args.func(args)
