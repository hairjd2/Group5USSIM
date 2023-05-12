#include <Wire.h>
#include <Adafruit_MCP4725.h>
#include "AZ.h"
#define DAC_ADDRESS 0x60

const int transDataSCL = 27;
const int transDataSDA = 26;
const int TxEnpin = 13;
int j;
Adafruit_MCP4725 dac;

void setup() {
    Wire.begin();
    dac.begin(DAC_ADDRESS);
    dac.setVoltage(0, false);
    pinMode(TxEnpin, INPUT);
    pinMode(transDataSCL, OUTPUT);
    pinMode(transDataSDA, OUTPUT);
    j = 30;
    Serial.begin(9600);
    delay(25);
}

void loop() {

    if(TxEnpin == HIGH) {
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
        // dac.setVoltage(data[i], false);
        Serial.println(j);
        j++;
    }
}