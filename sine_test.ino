#include <Wire.h>
#include <Adafruit_MCP4725.h>
#include <math.h>

#define DAC_ADDRESS 0x62 // MCP4725 I2C address

Adafruit_MCP4725 dac;
double theta_R = -10 * PI/180;
int SCAN_TO = 0;
double theta_BW = 2* PI/180;
double theta_min = -62* PI/180;
double theta_max = 62* PI/180;
double max_SINX;
double min_SINX;
int min_OMEGAT = sin(1626.01626 * 461.25 + (2*PI)) * pow(10, 5);
int max_OMEGAT = sin(1626.01626 * 153.75 + (2*PI)) * pow(10, 5);

void setup() {
  Wire.begin();
  dac.begin(DAC_ADDRESS);
  dac.setVoltage(0, false); // set initial DAC output to 0V
  Serial.begin(9600);
  delay(25);
  generate_sinx();
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
        min_SINX = temp_min * pow(10, 5);
        max_SINX = temp_max * pow(10, 5);
    }else{
        x_max = PI * ((theta_max - q1/50.0) - theta_R) / (1.15*theta_BW);
        x_min = PI * ((theta_max - q3/50.0) - theta_R) / (1.15*theta_BW);
        temp_min = (sin(x_min)/x_min);
        temp_max = (sin(x_max)/x_max);
        min_SINX = temp_min * pow(10, 5);
        max_SINX = temp_max * pow(10, 5);
    }
}

double generate_wave(int t){
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
    return SINX * sin(1626.01626 * t + (2*PI));
}

void loop() {
  for (int t = 0; t < 616; t++) { // generate a full sine wave cycle
    double sinValue = generate_wave(t); // calculate sine wave value
    sinValue *= pow(10, 5);
    sinValue += 1;
    int newSinValue = (int)sinValue;
    Serial.println(min_SINX);
    Serial.println(max_SINX);
    //Serial.println(min_OMEGAT);
    //Serial.println(max_OMEGAT);
    int dacValue = map(newSinValue, min_SINX * min_OMEGAT, max_SINX * max_OMEGAT, -2047, 2047) / 10; // convert to DAC value
    dacValue = dacValue * 10 + 2047;
    //Serial.println(dacValue);
    dac.setVoltage(dacValue, false); // send DAC value
    delayMicroseconds(1000); // wait for DAC to settle
  }
}
