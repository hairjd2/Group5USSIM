#include <Wire.h>
#include <Adafruit_MCP4725.h>
#include "AZ.h"
#include "DATA.h"
#include "LEFT_OCI.h"
#include "RIGHT_OCI.h"
#include "UPPER_OCI.h"
#define DAC_ADDRESS 0x62

const int transDataSCL = 27;
const int transDataSDA = 26;
const int Atype2pin = 13;
const int Atype1pin = 12; // seems to be negated
const int Atype0pin = 11;
const int TxEnpin = 10;
const int startScanpin = 9;
const int toFropin = 7;
const int DPSKpin = 1;

int Atype;
int i;
int currDPSK;

bool isFro = false;
Adafruit_MCP4725 dac;

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
int scanLength = 1000;
int length;

void setup() {
    currDPSK = LOW;
    Atype = 2;
    i = 0;
    length = 629;

    pinMode(transDataSCL, OUTPUT);
    pinMode(transDataSDA, OUTPUT);
    pinMode(Atype2pin, INPUT);
    pinMode(Atype1pin, INPUT);
    pinMode(Atype0pin, INPUT);
    pinMode(TxEnpin, INPUT);
    pinMode(startScanpin, INPUT);
    pinMode(toFropin, INPUT);
    pinMode(DPSKpin, INPUT);

    Serial.begin(9600);
    Wire.begin();
    dac.begin(DAC_ADDRESS);
    dac.setVoltage(0, false); // set initial DAC output to 0V
    delay(25);
}

void loop() {
    if(digitalRead(Atype2pin) == HIGH && digitalRead(Atype0pin) == LOW) {
        if(Atype != 4) {
            i = 0;
        }
        Atype = 4;
    }
    else if(digitalRead(Atype1pin) == HIGH && digitalRead(Atype0pin) == HIGH) {
        if(Atype != 3) {
            i = 0;
        }
        Atype = 3;
    }
    else if(digitalRead(Atype1pin)  == HIGH && digitalRead(Atype0pin) == LOW) {
        if(Atype != 2) {
            i = 0;
        }
        Atype = 2;
    }
    else if(digitalRead(Atype2pin) == LOW && digitalRead(Atype1pin) == LOW && digitalRead(Atype0pin) == HIGH) {
        if(Atype != 1) {
            i = 0;
        }
        Atype = 1;
    }
    else if(digitalRead(Atype1pin) == LOW && digitalRead(Atype0pin) == LOW) {
        if(Atype != 0) {
            i = 0;
        }
        Atype = 0;
    }
    else {
        if(Atype != 5) {
            i = 0;
        }
        Atype = 5;
    }

    // for(int i = 0; i < length; i++){
    //    dac.setVoltage(data[i], false);
    // }

    // for(int i = 0; i < 100; i++){
    //    dac.setVoltage(0, false);
    // }

    // for(int i = 0; i < length; i++){
    //    dac.setVoltage(left[i], false);
    // }

    //  for(int i = 0; i < 100; i++){
    //    dac.setVoltage(0, false);
    // }

    // for(int i = 0; i < length; i++){
    //    dac.setVoltage(upper[i], false);
    // }

    //  for(int i = 0; i < 100; i++){
    //    dac.setVoltage(0, false);
    // }

    // for(int i = 0; i < length; i++){
    //    dac.setVoltage(right[i], false);
    // }

    // for(int i = 0; i < 100; i++){
    //    dac.setVoltage(0, false);
    // }

    // for(int i = 0; i < scanLength; i++){
    //    dac.setVoltage(scanData[i], false);
    // }

    // Serial.println(Atype);

    //if(Atype == 0 && digitalRead(TxEnpin) == HIGH) {
    if(Atype == 0){
        //Serial.println(data[i]);
        dac.setVoltage(data[i], false);
        //Serial.println(i);
    }
    else if(Atype == 1 && digitalRead(TxEnpin) == HIGH) {
        dac.setVoltage(left[i], false);
    }
    else if(Atype == 2 && digitalRead(TxEnpin) == HIGH) {
        dac.setVoltage(upper[i], false);
    }
    else if(Atype == 3 && digitalRead(TxEnpin) == HIGH) {
        dac.setVoltage(right[i], false);
    }
    else if(Atype == 4 && digitalRead(TxEnpin) == HIGH) {
        dac.setVoltage(scanData[i], false);
    }
    else {
        dac.setVoltage(2047, false);
        //dac.setVoltage(data[i], false);
    }

    //Serial.println(Atype);
    
    //if (digitalRead(TxEnpin) == HIGH) {
      if (1 == 1){
        if(Atype == 4) {
            if(digitalRead(toFropin) == LOW) {
                i += 1;
                i %= scanLength;
            }
            else {
                if (i - 1 < 0){
                    i = scanLength - 1;
                }else{
                    i -= 1;
                }
            }
          delayMicroseconds(620);
        }
        else if(Atype == 0) {
          //Serial.println("Reached Atype 0 if statement");
            if (digitalRead(DPSKpin) != currDPSK)
            {              
                i += length/2;
                i %= length;
                i += 10;
                i %= length;
                currDPSK = digitalRead(DPSKpin);
            } else {
              //Serial.println(i);
                i += 10;
                i %= length;
            }
        }
        else {
            i += 10;
            i %= length;
        }
    }
}