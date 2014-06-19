import sys
import glob
import matplotlib.pyplot as plt
import numpy as np

import math

VOLTS = 12
labels = ['1 process', '2 processes', '3 processes', '4 processes', '5 processes', '8 processes']


#parsing data
'''
for fileName in glob.glob(sys.argv[1]+'//*'):
	data = np.genfromtxt(fileName, delimiter="\n", dtype=float)
	print fileName.split('/')[-1]
	print ','.join(map(str,data))
	print ' '
'''

#1wire
atom = {
	'baseline': 11.6,
	'power': [[0.63,0.6,0.61,0.58,0.61,0.6,0.6,0.59,0.63,0.62,0.59,0.61,0.6,0.62,0.6,0.62,0.61,0.6,0.62,0.63,0.61,0.61,0.63,0.6,0.61,0.6,0.61,0.62,0.61,0.6,0.63,0.62,0.6,0.62,0.61],[0.6,0.65,0.65,0.65,0.66,0.65,0.65,0.66,0.66,0.67,0.67,0.67,0.66,0.66,0.65,0.66,0.67,0.67,0.66,0.68,0.68,0.69,0.68,0.68,0.68,0.69,0.68,0.67,0.67,0.67,0.67,0.69,0.68,0.7,0.69],[0.64,0.62,0.61,0.62,0.63,0.65,0.68,0.68,0.66,0.69,0.68,0.7,0.7,0.72,0.72,0.71,0.72,0.73,0.73,0.73,0.72,0.72,0.7,0.7,0.69,0.7,0.71,0.71,0.69,0.68,0.7,0.69,0.68,0.71,0.7,0.68,0.68,0.69,0.7,0.69,0.67,0.68,0.69,0.65],[0.62,0.69,0.7,0.67,0.67,0.7,0.71,0.7,0.7,0.7,0.71,0.72,0.69,0.7,0.69,0.7,0.69,0.69,0.72,0.7,0.71,0.71,0.72,0.7,0.71,0.71,0.72,0.72,0.71,0.73,0.74,0.72,0.72,0.71,0.71,0.71,0.72,0.72,0.71,0.7,0.73,0.72,0.71,0.73,0.72,0.72,0.73,0.72,0.7,0.71,0.72]],
	'time': [1043, 1063, 1345, 1647]
	}
#1wire
quad = {
	'baseline': 6.8,
	'power': [[0.95,0.92,0.87,0.8,0.82,0.82,0.84,0.82,0.9,0.94,0.96,0.96,0.94,0.96,0.97,0.97,0.97,0.97,0.98,1.0,0.97,1.0,1.03,0.95,0.99,1.0,0.98,0.99,0.99],[1.48,1.46,1.25,1.23,1.21,1.24,1.2,1.24,1.44,1.46,1.52,1.55,1.53,1.55,1.6,1.59,1.55,1.54,1.58,1.57,1.61,1.57,1.6,1.55,1.6,1.59,1.55,1.54,1.58,1.57,1.61,1.57,1.6,1.58,1.5,1.58,1.56,1.56,1.6,1.59],[1.97,1.58,1.66,1.66,1.68,1.67,1.62,1.51,1.78,1.84,1.86,1.86,1.87,1.87,1.86,1.86,1.86,1.85,1.86,1.86,1.8,1.88,1.87,1.85,1.89,1.85,1.87,1.9,1.87],[1.9,2.44,2.35,1.95,2.0,2.03,2.03,2.0,2.1,2.14,2.08,2.11,2.07,2.13,2.1,2.11,2.11,2.1,2.11,2.15,2.13,2.12,2.15,2.0,2.11,2.11,2.12,2.12,2.11,2.13,2.16,2.13],[0.95,2.38,2.23,1.92,1.97,1.98,1.97,1.99,2.03,2.03,2.23,2.1,2.07,2.09,2.09,2.12,2.12,2.08,2.1,2.13,2.05,2.08,2.08,2.1,2.1,2.13,2.1,2.09,2.11,2.11,2.1,2.09,2.09,2.1,2.08,2.11,2.11,2.1],[2.54,2.01,2.09,2.09,2.1,2.21,2.15,2.15,2.19,2.21,2.16,2.16,2.18,2.18,2.2,2.18,2.19,2.18,2.17,2.2,2.21]],
	'time': [290, 290, 297, 303, 356, 592]
	}
#all 4wires 
arm = {
	'baseline': 49.1,
	'power': [[4.18,4.20], [4.22, 4.23], [4.26, 4.26, 4.30, 4.30 ,4.29], [4.29, 4.35, 4.35], [4.36, 4.33, 4.36, 4.36], [4.30, 4.26, 4.32, 4.36, 4.37, 4.36, 4.38]],
	'time': [575, 593, 595, 607, 764, 1253]
	}


#step = time/(len(power)-1)
#x = np.arange(start=0, stop=time+1, step=step)


#ATOM
for i, time in enumerate(atom['time']):
	#2wires
	atom['power'][i] = [q * 2 for q in atom['power'][i]]
	step = float(atom['time'][i])/(len(atom['power'][i])-1)
	x = np.arange(start=0, stop=atom['time'][i]+1, step=step)
	y = [p * VOLTS-atom['baseline'] for p in atom['power'][i]]

	totalW = np.trapz(y, x=x)
	print '[atom] '+labels[i]+': '+str(totalW)+' total Watts consumed'
	plot, = plt.plot(x, y, '-', label=labels[i])



plt.legend(loc=4)
plt.title('ATOM - Power consumption measured during Event\'s processing (clamp)')
plt.xlabel('Time (s)')
plt.ylabel('Power CMSSW consumed (W)')
plt.show()
print ' '


#QUAD
for i, time in enumerate(quad['time']):
	#2wires
	quad['power'][i] = [q * 2 for q in quad['power'][i]]
	step = float(quad['time'][i])/(len(quad['power'][i])-1)
	x = np.arange(start=0, stop=quad['time'][i]+1, step=step)
	y = [p * VOLTS-quad['baseline'] for p in quad['power'][i]]

	totalW = np.trapz(y, x=x)
	print '[quad] '+labels[i]+': '+str(totalW)+' total Watts consumed'

	plot, = plt.plot(x, y, '-', label=labels[i])

plt.legend(loc=4)
plt.title('QUAD - Power consumption measured during Event\'s processing (clamp)')
plt.xlabel('Time (s)')
plt.ylabel('Power CMSSW consumed (W)')
plt.show()
print ' '

#ARM
for i, time in enumerate(arm['time']):
	#2wires -> all wires in measurements
	step = float(arm['time'][i])/(len(arm['power'][i])-1)
	x = np.arange(start=0, stop=arm['time'][i]+1, step=step)
	y = [p * VOLTS-arm['baseline'] for p in arm['power'][i]]
	
	totalW = np.trapz(y, x=x)
	print '[ARM] '+labels[i]+': '+str(totalW)+' total Watts consumed'

	plot, = plt.plot(x, y, '-', label=labels[i])

plt.legend(loc=4)
plt.title('ARM - Power consumption measured during Event\'s processing (clamp)')
plt.xlabel('Time (s)')
plt.ylabel('Power CMSSW consumed (W)')
plt.show()