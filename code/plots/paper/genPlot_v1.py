import matplotlib.pyplot as plt
import numpy as np
import math

#arm_int = [0.112404591764, 0.129612767235, 0.168527884675, 0.117256787998, 0.108744373625]
arm_int = [0.112404591764, 0.129612767235, 0.168527884675, 0.117256787998]
#intel_int = [0.0705764433275, 0.100796803707, 0.10419274711, 0.102585549942, 0.0975209520741]
intel_int = [0.0705764433275, 0.100796803707, 0.10419274711, 0.102585549942]
#arm_ext = [0.0404608654417, 0.0597864857193, 0.0627435547938, 0.0512965616325, 0.0596317003073]
arm_ext = [0.0404608654417, 0.0597864857193, 0.0627435547938, 0.0512965616325]
#intel_ext = [.0145, .0236, .0248, .0244, .0236]
intel_ext = [.0145, .0236, .0248, .0244]

#aalto_
aalto_int = [.0146, 0.0149, 0.050, 0.046]

labels = ['1/4','1/2','1','2']

x = [.25, .5, 1, 2]

#internal average
plt.scatter(x, arm_int, color='blue', edgecolor='none', s=75, label='ARM_odroid')
plt.scatter(x, intel_int, color='red', edgecolor='none', s=75, label='Intel_xeon')

#aalto_
plt.scatter(x, aalto_int, color='green', edgecolor='none', s=75, label='ARM_viridis')

plt.xticks((0, .25, .5, 1, 2))
plt.legend(loc=1)
#plt.title('Onchip measurements - throughput per watts(avg)')
#plt.xlabel('Nr threads/core')
#plt.ylabel('events/s/W')

plt.show()

#external average

plt.scatter(x, arm_ext, color='blue', edgecolor='none', s=75, label='arm')
plt.scatter(x, intel_ext, color='red', edgecolor='none', s=75, label='intel')

plt.xticks((0, 0.25, 0.5, 1, 2))

plt.legend(loc=1)
#plt.title('External measurements - throughput per watts(avg)')
#plt.xlabel('Nr threads/core')
#plt.ylabel('events/s/W')

plt.show()
