import sys
import matplotlib.pyplot as plt
import numpy as np

VOLTS = 12

#genplot.py input 'name' sampleTime time
inputFile = sys.argv[1]
nameExp = sys.argv[2]
sampleTime = sys.argv[3]
time = sys.argv[4]


data = np.genfromtxt(inputFile, delimiter="\n", dtype=float)
x = np.array(range(len(data)))

plt.title(nameExp)
plt.plot(x, data*VOLTS, 'bo-')
plt.ylabel('Watts')
plt.xlabel('Samplings: each '+sampleTime+' for '+time+'m')
plt.savefig(nameExp+'.png')

print "Done."