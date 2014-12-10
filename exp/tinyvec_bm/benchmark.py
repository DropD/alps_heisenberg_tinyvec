#!python

import subprocess32 as sp
import sys, os, argparse, pyalps, re
from matplotlib import pyplot as plt
from ethpy import datio as dio
from ethpy import fncplot as fpl
import numpy as np

ops = ['plus', 'minus', 'divide', 'multiply']

class commandline_interface(object):
    def __init__(self):
        self.parser = argparse.ArgumentParser(description='Run and and plot tinyvector benchmarks')
        self.parser.add_argument('-v', '--version', action='version', version='%(prog)s 1.0')
        self.subparsers = self.parser.add_subparsers(title='subcommands')

        self.sp_run = self.subparsers.add_parser('run', help='run the benchmarks and create plots')
        self.sp_analyze = self.subparsers.add_parser('plot', help='''create runtime and speedup plots''')
        #~ self.sp_clean = self.subparsers.add_parser('clean', help='''remove all intermediary files''')


        self.sp_run.add_argument('binpath', help='the path to the benchmark executables')
        self.sp_run.add_argument('n', help='run benchmarks with up to 2^n tinyvectors per vector')

    def add_run_func(self, run_func):
        self.sp_run.set_defaults(func=run_func)

    def add_analyze_func(self, an_func):
        self.sp_analyze.set_defaults(func=an_func)

    #~ def add_clean_func(self, cl_func):
        #~ self.sp_clean.set_defaults(func=cl_func)

def runbm(args):
    '''get benchmark executables and run them
    '''
    bins = {i : [os.path.join(args.binpath, i)] for i in ops}
    #~ args = {i : ['bm_{}.dat'.format(i), 'res_{}.txt'.format(i), args.n] for i in ops}
    args = {i : ['bm_{}.dat'.format(i), args.n] for i in ops}

    for op in ops:
        call = bins[op] + args[op]
        print 'benchmarking {}'.format(op)
        run_out = sp.check_output(call)

    analyze(args)

def plot_runtime(x, y, op):
    '''create a runtime plot for the given operation's benchmark'''
    plt.figure()

    plt.plot(x, y[:, 0], label =  '2D simple', color = 'b', ls = '-')
    plt.plot(x, y[:, 1], label =  '3D simple', color = 'g', ls = '-')
    plt.plot(x, y[:, 2], label =  '4D simple', color = 'r', ls = '-')
    plt.plot(x, y[:, 4], label = '16D simple', color = 'c', ls = '-')
    
    plt.plot(x, y[:, 5], label =  '2D intrin', color = 'b', ls = '--')
    plt.plot(x, y[:, 6], label =  '4D intrin', color = 'g', ls = '--')
    plt.plot(x, y[:, 7], label =  '8D intrin', color = 'r', ls = '--')
    plt.plot(x, y[:, 9], label = '16D intrin', color = 'c', ls = '--')

    plt.xscale('log')
    plt.yscale('log')
    plt.legend(loc = 'best')
    fpl.xlabel('size')
    fpl.ylabel('# cycles')
    fpl.title(r'simple vs template unrolled vectorized \\ Release flags')
    plt.savefig('rt_'+op+'.pdf')

def plot_speedup(x, y, op):
    '''create a speedup plot for the given operation's benchmark'''
    s = y[:,0:5] / y[:,5:10]

    plt.figure()
    plt.plot(x, s[:,0], label = '2D')
    plt.plot(x, s[:,1], label = '3D')
    plt.plot(x, s[:,2], label = '4D')
    plt.plot(x, s[:,4], label = '16D')
    plt.hlines(1.0, 1e0, 1e6, colors = 'k', linestyles = '--')

    plt.xscale('log')
    plt.legend(loc = 'best')
    fpl.xlabel('size')
    fpl.ylabel('speedup')
    fpl.title(r'speedup template vec vs simple')
    plt.savefig('su_'+op+'.pdf')
 
def analyze(args):
    print 'plotting benchmarks'
    for op in ops:
        results = dio.read('bm_'+op+'.dat')
        x = results[:,0]
        y = results[:,1:]
        plot_runtime(x, y, op)
        plot_speedup(x, y, op)

def clean(args):
    pass

cli = commandline_interface()
cli.add_run_func(runbm)
cli.add_analyze_func(analyze)
#~ cli.add_clean_func(clean)

if __name__ == '__main__':
    args = cli.parser.parse_args()
    args.func(args)
