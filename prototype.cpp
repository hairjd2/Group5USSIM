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
const double OMEGA_T_MIN = sin(1626.01626 * T_MIN + (2*M_PI));
const double OMEGA_T_MAX = sin(1626.01626 * T_MAX + (2*M_PI));

double generate_sinx(int scanTo, int level, double thetaT, double thetaR, double thetaBW);
double generate_wave(int scanTo, int t, double thetaT, double thetaR, double thetaBW);
long map(long x, long in_min, long in_max, long out_min, long out_max);

int main(){
    double wave;
    long waveLong;
    int mappedWave;

    ofstream output("Constant_Waves.txt");
    
    // To Scan AZ
    //output << "{" << "\n";

    for (int i = 0; i < 616; i++){
        wave = generate_wave(0, i, 1.082, -0.1745, 0.034);
        waveLong = wave * pow(10, 5);
        mappedWave = map(waveLong, -0.342*pow(10, 5), 0.832*pow(10, 5), 4095, 0);
        output << i << "\t";
        output << wave << "\n";
        //output << mappedWave << "\n";
    }
    //output << "};";

    // 

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
    wave = sinXoX * sin(1626.01626 * t + (2*M_PI));
    return wave;
}

long map(long x, long in_min, long in_max, long out_min, long out_max){
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}