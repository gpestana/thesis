import sys
import utils
import matplotlib.pyplot as plt

filePath = sys.argv[1]

data = utils.parse(filePath)
labels = []
title = ''

#options
PCK_NR = int(float(sys.argv[2])) 
PCK = 1
PP0 = 1
DRAM = 1 

for core in range(0, 32):
    if(core/8 == PCK_NR):
        if(PCK):
            x = range(0, len(data[core]['pck']))
            plot, = plt.plot(x, data[core]['pck'], color = 'blue')
    
        if(PP0):
            x = range(0, len(data[core]['pp0']))
            plot, = plt.plot(x, data[core]['pp0'], color='green')

        if(DRAM):
            x = range(0, len(data[core]['dram']))
            plot, = plt.plot(x, data[core]['dram'], color='red')
            plt.title('dram')

#labels.append(plot)
#plt.legend(bbox_to_anchor=(0., 1.02, 1., .102), loc=3,
#       ncol=5, mode="expand", borderaxespad=0.)

plt.title('package nr #'+str(PCK_NR)+' - [blue]pck_'+str(PCK)+' [green]pp0_'+str(PP0)+' [red]dram_'+str(DRAM))
plt.ylabel('E(J) and P(w)')
plt.xlabel('T(s)')
plt.show()
