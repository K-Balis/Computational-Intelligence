import matplotlib as mpl
import matplotlib.pyplot as plt
import matplotlib.colors

category_1_x1 = []
category_1_x2 = []
category_2_x1 = []
category_2_x2 = []
category_3_x1 = []
category_3_x2 = []
wrong_x1 = []
wrong_x2 = []

def separateData(dataList):
    for i in range(0, len(dataList)):
        if(i==0):
            correct_predictions = int(dataList[i])
        elif(i>=1 and i< (correct_predictions + 1)):
            splitData = [float(value) for value in dataList[i].split(' ')]
            if(splitData[2]==1):
                category_1_x1.append(splitData[0])
                category_1_x2.append(splitData[1])
            elif(splitData[2]==2):
                category_2_x1.append(splitData[0])
                category_2_x2.append(splitData[1])
            elif(splitData[2]==3):
                category_3_x1.append(splitData[0])
                category_3_x2.append(splitData[1])
        elif(i >= (correct_predictions + 1) and i < 4001):
            splitData = [float(value) for value in dataList[i].split(' ')]
            wrong_x1.append(splitData[0])   
            wrong_x2.append(splitData[1])

data = open("results.txt", "r")
dataString = data.read()
dataList = dataString.split("\n")
separateData(dataList)


fig, ax = plt.subplots()
ax.plot(category_1_x1, category_1_x2, '+', color = (0.0, 1.0, 0.0))
ax.plot(category_2_x1, category_2_x2, '+', color = (0.0, 0.0, 1.0))
ax.plot(category_3_x1, category_3_x2, '+', color = (0.0, 1.0, 1.0))
ax.plot(wrong_x1, wrong_x2, 'x', color = (1.0, 0.0, 0.0))
plt.xlim([-1, 1])
plt.ylim([-1, 1])
plt.show()