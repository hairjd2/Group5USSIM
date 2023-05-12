#include <Wire.h>
#include <Adafruit_MCP4725.h>
#include "AZ.h"
#define DAC_ADDRESS 0x62

const int TxEnpin = 10;
int i;
Adafruit_MCP4725 dac;

void setup() {
    Wire.begin();
    dac.begin(DAC_ADDRESS);
    dac.setVoltage(0, false);
    pinMode(TxEnpin, INPUT);
    i = 30;
    Serial.begin(9600);
    delay(25);
}

void loop() {
    Serial.println(i);

    if(loop == HIGH) {
        dac.setVoltage(data[i], false);
        i++;
    }
}