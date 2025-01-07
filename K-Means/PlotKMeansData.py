import matplotlib as mpl
import matplotlib.pyplot as plt
import matplotlib.colors

minErrors = []
y = {}
for i in range (0,26):
    y[i] = []

def clearDict(y):
    for i in range (0,26):
        y[i].clear()

def manipulateData(dataList, numofclusters):
    for i in range(0, len(dataList)):
        if(i==0):
            minErrors.append(float(dataList[i]))
        elif(i>=1 and i<1201):
            splitData = [float(value) for value in dataList[i].split(' ')]
            if(splitData[2]==0):
                y[0].append(splitData[0])
                y[1].append(splitData[1])
            elif(splitData[2]==1):
                y[2].append(splitData[0])
                y[3].append(splitData[1])
            elif(splitData[2]==2):
                y[4].append(splitData[0])
                y[5].append(splitData[1])
            elif(splitData[2]==3):
                y[6].append(splitData[0])
                y[7].append(splitData[1])
            elif(splitData[2]==4):
                y[8].append(splitData[0])
                y[9].append(splitData[1])
            elif(splitData[2]==5):
                y[10].append(splitData[0])
                y[11].append(splitData[1])
            elif(splitData[2]==6):
                y[12].append(splitData[0])
                y[13].append(splitData[1])
            elif(splitData[2]==7):
                y[14].append(splitData[0])
                y[15].append(splitData[1])
            elif(splitData[2]==8):
                y[16].append(splitData[0])
                y[17].append(splitData[1])
            elif(splitData[2]==9):
                y[18].append(splitData[0])
                y[19].append(splitData[1])
            elif(splitData[2]==10):
                y[20].append(splitData[0])
                y[21].append(splitData[1])
            else:
                y[22].append(splitData[0])
                y[23].append(splitData[1])
        elif(i>=1201 and i<(1201+numofclusters)):
            splitMeanPos = [float(value) for value in dataList[i].split()]
            y[24].append(float(splitMeanPos[0]))
            y[25].append(float(splitMeanPos[1]))

data = open("3_clusters.txt", "r");
dataString = data.read();
dataList = dataString.split("\n")
M = 3
manipulateData(dataList, M)

fig, ax = plt.subplots()
ax.plot(y[24], y[25], '*', color = (0.0, 0.0, 0.0))
ax.plot(y[0], y[1], '+', color = (1.0, 0.0, 0.0))
ax.plot(y[2], y[3], '+', color = (0.0, 1.0, 0.0))
ax.plot(y[4], y[5], '+', color = (0.0, 0.0, 1.0))
plt.show()

#----------------------------------------------------------------

clearDict(y)

data = open("6_clusters.txt", "r");
dataString = data.read();
dataList = dataString.split("\n")
M = 6
manipulateData(dataList, M)

fig, ax = plt.subplots()
ax.plot(y[24], y[25], '*', color = (0.0, 0.0, 0.0))
ax.plot(y[0], y[1], '+', color = (1.0, 0.0, 0.0))
ax.plot(y[2], y[3], '+', color = (0.0, 1.0, 0.0))
ax.plot(y[4], y[5], '+', color = (0.0, 0.0, 1.0))
ax.plot(y[6], y[7], '+', color = (1.0, 1.0, 0.0))
ax.plot(y[8], y[9], '+', color = (1.0, 0.0, 1.0))
ax.plot(y[10], y[11], '+', color = (0.0, 1.0, 1.0))
plt.show()
#----------------------------------------------------------------

clearDict(y)

data = open("9_clusters.txt", "r");
dataString = data.read();
dataList = dataString.split("\n")
M = 9
manipulateData(dataList, M)

fig, ax = plt.subplots()
ax.plot(y[24], y[25], '*', color = (0.0, 0.0, 0.0))
ax.plot(y[0], y[1], '+', color = (1.0, 0.0, 0.0))
ax.plot(y[2], y[3], '+', color = (0.0, 1.0, 0.0))
ax.plot(y[4], y[5], '+', color = (0.0, 0.0, 1.0))
ax.plot(y[6], y[7], '+', color = (1.0, 1.0, 0.0))
ax.plot(y[8], y[9], '+', color = (1.0, 0.0, 1.0))
ax.plot(y[10], y[11], '+', color = (0.0, 1.0, 1.0))
ax.plot(y[12], y[13], '+', color = (0.5, 0.5, 0.0))
ax.plot(y[14], y[15], '+', color = (0.5, 0.0, 0.5))
ax.plot(y[16], y[17], '+', color = (0.0, 0.5, 0.5))
plt.show()

#----------------------------------------------------------------

clearDict(y)

data = open("12_clusters.txt", "r");
dataString = data.read();
dataList = dataString.split("\n")
M = 12
manipulateData(dataList, M)

fig, ax = plt.subplots()
ax.plot(y[24], y[25], '*', color = (0.0, 0.0, 0.0))
ax.plot(y[0], y[1], '+', color = (1.0, 0.0, 0.0))
ax.plot(y[2], y[3], '+', color = (0.0, 1.0, 0.0))
ax.plot(y[4], y[5], '+', color = (0.0, 0.0, 1.0))
ax.plot(y[6], y[7], '+', color = (1.0, 1.0, 0.0))
ax.plot(y[8], y[9], '+', color = (1.0, 0.0, 1.0))
ax.plot(y[10], y[11], '+', color = (0.0, 1.0, 1.0))
ax.plot(y[12], y[13], '+', color = (0.5, 0.5, 0.0))
ax.plot(y[14], y[15], '+', color = (0.5, 0.0, 0.5))
ax.plot(y[16], y[17], '+', color = (0.0, 0.5, 0.5))
ax.plot(y[18], y[19], '+', color = (0.25, 0.75, 0.0))
ax.plot(y[20], y[21], '+', color = (0.25, 0.0, 0.75))
ax.plot(y[22], y[23], '+', color = (0.0, 0.25, 0.75))

plt.show()

#---------------------------------------------------------------
fig, ax = plt.subplots()
ax.plot([3,6,9,12], minErrors, linestyle='-', marker='X', color='r')
plt.ylabel("Minimum clustering Error")
plt.xlabel("Number of Clusters")
plt.show()