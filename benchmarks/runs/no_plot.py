import matplotlib.pyplot as plt
from ethpy import datio as dio
from ethpy import fncplot as fpl
from matplotlib import rc
#~ rc('text', usetex=True)
import sys

runs = ['debug_no_i386', 'debug_no_native', 'rwd_no_i386', 'rwd_no_native', 'r_no_i386', 'r_no_native',
        'debug_ur_i386', 'debug_ur_native', 'rwd_ur_i386', 'rwd_ur_native', 'r_ur_i386', 'r_ur_native',
        'debug_uh_i386', 'debug_uh_native', 'rwd_uh_i386', 'rwd_uh_native', 'r_uh_i386', 'r_uh_native',
        'debug_uv_native', 'rwd_uv_native', 'r_uv_native'
       ]
result_files = [i+'.out.dat' for i in runs]

if len(sys.argv) > 1 and sys.argv[1] == 'run':
    import subprocess32 as sp
    from os import path
    for i in range(len(runs)):
        r = runs[i]

        if 'debug_' in r: pdir = '../build-d/'
        elif 'rwd_' in r: pdir = '../build-rwd/'
        elif 'r_'   in r: pdir = '../build-r/'

        if '_no_' in r: popt = 'no'
        elif '_ur_' in r: popt = 'ur'
        elif '_uh_' in r: popt = 'uh'
        elif '_uv_' in r: popt = 'uv'

        if 'i386' in r: pname = 'pb_{}_i386'.format(popt)
        elif 'native' in r: pname = 'pb_{}_native'.format(popt)

        with open(result_files[i], 'w') as resf:
            sp.call([path.join(pdir, pname)], stdout = resf)

results = {runs[i] : dio.read(result_files[i]) for i in range(len(runs))}

x = results['debug_no_i386'][:,0]

y_dbni_2 = results['debug_no_i386'][:,1]
y_dbni_4 = results['debug_no_i386'][:,2]
y_dbni_8 = results['debug_no_i386'][:,3]

y_dbnn_2 = results['debug_no_native'][:,1]
y_dbnn_4 = results['debug_no_native'][:,2]
y_dbnn_8 = results['debug_no_native'][:,3]

y_rwni_2 = results['rwd_no_i386'][:,1]
y_rwni_4 = results['rwd_no_i386'][:,2]
y_rwni_8 = results['rwd_no_i386'][:,3]
y_rwni_16 = results['rwd_no_i386'][:,4]
y_rwni_32 = results['rwd_no_i386'][:,5]

y_rwnn_2 = results['rwd_no_native'][:,1]
y_rwnn_4 = results['rwd_no_native'][:,2]
y_rwnn_8 = results['rwd_no_native'][:,3]  
y_rwnn_16 = results['rwd_no_native'][:,4]
y_rwnn_32 = results['rwd_no_native'][:,5]

y_rlni_2 = results['r_no_i386'][:,1]
y_rlni_4 = results['r_no_i386'][:,2]
y_rlni_8 = results['r_no_i386'][:,3]

y_rlnn_2 = results['r_no_native'][:,1]
y_rlnn_4 = results['r_no_native'][:,2]
y_rlnn_8 = results['r_no_native'][:,3]  

#----------------------- no optimizations 2-8 Dim, Debug -------------------------------
plt.figure()

plt.plot(x, y_dbni_2, label='2D - i386')
plt.plot(x, y_dbni_4, label='4D - i386')
plt.plot(x, y_dbni_8, label='8D - i386')

plt.plot(x, y_dbnn_2, label='2D - native')
plt.plot(x, y_dbnn_4, label='4D - native')
plt.plot(x, y_dbnn_8, label='8D - native')

plt.xscale('log')
plt.yscale('log')
plt.legend(loc = 'best')
fpl.xlabel('size')
fpl.ylabel('# cycles')
fpl.title('tinivec + with -O0 -g')
plt.savefig('dbni.pdf')
 
#----------------------- no optimizations 2-8 Dim, -O2 -------------------------------
plt.figure()

plt.plot(x, y_rwni_2, label='2D - i386 - O2')
plt.plot(x, y_rwni_4, label='4D - i386 - O2')
plt.plot(x, y_rwni_8, label='8D - i386 - O2')

plt.plot(x, y_rwnn_2, label='2D - native - O2')
plt.plot(x, y_rwnn_4, label='4D - native - O2')
plt.plot(x, y_rwnn_8, label='8D - native - O2')

plt.xscale('log')
plt.yscale('log')
plt.legend(loc = 'best')
fpl.xlabel('size')
fpl.ylabel('# cycles')
fpl.title('tinivec + with -O2 -g')
plt.savefig('rwni.pdf')
         
#----------------------- no optimizations 2-8 Dim, -O3 -------------------------------
plt.figure()

plt.plot(x, y_rlni_2, label='2D - i386 - O3')
plt.plot(x, y_rlni_4, label='4D - i386 - O3')
plt.plot(x, y_rlni_8, label='8D - i386 - O3')

