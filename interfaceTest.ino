int transDataSCL = 27;
int transDataSDA = 26;
int Atype2 = 13;
int Atype1 = 12; // seems to be negated
int Atype0 = 11;
int Stype1 = 10;
int Stype0 = 9;
int startScanpin = 8;
int DPSKpin = 7;

int startScan;
int DPSK;
int Atype;
int Stype;

void setup() {
// TODO: setup the pins we want to watch
    int Atype = 5;
    int Stype = 0;

    setPins();
}

void loop() {
// TODO: poll for each pin we're getting inputs of
    checkPins();

}

void setPins() {
    pinMode(transData, OUTPUT);
    pinMode(Atype2, INPUT);
    pinMode(Atype1, INPUT);
    pinMode(Atype0, INPUT);
    pinMode(Stype1, INPUT);
    pinMode(Stype0, INPUT);
    pinMode(startScanpin, INPUT);
    pinMode(DPSKpin, INPUT);
}

void checkPins() {
    startScan = digitialRead(startScanpin);
    DPSK = digitalRead(DPSKpin);

    if(digitalRead(Atype2) == HIGH) {
        Atype = 4;
    }
    else if(digitalRead(Atype1) == HIGH && digitalRead(Atype0) == HIGH) {
        Atype = 3;
    }
    else if(digitalRead(Atype1)  == HIGH && digitalRead(Atype0) == LOW) {
        Atype = 2;
    }
    else if(digitalRead(Atype1)  == LOW && digitalRead(Atype0) == HIGH) {
        Atype = 1;
    }
    else if(digitalRead(Atype1)  == LOW && digitalRead(Atype0) == LOW) {
        Atype = 0;
    }
    else {
        Atype = 5;
    }

    if(digitalRead(Stype1)  == HIGH && digitalRead(Stype0) == LOW) {
        Stype = 2;
    }
    else if(digitalRead(Stype1)  == LOW && digitalRead(Stype0) == HIGH) {
        Stype = 1;
    }
    else if(digitalRead(Stype1)  == LOW && digitalRead(Stype0) == LOW) {
        Stype = 0;
    }
    else {
        Stype = -1;
    }


}