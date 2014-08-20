def parse(path):
    
    file = open(path, 'r')
    data = []
    for cpu in range(0, 32):
        data.append({'pck':[], 'pp0': [], 'dram': []})
 
    cpu = 0

    for line in file:
        dataArr = line.split()
        if len(dataArr) == 1:
            cpu = 0
        else:
            data[cpu]['pck'].append(dataArr[1])
            data[cpu]['pp0'].append(dataArr[2])
            data[cpu]['dram'].append(dataArr[3])
            cpu = cpu+1 

    return data
