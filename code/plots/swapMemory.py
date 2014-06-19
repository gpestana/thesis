import re
import sys
import matplotlib.pyplot as plt
import numpy as np
from matplotlib.font_manager import FontProperties

# usage: python memory.py file.out -<arch>

kb_to_GB = 1048576
kb_to_MB = 1024
data = {}
file = open(sys.argv[1], "r")

allMem = []
allSwap = []
allBuff = []
allCache = []

for line in file:
       if re.search('Mem', line):
              if sys.argv[2] == '-arm':
                     allMem.append(int(line.split()[4].replace('k',''))/kb_to_MB)
                     allBuff.append(int(line.split()[8].replace('k',''))/kb_to_MB)
              else:
                     allMem.append(int(line.split()[3].replace('k',''))/kb_to_MB)
                     allBuff.append(int(line.split()[7].replace('k',''))/kb_to_MB)
       
       if re.search('Swap', line):
       	if sys.argv[2] == '-arm':
                     allSwap.append(int(line.split()[4].replace('k',''))/kb_to_MB)
                     allCache.append(int(line.split()[8].replace('k',''))/kb_to_MB)
       	else:
                     allSwap.append(int(line.split()[3].replace('k',''))/kb_to_MB)
                     allCache.append(int(line.split()[7].replace('k',''))/kb_to_MB)

#plot
fontP = FontProperties()
fontP.set_size('small')
x = np.array(range(len(allSwap)))
labels = []

plot, = plt.plot(x, allSwap, '-', label='swap mem')
plot, = plt.plot(x, allMem, '-', label='mem')
plot, = plt.plot(x, allBuff, '-', label='buffered mem')
plot, = plt.plot(x, allCache, '-', label='cached mem')

labels.append(plot)
plt.legend(bbox_to_anchor=(0., 1.02, 1., .102), loc=3,
       ncol=5, mode="expand", borderaxespad=0.)

#plt.title(sys.argv[1])
plt.ylabel('MB')
plt.xlabel('Samplings')
plt.show()