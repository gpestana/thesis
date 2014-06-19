## DATA

# A. ps
# - TRS 
# - DRS   
# - RSS Resident set size
# - %MEM

# B. top
# - VIRT The total amount of virtual memory used by the task. It includes all code, data and shared libraries plus pages that have been swapped out.   
# - RES The non-swapped physical memory a task has used | RES = CODE + DATA
# - SHR The amount of shared memory used by a task. It simply reflects memory that could be potentially shared with other processes. 
# - %CPU  
# - %MEM tasks share of available physical memory


# parse the data
# 1. trim the data (grep in python)
# 	1.2. parse the data from lines
# 2. generate plts

import re
import sys
import matplotlib.pyplot as plt
import numpy as np
from matplotlib.font_manager import FontProperties


# usage: python memory.py file.out 

kb_to_GB = 1048576
kb_to_MB = 1024
data = {}
file = open(sys.argv[1], "r")


# data structure
# procNr -> VIRT, RES, SHR, %CPU, %MEM
#
for line in file:
       if re.search('cmsRun', line):
             dataLine = line.split()
             if not dataLine[0] in data.keys():
             	data[dataLine[0]] = {'VIRT': [], 'RES': [], 'SHR': [], 'CPU': [], 'MEM': []}
             else:
             	data[dataLine[0]]['VIRT'].append(dataLine[4])
             	data[dataLine[0]]['RES'].append(dataLine[5])
             	data[dataLine[0]]['SHR'].append(dataLine[6])
             	data[dataLine[0]]['CPU'].append(dataLine[8])
             	data[dataLine[0]]['MEM'].append(dataLine[9])

size = len(data[data.keys()[0]]['VIRT'])

#add up data
VIRT = [0] * size
RES = [0] * size
SHR = [0] * size
CPU = [0] * size
MEM = [0] * size

for dkey in data.keys():
      for i, v in enumerate(data[dkey]['VIRT']):
            if(i<len(VIRT)):
                  VIRT[i] = VIRT[i] + float(v.replace('m','000'))/kb_to_GB
      for i, v in enumerate(data[dkey]['RES']):
            if(i<len(RES)):
                  RES[i] = RES[i] + float(v.replace('m','000'))/kb_to_GB
      for i, v in enumerate(data[dkey]['SHR']):
            if(i<len(SHR)):
                  SHR[i] = SHR[i] + float(v.replace('m','000'))/kb_to_GB
      for i, v in enumerate(data[dkey]['CPU']):
            if(i<len(CPU)):
                  CPU[i] = CPU[i] + float(v.replace('m','000')) 
      for i, v in enumerate(data[dkey]['MEM']):
            if(i<len(MEM)):
                  MEM[i] = MEM[i] + float(v.replace('m','000')) 

#plot VIRT, RES, SHR & CPU, MEM
fontP = FontProperties()
fontP.set_size('small')
x = np.array(range(size))
labels = []

plot, = plt.plot(x, VIRT, '-', label='virtual mem')
plot, = plt.plot(x, RES, '-', label='non-swapped mem (code + data)')
plot, = plt.plot(x, SHR, '-', label='shared mem')
labels.append(plot)
plt.legend(bbox_to_anchor=(0., 1.02, 1., .102), loc=3,
       ncol=5, mode="expand", borderaxespad=0.)
#plt.title(sys.argv[1])
plt.ylabel('GB')
plt.xlabel('Samplings')
plt.show()

plot1, = plt.plot(x, MEM, '-', label='%mem')
plot2, = plt.plot(x, CPU, '-', label='%cpu')                
#plt.xticks(np.arange(min(x), max(x)+1, 25.0))
labels.append(plot)
plt.legend(bbox_to_anchor=(0., 1.02, 1., .102), loc=3,
       ncol=2, mode="expand", borderaxespad=0.)
#plt.title(name)
plt.ylabel('%')
plt.xlabel('Samplings')
plt.show()