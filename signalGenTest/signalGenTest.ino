// Nkosi & Seth
// MLS Signal Generation
// Arduino Nano Board

/*
Required Functionality:
    - Sine wave generation
*/
#include <Wire.h>
#include <Adafruit_MCP4725.h>
#include <math.h>
#include <cmath>
Adafruit_MCP4725 dac;
const int ARRAY_SIZE = 256;
const int NEGATION_MULTIPLIER = -1;
const int QUARTER_DEGREE_VAL = 90;
//const double PI = 3.14159265;
const double WAVE_PERIOD = 615E-3;
const int STRAIGHT_ANGLE = 180;
const double FREQ = 1626.01626;
const int SCAN_TO = 1;

float a_type[6] = {1, 0.5, 0.25, 0.125, 10, 0};
float s_type[3] = {1.5, 2, 2};
int theta_min = -62;
int theta_max = 62; 
int theta_R = -3;
int theta_BW = 2;
int theta_A = 10;
int omega_t[616];
int sinx_x_to[616];
int sinx_x_fro[616];
double data_points[ARRAY_SIZE] = {0};
double data_point_multiplier = QUARTER_DEGREE_VAL / ARRAY_SIZE;
double amplitude_multiplier = 1;
double quarter_period = WAVE_PERIOD / 4;
int antenna_pin = 26;
double radian_converter = PI / STRAIGHT_ANGLE;


void setup(){

    generate_wt();
    generate_sinx();
    dac.begin(0x62);
}

void generate_wt(){
    double temp;
    for(int i = 0; i < 616; i++){
        temp =  sin(FREQ * i + PI) + 1.65;
        temp = temp * pow(2, 12-1)/2;
        omega_t[i] = round(temp);
    }
}

void generate_sinx(){
    double temp;
    double x;
    if (SCAN_TO)
    {
        for(int i = 0; i < 616; i++){
            x = PI * ((theta_min + i/50) - theta_R) / (1.15*theta_BW);
            temp =  (sin(x)/x) + 1.65;
            temp = temp * pow(2, 12-1)/2;
            sinx_x_to[i] = round(temp);
        }
    }else{
        for(int i = 0; i < 616; i++){
            x = PI * ((theta_max + i/50) - theta_R) / (1.15*theta_BW);
            temp =  (sin(x)/x) + 1.65;
            temp = temp * pow(2, 12-1)/2;
            sinx_x_fro[i] = round(temp);
        }
    }
    
    
    
}



void loop(){
    for(int i = 0; i < 616; i++){
        dac.setVoltage((sinx_x_to[i]*omega_t[i]*theta_A)/3.3, false);

    }
}
