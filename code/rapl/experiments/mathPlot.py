import sys
import utils
import numpy as np

filePath = sys.argv[1]
data = utils.parse(filePath)


nr_events = float(sys.argv[2])
time = len(data[0]['pck'])
#time = float(sys.argv[3])

pp0_total = []
pck_total = []
dram_total = []

all = []

cpu_nr = 0
for cpu in data:
    #remove weird negatives
    pck = np.array(map(float, data[cpu_nr]['pck']))
    for i, val in enumerate(pck):
        if val < 0:
            pck[i] = last_val 
        last_val = pck[i]

    pp0 = np.array(map(float, data[cpu_nr]['pp0']))
    for i, val in enumerate(pp0):
        if val < 0:
            pp0[i] = last_val 
        last_val = pp0[i]


    dram = np.array(map(float, data[cpu_nr]['dram']))
    for i, val in enumerate(dram):
        if val < 0:
            dram[i] = last_val 
        last_val = dram[i]


    pck_total.append(np.mean(pck))
    pp0_total.append(np.mean(pp0))
    dram_total.append(np.mean(dram))
   
    #is this?? 
    all.append(np.mean(pck)+np.mean(dram)+np.mean(pp0))

    cpu_nr=cpu_nr+1

print 'time:' + str(time)

#whole mean:
mean_pck = np.mean(pck_total)
mean_pp0 = np.mean(pp0_total)
mean_dram =  np.mean(dram_total) 
print mean_pck
print mean_pp0
print mean_dram

#throughput:
throughput = nr_events/time

#throughput per watt:
print 'pck'
print throughput/mean_pck 

print 'pp0'
print throughput/mean_pp0

print 'dram'
print throughput/mean_dram

print 'all'
print throughput/np.mean(all)

print 'sum all'
print np.sum(all)
