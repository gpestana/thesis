import sys 
import utils
import numpy as np

filePath = sys.argv[1]
data = utils.parse(filePath)

pck_avg = 0
pp0_avg = 0
dram_avg = 0

for core in range(0,32):
  PCK_NR = core/8
  
  pck_avg = pck_avg + np.mean([float(i) for i in data[core]['pck']])
  pp0_avg = pp0_avg + np.mean([float(i) for i in data[core]['pp0']])
  dram_avg = dram_avg + np.mean([float(i) for i in data[core]['dram']])

print pck_avg/32
print pp0_avg/32
print dram_avg/32

