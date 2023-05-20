#include <Wire.h>
#include <Adafruit_MCP4725.h>
#include "AZ.h"
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

bool TxEn;
int startScan;
bool DPSK;
int toFro;
int Atype;
int Stype;
int i;
int j;

bool isFro = false;
Adafruit_MCP4725 dac;

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
int scanLength = 1000;

void setup() {
    int Atype = 5;
    i = 0;

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
    if(digitalRead(Atype2pin) == HIGH) {
        if(Atype == 4) {
            i = 0;
        }
        Atype = 4;
    }
    else if(digitalRead(Atype1pin) == HIGH && digitalRead(Atype0pin) == HIGH) {
        if(Atype == 3) {
            i = 0;
        }
        Atype = 3;
    }
    else if(digitalRead(Atype1pin)  == HIGH && digitalRead(Atype0pin) == LOW) {
        if(Atype == 2) {
            i = 0;
        }
        Atype = 2;
    }
    else if(digitalRead(Atype1pin) == LOW && digitalRead(Atype0pin) == HIGH) {
        if(Atype == 1) {
            i = 0;
        }
        Atype = 1;
    }
    else if(digitalRead(Atype1pin) == LOW && digitalRead(Atype0pin) == LOW) {
        if(Atype == 0) {
            i = 0;
        }
        Atype = 0;
    }
    else {
        if(Atype == 5) {
            i = 0;
        }
        Atype = 5;
    }

    Serial.println(digitalRead(TxEnpin));

    if(Atype == 0 && TxEnpin == HIGH) {
        dac.setVoltage(data[i], false);
    }
    else if(Atype == 1 && TxEnpin == HIGH) {
        dac.setVoltage(left[i], false);
    }
    else if(Atype == 2 && TxEnpin == HIGH) {
        dac.setVoltage(upper[i], false);
    }
    else if(Atype == 3 && TxEnpin == HIGH) {
        dac.setVoltage(right[i], false);
    }
    else if(Atype == 4 && TxEnpin == HIGH) {
        dac.setVoltage(scanData[i], false);
    }
    else {
        dac.setVoltage(2047, false);
    }

    if (digitalRead(TxEnpin) == HIGH){
      Serial.println("Reached loop and TxEn");
        if (digitalRead(toFropin)==LOW)
        {
            if (digitalRead(DPSKpin)==HIGH)
            {
                i += length/2;
                i %= length;
                i +=1;
                i %= length;
            }else{
                i +=1;
                i %= length;
            }
        
        } else 
        {
            if (digitalRead(DPSKpin)==HIGH)
            {
                if (i - length/2 < 0){
                    i = length - (length/2 - i);
                }else{
                    i -= length/2;
                }
                dac.setVoltage(data[i], false);
                if (i - 1 < 0){
                    i = length - 1;
                }else{
                    i -= 1;
                }
            }else{
                dac.setVoltage(data[i], false);
                if (i - 1 < 0){
                    i = length - 1;
                }else{
                    i -= 1;
                }
            }
        }
    }
}