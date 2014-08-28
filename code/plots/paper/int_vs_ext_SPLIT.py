import matplotlib.pyplot as plt 
import numpy as np
import math


N = 5
ind = np.arange(N)    # the x locations for the groups
width = 0.35       # the width of the bars: can also be len(x) sequence

#arm
arm_external = (.64, .54, .44, .54, .58)
arm_internal = (.36, .46, .56, .46, .42)
arm_mem = (.018,.01,.008,.01, .006)

p0 = plt.bar(ind, arm_mem, width, color='red')
p1 = plt.bar(ind, arm_internal,   width, color='green', bottom=arm_mem)
p2 = plt.bar(ind, arm_external, width, color='blue', bottom=arm_internal)

plt.xlabel('Nr threads/core')
plt.title('ARM ratio internal/external energy')
plt.xticks(ind+width/2., ('.25', '.5', '1', '2', '4') )
plt.yticks(np.arange(0,1,.1))
plt.legend( (p0[0], p1[0], p2[0]), ('memory', 'cpu', 'overall') )

plt.show()


#intel
intel_external = (.8, .77, .74, .74, .77)
intel_internal = (.2, .23, .24, .24, .23)
intel_mem = (.04,.0345,.0366,.0366, .0345)


p0 = plt.bar(ind, intel_mem, width, color='red')
p1 = plt.bar(ind, intel_internal,   width, color='green', bottom=intel_mem)
p2 = plt.bar(ind, intel_external, width, color='blue', bottom=intel_internal)

plt.xlabel('Nr threads/core')
plt.title('Intel ratio internal/external energy')
plt.xticks(ind+width/2., ('.25', '.5', '1', '2', '4') )
plt.yticks(np.arange(0,1,.1))
plt.legend( (p0[0], p1[0], p2[0]), ('memory', 'cpu', 'overall') )

plt.show()

