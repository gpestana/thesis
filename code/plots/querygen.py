import os, sys, re
import genplot_all as plot

matchStr = 'Sensor Reading        : '


#GEN:  querygen.py gen rawDataFileName
#PLOT: querygen.py plot name

allMatches = []

#generate data
if(sys.argv[1] == 'gen'):
	script_dir = os.path.dirname(__file__)
	filePath = os.path.join(script_dir, sys.argv[2])
	f = open(filePath,'r')
	lines = f.readlines()
	f.close()

	for line in lines:
	    if matchStr in line:
	    	res = re.findall(r"[-+]?\d*\.\d+|\d+", line)
	        allMatches.append(res[0])

	for node in allMatches[0::8]:
		print node

#plotting
if (sys.argv[1] == 'plot'):
	plot.gen(sys.argv[2])