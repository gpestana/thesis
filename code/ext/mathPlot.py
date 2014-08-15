import sys
import numpy as np

#python <output_file> <arm or intel> <nr_events>

file = open(sys.argv[1])
nr_events = float(sys.argv[3])

samplings = []

#time == nr_lines
#W is 3rd colum, remove final W
if(sys.argv[2] == 'arm'):
    print 'arm:'
    time = 0
    for line in file:
        time = time+1
        dataArr = line.split()
        samplings.append(float(dataArr[2][:-1]))

        mean = np.mean(samplings)
        
else:
    print 'intel'
    for line in file:
        print line


sum_power = np.sum(samplings)
throughput = nr_events/time


print str(time)+'s'
print str(sum_power) + ' W'
print str(mean) +' W'
print str(throughput/mean)+' ev/s/W'

