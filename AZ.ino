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
int ledPin = 2;

int ledState = HIGH;
int Atype2state;
int Atype1state;
int Atype0state;
int TxEnState;
int startScanState;
int toFroState;
int DPSKState;

int TxEn;
int startScan;
int DPSK;
int toFro;
int Atype2;
int Atype1;
int Atype0;
int Atype;
int Stype;
int i;
int j;

bool isFro = false;
Adafruit_MCP4725 dac;

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
int length = 1000;
// int stationType[3][3] = {{-10, }, {-10, }, {3, }}

void setup() {
    int Atype = 5;
    int Stype = 0;
    i = 0;
    j = 0;

    Serial.println(j);

    Wire.begin();
    dac.begin(DAC_ADDRESS);
    dac.setVoltage(0, false); // set initial DAC output to 0V
    Serial.begin(9600);
    delay(25);
    
    setPins();
}

void loop() {
// TODO: poll for each pin we're getting inputs of
    checkPins();

    if(DPSK) {
        if(!isFro) {
            i += length / 2;
            i %= length;
        }
        else {
            if ((i - (length / 2)) < 0){
                i = length - (length/2 - i);
            } else {
                i -= length/2;
            }
        }
    }


    if (TxEn || j % 100 == 0) {
        if (!isFro) {
            dac.setVoltage(data[i], false);
            i++;
            i %= length;
            
        } else {
            dac.setVoltage(data[i], false);
            if ((i - 1) < 0){
                i = length - 1;
            }else{
                i -= 1;
            }
        }
        
    }

    j++;
    Serial.println(j);
}

void setPins() {
    pinMode(ledPin, OUTPUT);
    pinMode(transDataSCL, OUTPUT);
    pinMode(transDataSDA, OUTPUT);
    pinMode(Atype2pin, INPUT);
    pinMode(Atype1pin, INPUT);
    pinMode(Atype0pin, INPUT);
    pinMode(TxEnpin, INPUT);
    pinMode(startScanpin, INPUT);
    pinMode(toFropin, INPUT);
    pinMode(DPSKpin, INPUT);

    Atype2state = LOW;
    Atype1state = LOW;
    Atype0state = LOW;
    TxEnState = LOW;
    startScanState = LOW;
    toFroState = LOW;
    DPSKState = LOW;
    digitalWrite(ledPin, ledState);
}

void checkPins() {
    debounce(TxEnpin, TxEn, TxEnState);
    debounce(startScanpin, startScan, startScanState);
    debounce(DPSKpin, DPSK, DPSKState);

    debounce(toFropin, toFro, toFroState);
    if(toFro == HIGH) {
        isFro = true;
    }
    else {
        isFro = false;
    }

    debounce(Atype2pin, Atype2, Atype2state);
    debounce(Atype1pin, Atype1, Atype1state);
    debounce(Atype0pin, Atype0, Atype0state);

    if(Atype2 == HIGH) {
        Atype = 4;
    }
    else if(Atype1 == HIGH && Atype0 == HIGH) {
        Atype = 3;
    }
    else if(Atype1  == HIGH && Atype0 == LOW) {
        Atype = 2;
    }
    else if(Atype1 == LOW && Atype0 == HIGH) {
        Atype = 1;
    }
    else if(Atype1 == LOW && Atype0 == LOW) {
        Atype = 0;
    }
    else {
        Atype = 5;
    }
}

void debounce(int pin, int &state, int &lastState) {
    int reading = digitalRead(pin);

    if(reading != lastState) {
        lastDebounceTime = millis();
    }

    if((millis() - lastDebounceTime) > debounceDelay) {
        if(reading != state) {
            state = reading;

            if(state == HIGH) {
                ledState = !ledState;
            }
        }
    }

    digitalWrite(ledPin, ledState);

    lastState = reading;
}