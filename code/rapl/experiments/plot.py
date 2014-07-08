import sys
import utils
import matplotlib.pyplot as plt
from pylab import *

filePath = sys.argv[1]
data = utils.parse(filePath)

YLIM = 100

for core in range(0, 32):
    PCK_NR = core/8
    x = range(0, len(data[core]['pck']))
    
    p = plt.subplot(2,2, PCK_NR+1)
    
    plt.title('socket #'+str(PCK_NR))
    pck_plot, = plt.plot(x, data[core]['pck'], color = 'blue')
    pp0_plot, = plt.plot(x, data[core]['pp0'], color='green')
    dram_plot, = plt.plot(x, data[core]['dram'], color='red')
    
    p.set_ylim([0, YLIM])
    


plt.figlegend((pck_plot, pp0_plot, dram_plot), ('package','power plan0','dram'), loc = 'upper center', ncol=5, labelspacing=0. )
plt.xlabel("time (s)")
plt.ylabel('power (w)')

fig = gcf()
fig.suptitle("note: all processores are represented. though, they overlap per package", fontsize=14, y=.05)
plt.show()
