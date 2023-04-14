int transDataSCL = 27;
int transDataSDA = 26;
int Atype2 = 13;
int Atype1 = 12; // seems to be negated
int Atype0 = 11;
int TxEnpin = 10;
int startScanpin = 9;
int toFropin = 8;
int DPSKpin = 7;

int TxEn;
int startScan;
int DPSK;
int Atype;
int Stype;

bool isFro = false;

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
    pinMode(transDataSCL, OUTPUT);
    pinMode(transDataSDA, OUTPUT);
    pinMode(Atype2, INPUT);
    pinMode(Atype1, INPUT);
    pinMode(Atype0, INPUT);
    pinMode(TxEn, INPUT);
    pinMode(startScanpin, INPUT);
    pinMode(toFropin, INPUT);
    pinMode(DPSKpin, INPUT);
}

void checkPins() {
    TxEn = digitalRead(TxEn);
    startScan = digitialRead(startScanpin);
    DPSK = digitalRead(DPSKpin);

    if(digitalRead(toFropin) == HIGH) {
        isFro = true;
    }
    else {
        isFro = false;
    }

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
}