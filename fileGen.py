import numpy as np
import matplotlib.pyplot as plt

DATAPOINTS = 61600
OMEGA = 162.3376623376623
THETAMIN = (-1.5 * np.pi) / 180
THETAMAX = (29.5 * np.pi) / 180
THETAR = (3 * np.pi) / 180
THETABW = (1.5 * np.pi) / 180
foundMin = -0.9911155873732591
foundMax = 0.8038443096599659
VMIN = 0
VMAX = 4095

def genFile():
    with open("txtfiles\EL.txt", 'w') as file:
        tVals = np.arange(0, 100, 0.1)
        file.write("double data[1000] = {\n")
        for t in tVals:
            # newVal = str(calcSinx(t))
            newVal = str(mapFunc(calcSinx(t), foundMin, foundMax, VMIN, VMAX))
            file.write(newVal + ",\n")
        file.write("};")

    with open("txtfiles\Test.txt", 'w') as file:
        file.write("EL = {\n")
        for t in range(10000):
            newVal = str(calcSinx(t / 100))
            # newVal = str(mapFunc(calcSinx(t / 100), foundMin, foundMax, VMIN, VMAX))
            file.write(newVal + ",\n")
        file.write("}")
    
    # with open("txtfiles\Test.txt", 'w') as file:
    #     for t in range(10000):
    #         newT = t / 100000
    #         newline = str(THETAMIN + (newT / 50)) + "\t" + str(calcSinx(newT)) + "\n"
    #         file.write(newline)
        # file.write("}")

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

    with open("txtfiles\EL.txt", 'r') as file:
        file.readline()
        value = ""
        while value != "};":
            value = file.readline()
            if value != "};":
                x.append(count)
                count += 0.01
                y.append(float(value[:-2]))
    
    # print(y)
    plt.figure()
    plt.plot(x, y)
    # plt.xlim(40, 60)
    print("Min value:", np.min(y))
    print("Max value:", np.max(y))
    plt.show()

def graphTestFile():
    x = []
    y = []
    count = 0.0

    with open("txtfiles\Test.txt", 'r') as file:
        file.readline()
        value = ""
        while value != "}":
            value = file.readline()
            if value != "}":
                x.append(count)
                count += 0.01
                y.append(float(value[:-2]))
    
    # print(y)
    plt.figure()
    plt.plot(x, y)
    # plt.xlim(40, 60)
    print("Min value:", np.min(y))
    print("Max value:", np.max(y))
    plt.show()

if __name__ == "__main__":
    genFile()
    graphFile()
    graphTestFile()