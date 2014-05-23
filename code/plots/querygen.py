import os, sys

matchStr = 'Sensor Reading        : '

script_dir = os.path.dirname(__file__)
filePath = os.path.join(script_dir, sys.argv[1])

#querygen.py inputName nameExp
nameExp = sys.argv[2]

allMatches = []

f = open(filePath,'r')
lines = f.readlines()
f.close()

for line in lines:
    if matchStr in line:
        allMatches.append(line)

print allMatches[0::4]