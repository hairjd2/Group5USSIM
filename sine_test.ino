#include <Wire.h>
#include <Adafruit_MCP4725.h>
#include <math.h>
#include "AZ.h"

#define DAC_ADDRESS 0x62 // MCP4725 I2C address

Adafruit_MCP4725 dac;
double theta_R = -10 * PI/180;
int SCAN_TO = 1;
double theta_BW = 2* PI/180;
double theta_min = -62* PI/180;
double theta_max = 62* PI/180;
double max_SINX;
double min_SINX;
double min_OMEGAT = sin(1626.01626 * 461.25 + (2*PI)) ;
double max_OMEGAT = sin(1626.01626 * 153.75 + (2*PI)) ;

void setup() {
  Wire.begin();
  dac.begin(DAC_ADDRESS);
  dac.setVoltage(0, false); // set initial DAC output to 0V
  Serial.begin(9600);
  delay(25);
  // generate_sinx();
}

void generate_sinx(){
    double q1 = 153.75;
    double q3 = 461.25;
    double x_max;
    double x_min;
    double temp_min;
    double temp_max;
    if (SCAN_TO)
    {
        x_max = PI * ((theta_min + q1/50.0) - theta_R) / (1.15*theta_BW);
        x_min = PI * ((theta_min + q3/50.0) - theta_R) / (1.15*theta_BW);
        temp_min = (sin(x_min)/x_min);
        temp_max = (sin(x_max)/x_max);
        min_SINX = temp_min;
        max_SINX = temp_max;
    }else{
        x_max = PI * ((theta_max - q1/50.0) - theta_R) / (1.15*theta_BW);
        x_min = PI * ((theta_max - q3/50.0) - theta_R) / (1.15*theta_BW);
        temp_min = (sin(x_min)/x_min);
        temp_max = (sin(x_max)/x_max);
        min_SINX = temp_min;
        max_SINX = temp_max;
    }
}

double generate_wave(float t){
    double x;
    double SINX;
    if (SCAN_TO)
    {
        x = PI * ((theta_min + t/50.0) - theta_R) / (1.15*theta_BW);
        SINX = (sin(x)/x);
    }else{
        x = PI * ((theta_max - t/50.0) - theta_R) / (1.15*theta_BW);
        SINX = (sin(x)/x);
    }

    if(t == 154) Serial.println(SINX * sin(1626.01626 * t + (2*PI)), DEC);
    return SINX * sin(1626.01626 * t + (2*PI));
}

void loop() {
  for(int i = 0; i < 1000; i++) {
    int dacValue = int(data[i]);

    dac.setVoltage(dacValue, false);
    delayMicroseconds(100);
  }

  for(int i = 999; i >= 0; i--) {
    int dacValue = int(data[i]);

    dac.setVoltage(dacValue, false);
    delayMicroseconds(100);
  }
}


