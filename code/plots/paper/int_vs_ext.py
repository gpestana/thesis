import matplotlib.pyplot as plt 
import numpy as np
import math


N = 4
ind = np.arange(N)    # the x locations for the groups
width = 0.35       # the width of the bars: can also be len(x) sequence

#arm
arm_external = (.64, .54, .44, .54)
arm_internal = (.36, .46, .56, .46)

p1 = plt.bar(ind, arm_internal,   width, color='red')
p2 = plt.bar(ind, arm_external, width, color='blue', bottom=arm_internal)

#plt.xlabel('Nr threads/core')
#plt.title('ARM ratio internal/external energy')
plt.xticks(ind+width/2., ('.25', '.5', '1', '2') )
plt.yticks(np.arange(0,1,.1))
plt.legend( (p1[0], p2[0]), ('cpu+memory', 'overall') )

plt.show()


#intel
intel_external = (.8, .77, .74, .74)
intel_internal = (.2, .23, .26, .24)

p1 = plt.bar(ind, intel_internal,   width, color='red')
p2 = plt.bar(ind, intel_external, width, color='blue', bottom=intel_internal)

#plt.xlabel('Nr threads/core')
#plt.title('Intel ratio internal/external energy')
plt.xticks(ind+width/2., ('.25', '.5', '1', '2') )
plt.yticks(np.arange(0,1,.1))
plt.legend( (p1[0], p2[0]), ('cpu+memory', 'overall') )

plt.show()

