import matplotlib
matplotlib.use('pdf')
import matplotlib.pyplot as plt
from ethpy import datio as dio
from ethpy import fncplot as fpl
#~ from matplotlib import rc
#~ rc('text', usetex=True)
import sys

op = sys.argv[1]
results = dio.read('bm_'+op+'.dat')

x = results[:,0]

y = results[:,1:]

#----------------------- simple vs template vectorized -------------------------------

def plot_data():
    plt.plot(x, y[:, 0], label =  '2D simple', color = 'b', ls = '-')
    plt.plot(x, y[:, 1], label =  '3D simple', color = 'g', ls = '-')
    plt.plot(x, y[:, 2], label =  '4D simple', color = 'r', ls = '-')
    plt.plot(x, y[:, 4], label = '16D simple', color = 'c', ls = '-')
    
    plt.plot(x, y[:, 5], label =  '2D intrin', color = 'b', ls = '--')
    plt.plot(x, y[:, 6], label =  '4D intrin', color = 'g', ls = '--')
    plt.plot(x, y[:, 7], label =  '8D intrin', color = 'r', ls = '--')
    plt.plot(x, y[:, 9], label = '16D intrin', color = 'c', ls = '--')

plt.figure()
plot_data()

plt.xscale('log')
plt.yscale('log')
plt.legend(loc = 'best')
fpl.xlabel('size')
fpl.ylabel('# cycles')
fpl.title(r'simple vs template unrolled vectorized \\ Release flags')
plt.savefig('rt_'+op+'.pdf')

#----------------------- speedup simple v tv per size and dim -------------------------------
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
 
