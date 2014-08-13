def parse(path):
    
    file = open(path, 'r')
    data = {'mem':[], 'a17':[], 'a5':[]}
    
    for line in file:
        dataArr = line.split()
        print dataArr
        if(dataArr[0] == 'mem'):
            data['mem'].append(float(dataArr[1]))    
        elif(dataArr[0] == 'a17'):
            data['a17'].append(float(dataArr[1]))
        else:
            data['a5'].append(float(dataArr[1]))

    return data    
