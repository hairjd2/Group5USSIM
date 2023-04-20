const int transDataSCL = 27;
const int transDataSDA = 26;
const int Atype2 = 13;
const int Atype1 = 12; // seems to be negated
const int Atype0 = 11;
const int TxEnpin = 10;
const int startScanpin = 9;
const int toFropin = 7;
const int DPSKpin = 1;

int TxEn;
int startScan;
int DPSK;
int Atype;
int Stype;

bool isFro = false;

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
// int stationType[3][3] = {{-10, }, {-10, }, {3, }}

void setup() {
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