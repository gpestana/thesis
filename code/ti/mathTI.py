import sys
import utils
import numpy as np

filePath = sys.argv[1]
data = utils.parse(filePath)

nr_events = float(sys.argv[2])
time = float(sys.argv[3])

total_cpu = []

#add up a17 and a5
for i in range(0, len(data['a17'])):
    total_cpu.append(data['a5'][i]+data['a17'][i])    
 
mean_cpu = np.mean(total_cpu)
mean_mem = np.mean(data['mem'])
#print mean_cpu
#print mean_mem

#throughput:
throughput = nr_events/time

#thtoughtput per watt:
print 'cpu'
print throughput/mean_cpu

print 'mem'
print throughput/mean_mem
