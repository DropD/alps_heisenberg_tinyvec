import matplotlib
matplotlib.use('pdf')
import matplotlib.pyplot as plt
import numpy as np
from ethpy import datio as dio
from ethpy import fncplot as fpl
#~ from matplotlib import rc
#~ rc('text', usetex=True)
import sys

ops = sys.argv[1:]
for op in ops:
    results = dio.read('bm_'+op+'.dat')

    opname = {'divide' : 'Division',
              'multiply' : 'Multiplication',
              'plus' : 'Addition',
              'minus' : 'Subtraction'}

    x = results[:,0]

    y = results[:,1:]

#----------------------- simple vs template vectorized -------------------------------

    def plot_data():
        plt.plot(x, y[:, 0], label =  '2D default', color = 'b', ls = '-')
        plt.plot(x, y[:, 1], label =  '3D default', color = 'g', ls = '-')
        plt.plot(x, y[:, 2], label =  '4D default', color = 'r', ls = '-')
        plt.plot(x, y[:, 4], label = '16D default', color = 'c', ls = '-')
        
        plt.plot(x, y[:, 5], label =  '2D optimized', color = 'b', ls = '--')
        plt.plot(x, y[:, 6], label =  '4D optimized', color = 'g', ls = '--')
        plt.plot(x, y[:, 7], label =  '8D optimized', color = 'r', ls = '--')
        plt.plot(x, y[:, 9], label = '16D optimized', color = 'c', ls = '--')

    plt.figure()
    plot_data()

    plt.xscale('log')
    plt.yscale('log')
    plt.legend(loc = 'best')
    fpl.xlabel('size')
    fpl.ylabel('# cycles')
    fpl.title(r'{} Operator - Runtime'.format(opname[op]))
    plt.savefig('rt_'+op+'.pdf')

#----------------------- speedup simple v tv per size and dim -------------------------------
    s = y[:,0:5] / y[:,5:10]

    plt.figure()
    plt.plot(x, s[:,0], label = '2D')
    plt.plot(x, s[:,1], label = '3D')
    plt.plot(x, s[:,2], label = '4D')
    plt.plot(x, s[:,4], label = '16D')
    xmin, xmax = plt.xlim()
    plt.hlines(1.0, xmin, 10**np.ceil(np.log10(xmax)), colors = 'k', linestyles = '--')

    plt.xscale('log')
    plt.legend(loc = 'best')
    fpl.xlabel('# of tinyvectors')
    fpl.ylabel('speedup')
    fpl.title(r'{} Operator - Speedup'.format(opname[op]))
    plt.savefig('su_'+op+'.pdf')
     
