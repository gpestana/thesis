import sys
import matplotlib.pyplot as plt

times = {
	'atom': [1043, 1063, 1345, 1647],
	'quad': [290, 290, 297, 303, 356, 592],
	'ARM': [575, 593, 595, 607, 764, 1253]
}

width = .20


#atom
atom = plt.bar(0-width, times['atom'][0], width, label='atom')
plt.bar(1-width, times['atom'][1], width)
plt.bar(2-width, times['atom'][2], width)
plt.bar(3-width, times['atom'][3], width)

#quad
quad = plt.bar(0, times['quad'][0], width, color='r')
plt.bar(1, times['quad'][1], width, color='r')
plt.bar(2, times['quad'][2], width, color='r')
plt.bar(3, times['quad'][3], width, color='r')
plt.bar(4, times['quad'][4], width, color='r')
plt.bar(5, times['quad'][5], width, color='r')

#arm
arm = plt.bar(0+width, times['ARM'][0], width, color='g')
plt.bar(1+width, times['ARM'][1], width, color='g')
plt.bar(2+width, times['ARM'][2], width, color='g')
plt.bar(3+width, times['ARM'][3], width, color='g')
plt.bar(4+width, times['ARM'][4], width, color='g')
plt.bar(5+width, times['ARM'][5], width, color='g')

plt.legend((atom, quad, arm), ['atom', 'quad', 'ARM'] )
plt.xticks(range(6),(1,2,3,4,5,8))
plt.yticks(range(0, 1801, 200))
plt.ylabel('Time (s)')
plt.xlabel('Nr Processes')
plt.title('Events\' processing time')
plt.show()