plt.plot(x, y_rlnn_2, label='2D - native - O3')
plt.plot(x, y_rlnn_4, label='4D - native - O3')
plt.plot(x, y_rlnn_8, label='8D - native - O3')

plt.xscale('log')
plt.yscale('log')
plt.legend(loc = 'best')
fpl.xlabel('size')
fpl.ylabel('# cycles')
fpl.title('tinivec + with -O3')
plt.savefig('rlni.pdf')

#----------------------- no optimizations 8 Dim, -O [0, 2, 3] -------------------------------
plt.figure()

plt.plot(x, y_dbni_8, label='8D - i386')
plt.plot(x, y_dbnn_8, label='8D - native')
plt.plot(x, y_rwni_8, label='8D - i386 - O2')
plt.plot(x, y_rwnn_8, label='8D - native - O2')
plt.plot(x, y_rlni_8, label='8D - i386 - O3')
plt.plot(x, y_rlnn_8, label='8D - native - O3')

plt.xscale('log')
plt.yscale('log')
plt.legend(loc = 'best')
fpl.xlabel('size')
fpl.ylabel('# cycles')
fpl.title('tinivec + 8d different flags')
plt.savefig('8d.pdf')

#----------------------- no optimizations 16 and 32 Dim -------------------------------
plt.figure()
plt.plot(x, y_rwni_16, label='16D - i386 - O2')
plt.plot(x, y_rwnn_16, label='16D - native - O2')
plt.plot(x, y_rwni_32, label='32D - i386 - O2')
plt.plot(x, y_rwnn_32, label='32D - native - O2')

plt.xscale('log')
plt.yscale('log')
plt.legend(loc = 'best')
fpl.xlabel('size')
fpl.ylabel('# cycles')
fpl.title('tinivec + >8d -O2')
plt.savefig('arch.pdf')
 
#----------------------- optimization techniques -------------------------------
y_rlnn_16  = results['r_no_native'][:,4]
y_rlun_16  = results['r_ur_native'][:,4]
y_rlhn_16  = results['r_uh_native'][:,4]
y_rlvn_16  = results['r_uv_native'][:,4]

plt.figure()
plt.plot(x, y_rlnn_16, label = 'simple for loop')
plt.plot(x, y_rlun_16, label = 'template unroll')
plt.plot(x, y_rlhn_16, label = 'hand unroll')
plt.plot(x, y_rlvn_16, label = 'vectorized unroll')

plt.xscale('log')
plt.yscale('log')
plt.legend(loc = 'best')
fpl.xlabel('size')
fpl.ylabel('# cycles')
fpl.title(r'Comparison of loop unroll techniques \\ \texttt{-O3 -march=native}')
plt.savefig('opt.pdf')

#----------------------- hand vectorized vs simple -------------------------------

y_rlvn_2  = results['r_uv_native'][:,1]
y_rlvn_4  = results['r_uv_native'][:,2]
y_rlvn_8  = results['r_uv_native'][:,3]
y_rlvn_32 = results['r_uv_native'][:,5]
y_rlnn_32 = results['r_no_native'][:,5]

plt.figure()
plt.plot(x, y_rlnn_2,  label =  '2D simple', color = 'b', ls = '-') #color = ( 1, 0, 0))
plt.plot(x, y_rlnn_4,  label =  '4D simple', color = 'g', ls = '-') #color = (.9,.1, 0))
plt.plot(x, y_rlnn_8,  label =  '8D simple', color = 'r', ls = '-') #color = (.8,.2, 0))
plt.plot(x, y_rlnn_16, label = '16D simple', color = 'c', ls = '-') #color = (.7,.3, 0))
plt.plot(x, y_rlnn_32, label = '32D simple', color = 'm', ls = '-') #color = (.6,.4, 0))

plt.plot(x, y_rlvn_2,  label =  '2D vectorized', color = 'b', ls = '--') #color = ( 0, 0, 1))
plt.plot(x, y_rlvn_4,  label =  '4D vectorized', color = 'g', ls = '--') #color = ( 0,.1,.9))
plt.plot(x, y_rlvn_8,  label =  '8D vectorized', color = 'r', ls = '--') #color = ( 0,.2,.8))
plt.plot(x, y_rlvn_16, label = '16D vectorized', color = 'c', ls = '--') #color = ( 0,.3,.7))
plt.plot(x, y_rlvn_32, label = '32D vectorized', color = 'm', ls = '--') #color = ( 0,.4,.6))

plt.xscale('log')
plt.yscale('log')
plt.legend(loc = 'best')
fpl.xlabel('size')
fpl.ylabel('# cycles')
fpl.title(r'hand vectorized vs simple \\ Release flags')
plt.savefig('dim_opt.pdf')

#----------------------- speedup per size and dim -------------------------------
s = results['r_no_native'] / results['r_uv_native']

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
fpl.title(r'speedup vectorized vs simple')
plt.savefig('speedup.pdf')
 







