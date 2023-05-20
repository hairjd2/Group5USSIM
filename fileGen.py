import numpy as np
import matplotlib.pyplot as plt

DATAPOINTS = 61600
OMEGA = 162.3376623376623
THETAMIN = (-62 * np.pi) / 180
THETAMAX = (62 * np.pi) / 180
THETAR = (-10 * np.pi) / 180
THETABW = (2 * np.pi) / 180
foundMin = -1
foundMax = 1
VMIN = 2047 - 205
VMAX = 2047 + 205

def genFile():
    with open("txtfiles\AZ.txt", 'w') as file:
        tVals = np.arange(0, 100, 0.1)
        file.write("int data[1000] = {\n")
        for t in tVals:
            # newVal = str(calcSinx(t))
            newVal = str(mapFunc(calcSinx(t), foundMin, foundMax, VMIN, VMAX))
            file.write(newVal + ",\n")
        file.write("};")

def calcSinx(t):
    x = np.pi * ((THETAMIN + (t / 50) - THETAR) / (1.15 * THETABW)) 
    return np.sinc(x) * np.sin(OMEGA * t)

def calcSinxFro(t):
    x = np.pi * ((THETAMAX - (t / 50) - THETAR) / (1.15 * THETABW)) 
    return np.sinc(x) * np.sin(OMEGA * t)

def mapFunc(x, inMin, inMax, outMin, outMax):
    return int((x - inMin) * (outMax - outMin) / (inMax - inMin) + outMin)

def graphFile():
    x = []
    y = []
    y2 = []
    y3 = []
    y4 = []
    count = 0.0

    with open("txtfiles\data.txt", 'r') as file:
        file.readline()
        value = ""
        while value != "};":
            value = file.readline()
            if value != "};":
                x.append(count)
                count += 0.01
                y.append(float(value[:-2]))

    with open("txtfiles\data2.txt", 'r') as file:
        file.readline()
        value = ""
        while value != "};":
            value = file.readline()
            if value != "};":
                y2.append(float(value[:-2]))

    with open("txtfiles\data3.txt", 'r') as file:
        file.readline()
        value = ""
        while value != "};":
            value = file.readline()
            if value != "};":
                y3.append(float(value[:-2]))

    with open("txtfiles\data4.txt", 'r') as file:
        file.readline()
        value = ""
        while value != "};":
            value = file.readline()
            if value != "};":
                y4.append(float(value[:-2]))
        
        # newY = []
        # for val in y:
        #     if(val > 2047):
        #         newY.append(val * 0.5)
        #     elif(val < 2047):
        #         newY.append(val * 2)
        #     else:
        #         newY.append(val)
    
    # print(y)
    plt.figure()
    plt.plot(x, y)
    plt.plot(x, y2)
    plt.plot(x, y3)
    plt.plot(x, y4)
    plt.axhline(y=2047, xmin=np.min(x), xmax=np.max(x))
    plt.show()

def genCosFile():
    with open("txtfiles\data.txt", 'w') as file:
        tVals = np.arange(0, 2*np.pi, 0.01)
        file.write("int data[629] = {\n")
        for t in tVals:
            # newVal = str(calcSinx(t))
            newVal = str(mapFunc(np.cos(t), foundMin, foundMax, VMIN, VMAX))
            file.write("\t" + newVal + ",\n")
        file.write("};")


if __name__ == "__main__":
    # genFile()
    genCosFile()
    graphFile()
    # graphTestFile()