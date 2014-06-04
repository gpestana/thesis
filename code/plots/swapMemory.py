import re
import sys
import matplotlib.pyplot as plt
import numpy as np
from matplotlib.font_manager import FontProperties

# usage: python memory.py file.out 

data = {}
file = open(sys.argv[1], "r")

allMem = []
allSwap = []
for line in file:
       if re.search('Mem', line):
       		if sys.argv[2] == '-arm':
       			allMem.append(line.split()[4].replace('k',''))
       		else:
       			allMem.append(line.split()[3].replace('k',''))
       if re.search('Swap', line):
       		if sys.argv[2] == '-arm':
       			allSwap.append(line.split()[4].replace('k',''))
       		else:
       			allSwap.append(line.split()[3].replace('k',''))


print len(allSwap)
print len(allMem)

#plot
fontP = FontProperties()
fontP.set_size('small')
x = np.array(range(len(allSwap)))
labels = []

plot, = plt.plot(x, allSwap, '-', label='swap mem used')
plot, = plt.plot(x, allMem, '-', label='mem used')
labels.append(plot)
plt.legend(loc=4)

plt.title(sys.argv[1])
plt.ylabel('kb')
plt.xlabel('Samplings')
plt.show()