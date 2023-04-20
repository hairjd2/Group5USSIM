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

bool isFro = false;

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
// int stationType[3][3] = {{-10, }, {-10, }, {3, }}

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