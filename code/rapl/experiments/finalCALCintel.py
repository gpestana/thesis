import sys
import utils
import numpy as np

filePath = sys.argv[1]
data = utils.parse(filePath)


nr_events = float(sys.argv[2])
time = len(data[0]['pck'])

pp0_total = []
pck_total = []
dram_total = []


cpu_nr = 0
for cpu in data:
    #remove weird negatives
    pck = np.array(map(float, data[cpu_nr]['pck']))
    for i, val in enumerate(pck):
        if val < 0:
            pck[i] = last_val
        else:
          last_val = pck[i]
          #print val

    pp0 = np.array(map(float, data[cpu_nr]['pp0']))
    for i, val in enumerate(pp0):
        if val < 0:
            pp0[i] = last_val
        else:
          last_val = pp0[i]


    dram = np.array(map(float, data[cpu_nr]['dram']))
    for i, val in enumerate(dram):
        if val < 0:
            dram[i] = last_val
        else:
          last_val = dram[i]

  
    

    pck_total.append(np.mean(pck))
    pp0_total.append(np.mean(pp0))
    dram_total.append(np.mean(dram))

    cpu_nr=cpu_nr+1

print len(pck)
print len(pp0)
print len(dram)

#whole mean:
mean_pck = np.mean(pck_total)
mean_pp0 = np.mean(pp0_total)
mean_dram =  np.mean(dram_total)
print 'mean pck: '+str(mean_pck)
print 'mean pp0: ' +str(mean_pp0)
print 'mean dram: ' +str(mean_dram)

#throughput:
throughput = nr_events/time

#throughput per watt:
print 'throughput per watt pck'
print throughput/mean_pck

print 'throughput per watt pp0'
print throughput/mean_pp0

print 'throughput per watt ram'
print throughput/mean_dram
