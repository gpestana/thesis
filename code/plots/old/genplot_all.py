import os, sys, time
import matplotlib.pyplot as plt
import numpy as np
from matplotlib.font_manager import FontProperties
import glob
import re
from scipy import integrate
import numpy

labels=[]
VOLTS = 12
inputs = []
name = sys.argv[2]

#parsing data
for fileName in glob.glob(sys.argv[1]+'//*'):
	input = {}
	data = np.genfromtxt(fileName, delimiter="\n", dtype=float)
	input['name'] = fileName.split('/')[-1]
	input['data'] = data 
	inputs.append(input)
	print 'added '+fileName

#generate plot
for i, input in enumerate(inputs):
	d = input['data']
	
	#remove!
	x = np.array(range(len(d)))
	
	#ATOM
	if name == 'atom':
		mult = 2
		baseline = 11.4 if sys.argv[3]=='-cmssw' else 0
		x = np.array(range(len(d)))*45
		plt.xlabel('Time (s)')
		if input['name'] == '8 processes':
			#59 samplings, each 90s
			x = np.array(range(len(d)))*90



	#QUAD
	if name == 'quad':
		mult = 2
		baseline = 6.8 if sys.argv[3]=='-cmssw' else 0
		x = np.array(range(len(d)))*10
		plt.xlabel('Time (s)')
		if input['name'] == '8 processes':
			#27 samplings, each 30s
			x = np.array(range(len(d)))*30
		

	#ARM
	if name == 'arm':
		mult = 1
		baseline = 49.1 if sys.argv[3]=='-cmssw' else 0
		x = np.array(range(len(d)))*5*60
		plt.xlabel('Time (s)')
		if input['name'] == '8 processes':
			#1cpu- 10 samplings, each 10m
			x = np.array(range(len(d)))*10*60


	v = d*VOLTS*mult-baseline
	plot, = plt.plot(x, v, '-', label=input['name'])
	labels.append(plot)

	#integration
	print integrate.simps(d)


fontP = FontProperties()
fontP.set_size('small')
plt.legend(loc=4)
plt.title(name)
plt.ylabel('Watts')
plt.show('test'+'.png')

