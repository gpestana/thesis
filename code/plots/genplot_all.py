import os, sys, time
import matplotlib.pyplot as plt
import numpy as np
from matplotlib.font_manager import FontProperties
import glob

VOLTS = 12
inputs = []
name = sys.argv[1]

def gen(name):

	for fileName in glob.glob('*.out'):
		input = {}
		data = np.genfromtxt(fileName, delimiter="\n", dtype=float)
		input['name'] = fileName
		input['data'] = data 
		inputs.append(input)
		print 'added '+fileName

	print 'gerenating plot..'

	fontP = FontProperties()
	fontP.set_size('small')

	labels=[]

	for i, input in enumerate(inputs):
		d = input['data']
		x = np.array(range(len(d)))
		plot, = plt.plot(x, d*VOLTS, 'o-', label=input['name'])
		labels.append(plot)

	plt.legend(loc=2)
	plt.title(name)
	plt.ylabel('Watts')
	plt.xlabel('Samplings')
	plt.show('test'+'.png')

