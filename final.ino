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

bool TxEn;
int startScan;
bool DPSK;
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

    // Atype2state = LOW;
    // Atype1state = LOW;
    // Atype0state = LOW;
    // TxEnState = LOW;
    // startScanState = LOW;
    // toFroState = LOW;
    // DPSKState = LOW;
    digitalWrite(ledPin, ledState);
}

void checkPins() {
    // debounce(TxEnpin, TxEn, TxEnState);
    Serial.println(digitalRead(TxEnpin));
    if(digitalRead(TxEnpin) == HIGH) {
        TxEn = true;
    }
    else {
        TxEn = false;
    }

    // debounce(startScanpin, startScan, startScanState);

    // debounce(DPSKpin, DPSK, DPSKState);
    Serial.println(digitalRead(DPSKpin));
    if(digitalRead(DPSKpin) == HIGH) {
        DPSK = true;
    }
    else {
        DPSK = false;
    }

    // debounce(toFropin, toFro, toFroState);
    Serial.println(digitalRead(toFropin));    
    if(digitalRead(toFropin) == HIGH) {
        isFro = true;
    }
    else {
        isFro = false;
    }

    // debounce(Atype2pin, Atype2, Atype2state);
    // debounce(Atype1pin, Atype1, Atype1state);
    // debounce(Atype0pin, Atype0, Atype0state);

    if(digitalRead(Atype2pin) == HIGH) {
        Atype = 4;
    }
    else if(digitalRead(Atype1pin) == HIGH && digitalRead(Atype0pin) == HIGH) {
        Atype = 3;
    }
    else if(digitalRead(Atype1pin)  == HIGH && digitalRead(Atype0pin) == LOW) {
        Atype = 2;
    }
    else if(digitalRead(Atype1pin) == LOW && digitalRead(Atype0pin) == HIGH) {
        Atype = 1;
    }
    else if(digitalRead(Atype1pin) == LOW && digitalRead(Atype0pin) == LOW) {
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


void setup() {
    int Atype = 5;
    int Stype = 0;
    i = 0;
    j = 0;
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
    if(digitalRead(Atype2pin) == HIGH) {
        Atype = 4;
    }
    else if(digitalRead(Atype1pin) == HIGH && digitalRead(Atype0pin) == HIGH) {
        Atype = 3;
    }
    else if(digitalRead(Atype1pin)  == HIGH && digitalRead(Atype0pin) == LOW) {
        Atype = 2;
    }
    else if(digitalRead(Atype1pin) == LOW && digitalRead(Atype0pin) == HIGH) {
        Atype = 1;
    }
    else if(digitalRead(Atype1pin) == LOW && digitalRead(Atype0pin) == LOW) {
        Atype = 0;
    }
    else {
        Atype = 5;
    }
    //setPins();
    Serial.begin(9600);
    //setPins();
    Wire.begin();
    dac.begin(DAC_ADDRESS);
    dac.setVoltage(0, false); // set initial DAC output to 0V
    delay(25);
    
    
    
    //checkPins();
    //Serial.println(digitalRead(TxEnpin));
}

void loop() {
  Serial.println(digitalRead(TxEnpin));
// TODO: poll for each pin we're getting inputs of
    //checkPins();

    // if(DPSK) {
    //     if(!isFro) {
    //         i += length / 2;
    //         i %= length;
    //     }
    //     else {
    //         if ((i - (length / 2)) < 0){
    //             i = length - (length/2 - i);
    //         } else {
    //             i -= length/2;
    //         }
    //     }
    // }


    // if (TxEn) {
    //     if (!isFro) {
    //         dac.setVoltage(data[i], false);
    //         i++;
    //         i %= length;
            
    //     } else {
    //         dac.setVoltage(data[i], false);
    //         if ((i - 1) < 0){
    //             i = length - 1;
    //         }else{
    //             i -= 1;
    //         }
    //     }
    //}
    if (digitalRead(TxEnpin)==HIGH){
      Serial.println("Reached loop and TxEn");
        if (digitalRead(toFropin)==LOW)
        {
            if (digitalRead(DPSKpin)==HIGH)
            {
                i += length/2;
                i %= length;
                dac.setVoltage(data[i], false);
                i +=1;
                i %= length;
            }else{
                dac.setVoltage(data[i], false);
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

    j++;
}