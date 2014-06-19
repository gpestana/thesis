import sys
import matplotlib.pyplot as plt

armTimes = [95, 95, 95, 97, 100, 114]
quadTimes = [7.50, 7.50, 7.50, 8, 9.30, 13.30]
atomTimes = [30, 30, 37.5, 44.15, 53.40, 90]

allTimes = [armTimes, quadTimes, atomTimes]
width = .20

if sys.argv[1] == '-arch':

	#atom
	plt.bar(0-width, quadTimes[0], width, label = 'test')
	plt.bar(1-width, quadTimes[1], width)
	plt.bar(2-width, quadTimes[2], width)
	plt.bar(3-width, quadTimes[3], width)
	plt.bar(4-width, quadTimes[4], width)
	plt.bar(5-width, quadTimes[5], width)

	#quad
	plt.bar(0, atomTimes[0], width, color='r')
	plt.bar(1, atomTimes[1], width, color='r')
	plt.bar(2, atomTimes[2], width, color='r')
	plt.bar(3, atomTimes[3], width, color='r')
	plt.bar(4, atomTimes[4], width, color='r')
	plt.bar(5, atomTimes[5], width, color='r')

	#arm
	plt.bar(0+width, armTimes[0], width, color='g')
	plt.bar(1+width, armTimes[1], width, color='g')
	plt.bar(2+width, armTimes[2], width, color='g')
	plt.bar(3+width, armTimes[3], width, color='g')
	plt.bar(4+width, armTimes[4], width, color='g')
	plt.bar(5+width, armTimes[5], width, color='g')
	

	plt.xticks(range(6),(1,2,3,4,5,8))
	plt.yticks(range(0, 130, 10))
	plt.ylabel('time(m)')
	plt.xlabel('nr cpus')

	plt.title('time x nr_processes x arch')

	plt.show()
	

if sys.argv[1] == '-cpu':
	print 'plots by cpu'

else:
	print 'invalid input. -cpu or -arch'