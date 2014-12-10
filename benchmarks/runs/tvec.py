import matplotlib.pyplot as plt
from ethpy import datio as dio
from ethpy import fncplot as fpl
from matplotlib import rc
#~ rc('text', usetex=True)
import sys
import subprocess32 as sp

runs = ['debug_uv_native', 'rwd_uv_native', 'r_uv_native',
        'debug_tv_native', 'rwd_tv_native', 'r_tv_native',
        'debug_no_native', 'rwd_no_native', 'r_no_native'
       ]
result_files = [i+'.out.dat' for i in runs]

if 'make' in sys.argv:
    bdir = ['../build-d/', '../build-rwd/', '../build-r/']
    for i in range(len(bdir)):
        sp.check_call(['make', '-C', bdir[i], 'rebuild_cache'])
        sp.check_call(['make', '-C', bdir[i], 'pb_uv_native', 'pb_tv_native', 'pb_no_native'])
    print 'build phase ended'

if 'run' in sys.argv:
    from os import path
    for i in range(len(runs)):
        r = runs[i]
        print 'running ' + r

        if 'debug_' in r: pdir = '../build-d/'
        elif 'rwd_' in r: pdir = '../build-rwd/'
        elif 'r_'   in r: pdir = '../build-r/'

        if '_uv_' in r: popt = 'uv'
        elif '_tv_' in r: popt = 'tv'
        elif '_no_' in r: popt = 'no'
        else: raise Exception('no suitable program found')

        if 'i386' in r: pname = 'pb_{}_i386'.format(popt)
        elif 'native' in r: pname = 'pb_{}_native'.format(popt)

        with open(result_files[i], 'w') as resf:
            sp.check_call([path.join(pdir, pname)], stdout = resf)
    print 'run phase ended'

results = {runs[i] : dio.read(result_files[i]) for i in range(len(runs))}

x = results[runs[0]][:,0]

yn = results['r_no_native'][:,1:]
yh = results['r_uv_native'][:,1:]
yt = results['r_tv_native'][:,1:]

#----------------------- simple vs template vectorized -------------------------------

plt.figure()
plt.plot(x, yn[:, 0], label =  '2D simple', color = 'b', ls = '-')
plt.plot(x, yn[:, 1], label =  '4D simple', color = 'g', ls = '-')
plt.plot(x, yn[:, 2], label =  '8D simple', color = 'r', ls = '-')
plt.plot(x, yn[:, 3], label = '16D simple', color = 'c', ls = '-')
plt.plot(x, yn[:, 4], label = '32D simple', color = 'm', ls = '-')

plt.plot(x, yt[:, 0], label =  '2D template', color = 'b', ls = '--')
plt.plot(x, yt[:, 1], label =  '4D template', color = 'g', ls = '--')
plt.plot(x, yt[:, 2], label =  '8D template', color = 'r', ls = '--')
plt.plot(x, yt[:, 3], label = '16D template', color = 'c', ls = '--')
plt.plot(x, yt[:, 4], label = '32D template', color = 'm', ls = '--')

plt.xscale('log')
plt.yscale('log')
plt.legend(loc = 'best')
fpl.xlabel('size')
fpl.ylabel('# cycles')
fpl.title(r'simple vs template unrolled vectorized - Release flags')
plt.savefig('svt_runtime.pdf')
 
#----------------------- hand vectorized vs template vectorized -------------------------------

plt.figure()
plt.plot(x, yh[:, 0], label =  '2D hand', color = 'b', ls = '-')
plt.plot(x, yh[:, 1], label =  '4D hand', color = 'g', ls = '-')
plt.plot(x, yh[:, 2], label =  '8D hand', color = 'r', ls = '-')
plt.plot(x, yh[:, 3], label = '16D hand', color = 'c', ls = '-')
plt.plot(x, yh[:, 4], label = '32D hand', color = 'm', ls = '-')

plt.plot(x, yt[:, 0], label =  '2D template', color = 'b', ls = '--')
plt.plot(x, yt[:, 1], label =  '4D template', color = 'g', ls = '--')
plt.plot(x, yt[:, 2], label =  '8D template', color = 'r', ls = '--')
plt.plot(x, yt[:, 3], label = '16D template', color = 'c', ls = '--')
plt.plot(x, yt[:, 4], label = '32D template', color = 'm', ls = '--')

plt.xscale('log')
plt.yscale('log')
plt.legend(loc = 'best')
fpl.xlabel('size')
fpl.ylabel('# cycles')
fpl.title(r'hand unrolled vectorized vs template unrolled vectorized - Release flags')
plt.savefig('hvt_runtime.pdf')

#----------------------- speedup simple v tv per size and dim -------------------------------
s = results['r_no_native'] / results['r_tv_native']

plt.figure()
plt.plot(x, s[:,1], label = '2D')
plt.plot(x, s[:,2], label = '4D')
plt.plot(x, s[:,3], label = '8D')
plt.plot(x, s[:,4], label = '16D')
plt.plot(x, s[:,5], label = '32D')
plt.hlines(1.0, 1e1, 1e5, colors = 'k', linestyles = '--')

plt.xscale('log')
plt.legend(loc = 'best')
fpl.xlabel('size')
fpl.ylabel('speedup')
fpl.title(r'speedup template vec vs simple')
plt.savefig('svt_speedup.pdf')
 

#----------------------- speedup per size and dim -------------------------------
s = results['r_uv_native'] / results['r_tv_native']

plt.figure()
plt.plot(x, s[:,1], label = '2D')
plt.plot(x, s[:,2], label = '4D')
plt.plot(x, s[:,3], label = '8D')
plt.plot(x, s[:,4], label = '16D')
plt.plot(x, s[:,5], label = '32D')
plt.hlines(1.0, 1e1, 1e5, colors = 'k', linestyles = '--')

plt.xscale('log')
plt.legend(loc = 'best')
fpl.xlabel('size')
fpl.ylabel('speedup')
fpl.title(r'speedup template vs hand (should be 1)')
plt.savefig('hvt_speedup.pdf')
 







