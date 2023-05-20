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
VMIN = 0
VMAX = 4095

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
        
        newY = []
        for val in y:
            newY.append(val * 0.75)
    
    # print(y)
    plt.figure()
    plt.plot(x, y)
    plt.plot(x, newY)
    plt.ylim(0, 4095)
    print("Min value:", np.min(y))
    print("Max value:", np.max(y))
    plt.show()

def genCosFile():
    with open("txtfiles\data.txt", 'w') as file:
        tVals = np.arange(0, 2*np.pi, 0.01)
        file.write("int data[1000] = {\n")
        for t in tVals:
            # newVal = str(calcSinx(t))
            newVal = str(((mapFunc(np.cos(t), foundMin, foundMax, VMIN, VMAX)) // 10) + 2047 - 204.5)
            file.write("\t" + newVal + ",\n")
        file.write("};")


if __name__ == "__main__":
    # genFile()
    genCosFile()
    graphFile()
    # graphTestFile()