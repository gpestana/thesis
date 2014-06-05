import os, sys, time
import matplotlib.pyplot as plt
import numpy as np
from matplotlib.font_manager import FontProperties
import glob
import re
from scipy import integrate

VOLTS = 12
inputs = []
name = sys.argv[2]

if name == 'arm':
	mult = 1
	baseline = 49.1
elif name == 'atom':
	mult = 2
	baseline = 11.4
elif name == 'quad':
	mult = 2
	baseline = 6.8
else:
	print 'invalid arch'
	exit(0)

#parsing data
for fileName in glob.glob(sys.argv[1]+'//*'):
	input = {}
	data = np.genfromtxt(fileName, delimiter="\n", dtype=float)
	input['name'] = fileName.split('/')[-1]
	input['data'] = data 
	inputs.append(input)
	print 'added '+fileName

fontP = FontProperties()
fontP.set_size('small')

labels=[]

for i, input in enumerate(inputs):
	d = input['data']
	x = np.array(range(len(d)))
	v = d*VOLTS*mult-baseline
	input['name'] = input['name']+' '+str(integrate.simps(v))
	plot, = plt.plot(x, v, '-', label=input['name'])
	
	labels.append(plot)

plt.legend(loc=4)
plt.title(name)
plt.ylabel('Watts')
plt.xlabel('Samplings')
plt.show('test'+'.png')

