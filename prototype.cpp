/*
* File: MLS_proto.cpp
* Project: CMPE 349 USSIM, Spring 2023
* Author: Nick Myers
* Date: 04/26/2023
* E-mail: nmyers3@umbc.edu
*
* Create prototype for Sine function output
*/

// Libraries
#include <iostream>
#include <string>
#include <math.h>
#include <cmath>
#include <fstream>

using namespace std;

// Constants
#define T_MIN 461.25
#define T_MAX 153.75
#define OMEGA_T_MIN = sin(1626.01626 * T_MIN + (2*M_PI))
#define OMEGA_T_MAX = sin(1626.01626 * T_MAX + (2*M_PI))

double generate_sinx(int scanTo, int level, double thetaT, double thetaR, double thetaBW);
double generate_wave(int scanTo, int t, double thetaT, double thetaR, double thetaBW);

int main(){
    double wave;
    double sinXoXMax = generate_sinx(1, 1, -1.082, -0.1745, 0.034);
    double sinXoXMin = generate_sinx(1, 0, -1.082, -0.1745, 0.034);
    cout << sinXoXMax << endl;
    cout << sinXoXMin << endl;

    ofstream output("wave.txt");

    for (int i = 0; i < 616; i++){
        wave = generate_wave(1, i, -1.082, -0.1745, 0.034);
        output << i << "\t";
        output << wave << "\n";
    }

    output.close();
    return 0;
}

double generate_sinx(int scanTo, int level, double thetaT, double thetaR, double thetaBW){
    double x;
    double sinXoX;

    if (scanTo && level){
        x = M_PI * (((thetaT + (T_MAX/50.0)) - thetaR)/(1.15 * thetaBW));
    }
    else if (scanTo && !level){
        x = M_PI * (((thetaT + (T_MIN/50.0)) - thetaR)/(1.15 * thetaBW));
    }
    else if (!scanTo && level){
        x = M_PI * (((thetaT - (T_MAX/50.0)) - thetaR)/(1.15 * thetaBW));
    }
    else{
        x = M_PI * (((thetaT - (T_MIN/50.0)) - thetaR)/(1.15 * thetaBW));
    }

    sinXoX = sin(x)/x;
    return sinXoX;
}

double generate_wave(int scanTo, int t, double thetaT, double thetaR, double thetaBW){
    double x;
    double sinXoX;
    double wave;

    if(scanTo){
        x = M_PI * (((thetaT + (t/50.0)) - thetaR)/(1.15 * thetaBW));
    }
    else{
        x = M_PI * (((thetaT - (t/50.0)) - thetaR)/(1.15 * thetaBW));
    }

    sinXoX = sin(x)/x;
    wave = sinXoX * sin(1626.01626 * t * (2*M_PI));
    return wave;
}