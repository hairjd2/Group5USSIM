import numpy as np

DATAPOINTS = 61600
OMEGA = 1626.01626
THETAMIN = (-62 * np.pi) / 180
THETAR = (-10 * np.pi) / 180
THETABW = (2 * np.pi) / 180

def genFile():
    with open("txtfiles/AZ.txt", 'w') as file:
        file.write("AZ = {\n")
        for t in range(10):
            file.write(str(calcSinx(t / 100)))
        file.write("}")

def calcSinx(t):
    x = np.pi * ((THETAMIN + (t / 50) - THETAR) / (1.15 * THETABW)) 

def graphFile():
    with open("txtfiles/AZ.txt", 'r') as file:
        file.readline()

if __name__ == "__main__":
    genFile()
    graphFile()