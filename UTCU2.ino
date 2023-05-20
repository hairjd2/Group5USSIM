// Pin number
//Antenna Type Pins
const int Atype2 = 13;
const int Atype1 = 12;
const int Atype0 = 11;
//Station Type Pins
// const int Stype1 = 10;
//const int Stype0 = 9;
//Other Pins
const int ToAndFro = 7;
const int DPSK = 1;
const int transmitEnable = 10;


//Function Sets Pin Mode
void setup() {
  // Set Pin Mode
  Serial.begin(9600);
  pinMode(Atype2, OUTPUT);
  pinMode(Atype1, OUTPUT);
  pinMode(Atype0, OUTPUT);
  pinMode(transmitEnable, OUTPUT);
  pinMode(ToAndFro, OUTPUT);
  pinMode(DPSK, OUTPUT);
}

int dataWord = 0;
//One Loop Of this Function is the 615ms max full sequence
void loop() {
  // basicDataWord1();
  // basicDataWord2();
  // basicDataWord3();
  // basicDataWord4();
  // basicDataWord5();
  // basicDataWord6();
  // auxDataWord();
  azfunction();
  // elfunction();
  // bazfunction();

  //dataWordSel(dataWord % 6);
  delayMicrosecond(20);
  /*
  //This Function Will Be Used to call the sequence 1 and 2 functions
  //which will then call the individual antenna functions
  sequenceOne();
  sequenceTwo();
  //Two Word delayMicrosecond (32 Bits)
  delayMicrosecond(2.048);
  sequenceOne();
  //Three Word delayMicrosecond (48 Bits)
  delayMicrosecond(3.072);
  sequenceTwo();
  sequenceOne();
  //Three Word delayMicrosecond (48 Bits)
  delayMicrosecond(3.072);
  sequenceTwo();

 //One Word delayMicrosecond
  delayMicrosecond(1.024);
  sequenceOne();
  sequenceTwo();
  //Three Word delayMicrosecond
  delayMicrosecond(3.072);

  //~604.288 ms cycle + cpu delayMicrosecond?
  */
}

void dataWordSel(int num){
  digitalWrite(transmitEnable,HIGH);
  if(num == 0){
    basicDataWord1();
  }if(num == 1){
    basicDataWord2();
  }
  if(num == 2){
    basicDataWord3();
  }if(num == 3){
    basicDataWord4();
  }if(num == 4){
    basicDataWord5();
  }if(num == 5){
    basicDataWord6();
  }
  digitalWrite(transmitEnable,LOW);
  dataWord ++;
}

//Sequence One: Commented Areas Represent Areas im unsure about
//We Have to Fit the Data word functionality into unused spaces
void sequenceOne(){
  elfunction();
  dataWordSel(dataWord % 6);
  //Blank
  azfunction();
  //flare/blank
  dataWordSel(dataWord % 6);
  elfunction();
  //****Blank
  bkAZfunction();
  dataWordSel(dataWord % 6);
  //***Note(2)
  dataWordSel(dataWord % 6);
  elfunction();
  //flare/blank
  auxDataWord();
}

//Sequence Two: Commented Areas Represent Areas im unsure about
//We Have to Fit the Data word functionality into unused spaces
void sequenceTwo(){
  elfunction();

  //flare/blank
  dataWordSel(dataWord % 6);
  azfunction();
  //flare/blank
  dataWordSel(dataWord % 6);
  elfunction();
  //****Growth Area(18.2ms max)
  delayMicrosecond(18.2);
  dataWordSel(dataWord % 6);
  elfunction();
  //flare/blank
  dataWordSel(dataWord % 6);
}


//Azimuth Function: Function outputs data for Azimuth function, at least 15.9ms to complete
void azfunction(){
  //Set Station Type Bits 2'b10 for AZ
  //digitalWrite(Stype1, HIGH);
  //digitalWrite(Stype0, LOW);
  digitalWrite(transmitEnable,HIGH);
  //Set Antenna Type to 3'd0 for Iden/Data Funtion
  digitalWrite(Atype2, LOW);
  digitalWrite(Atype1, LOW);
  digitalWrite(Atype0, LOW);
  Serial.println("Iden/Data Funtion");

  //Send Preamble Accross DPSK line
  Serial.println("Sending Preamble");

  //Carrier Acquisition Period
  digitalWrite(DPSK, LOW);
  delayMicroseconds(83200);//0.832ms for 0.064*13bits
  Serial.println("Carrier Acquisition Complete");

  //Send Time Sync/Barker Code//InDPSK
  digitalWrite(DPSK, HIGH);
  delayMicroseconds(6400);// 0.192ms for 0.064 * 1bits
  digitalWrite(DPSK, HIGH);
  delayMicroseconds(6400);// 0.192ms for 0.064 * 1bits
  digitalWrite(DPSK, HIGH);
  delayMicroseconds(6400);// 0.192ms for 0.064 * 1bits
  digitalWrite(DPSK, LOW);
  delayMicroseconds(6400);//0.064ms for 0.064*1bits
  digitalWrite(DPSK, HIGH);
  delayMicroseconds(6400);//0.128ms for 0.064*2bits
  Serial.println("Time Sync/Barker Code Complete");

  //Send Function ID//AZ Function ID
  digitalWrite(DPSK, LOW);
  delayMicroseconds(6400);//0.128ms for 0.064*2bits
  digitalWrite(DPSK, LOW);
  delayMicroseconds(6400);//0.128ms for 0.064*2bits
  digitalWrite(DPSK, HIGH);
  delayMicroseconds(6400);//0.128ms for 0.064*2bits
  digitalWrite(DPSK, HIGH);
  delayMicroseconds(6400);//0.128ms for 0.064*2bits
  digitalWrite(DPSK, LOW);
  delayMicroseconds(6400);//0.128ms for 0.064*2bits
  digitalWrite(DPSK, LOW);
  delayMicroseconds(6400);//0.128ms for 0.064*2bits
  digitalWrite(DPSK, HIGH);
  delayMicroseconds(6400);//0.192ms for 0.064*3bits
  Serial.println("Function ID Complete");

  //Antenna Select 
  digitalWrite(DPSK, LOW);
  delayMicroseconds(38400); //0.384ms for 0.064*6bits
  Serial.println("Antenna Select Complete");

  //Left OCI
  //3'b001
  digitalWrite(Atype2,LOW);
  digitalWrite(Atype1,LOW);
  digitalWrite(Atype0,HIGH);
  delayMicroseconds(12800); //0.128ms for 0.064 *2 bits/clk cycles
  Serial.println("Left OCI Complete");

  //Rear OCI
  //3'b010
  digitalWrite(Atype2,LOW);
  digitalWrite(Atype1,HIGH);
  digitalWrite(Atype0,LOW);
  delayMicroseconds(12800); //0.128ms for 0.064 *2 bits/clk cycles
  Serial.println("Rear/Upper OCI Complete");

  //Right OCI
  // 3'b011
  digitalWrite(Atype2,LOW);
  digitalWrite(Atype1,HIGH);
  digitalWrite(Atype0,HIGH);
  delayMicroseconds(12800); //0.128ms for 0.064 *2 bits/clk cycles
  Serial.println("Right OCI Complete");

  //Skip Morse Code???
  digitalWrite(DPSK, LOW);
  delayMicroseconds(6400);//0.064ms for 0.064*1bits
  Serial.println("Morse Code Complete");

  //Skipping Test Pulse
  digitalWrite(DPSK, LOW);
  delayMicroseconds(6400);//0.064ms for 0.064*1bits
  Serial.println("Test Pulse Complete");

  //To Scanning Beam
  //Turn Beam on
  //3'b100
  digitalWrite(Atype2,HIGH);
  digitalWrite(Atype1,LOW);
  digitalWrite(Atype0,LOW);

  //Set ToAndFro High for To Scan
  digitalWrite(ToAndFro,LOW);

  //Scan for 6.2 ms
  delayMicroseconds(620000);
  Serial.println("Scan To Complete");

  //Turn Off Scanning Beam
  //3'b101 
  digitalWrite(Atype2,HIGH);
  digitalWrite(Atype1,LOW);
  digitalWrite(Atype0,HIGH);
  delayMicroseconds(30000);
  Serial.println("Turn off");

  //Fro Scanning Beam

  //Set ToAndFro LOW for Fro Scan
  digitalWrite(ToAndFro,HIGH);

  //Turn Antenna Back On
  //3'b100
  digitalWrite(Atype2,HIGH);
  digitalWrite(Atype1,LOW);
  digitalWrite(Atype0,LOW);

  //Scan For 6.2ms
  delayMicroseconds(620000);
  Serial.println("Scan Fro Complete");

  //15.9 ms sequence Complete 
  digitalWrite(transmitEnable,LOW);
  //Set Antenna Type to 3'd0 for Iden/Data Funtion
  digitalWrite(Atype2, HIGH);
  digitalWrite(Atype1, LOW);
  digitalWrite(Atype0, HIGH);
  //Scan Complete
  delayMicroseconds(876000);
  Serial.println("Scan Complete");
  Serial.println("Sequence Complete");
}


//Elevation Function: Function outputs data for Elevation function
void elfunction(){
    //Set Station Type Bits 2'b10 for AZ
  //digitalWrite(Stype1, HIGH);
  //digitalWrite(Stype0, LOW);
  digitalWrite(transmitEnable,HIGH);
  //Set Antenna Type to 3'd0 for Iden/Data Funtion
  digitalWrite(Atype2, LOW);
  digitalWrite(Atype1, LOW);
  digitalWrite(Atype0, LOW);
  Serial.println("Iden/Data Funtion");

  //Send Preamble Accross DPSK line
  Serial.println("Sending Preamble");

  //Carrier Acquisition Period
  digitalWrite(DPSK, LOW);
  delayMicroseconds(83200);//0.832ms for 0.064*13bits
  Serial.println("Carrier Acquisition Complete");

  //Send Time Sync/Barker Code//InDPSK
  digitalWrite(DPSK, HIGH);
  delayMicroseconds(6400);// 0.192ms for 0.064 * 1bits
  digitalWrite(DPSK, HIGH);
  delayMicroseconds(6400);// 0.192ms for 0.064 * 1bits
  digitalWrite(DPSK, HIGH);
  delayMicroseconds(6400);// 0.192ms for 0.064 * 1bits
  digitalWrite(DPSK, LOW);
  delayMicroseconds(6400);//0.064ms for 0.064*1bits
  digitalWrite(DPSK, HIGH);
  delayMicroseconds(6400);//0.128ms for 0.064*2bits
  Serial.println("Time Sync/Barker Code Complete");

  //Send Function ID//EL Function ID
  digitalWrite(DPSK, HIGH);
  delayMicroseconds(6400);//0.128ms for 0.064*2bits
  digitalWrite(DPSK, HIGH);
  delayMicroseconds(6400);//0.128ms for 0.064*2bits
  digitalWrite(DPSK, LOW);
  delayMicroseconds(6400);//0.128ms for 0.064*2bits
  digitalWrite(DPSK, LOW);
  delayMicroseconds(6400);//0.128ms for 0.064*2bits
  digitalWrite(DPSK, LOW);
  delayMicroseconds(6400);//0.128ms for 0.064*2bits
  digitalWrite(DPSK, LOW);
  delayMicroseconds(6400);//0.128ms for 0.064*2bits
  digitalWrite(DPSK, HIGH);
  delayMicroseconds(6400);//0.192ms for 0.064*3bits
  Serial.println("Function ID Complete");

  //Antenna Select 
  digitalWrite(DPSK, LOW);
  delayMicroseconds(38400); //0.384ms for 0.064*6bits
  Serial.println("Antenna Select Complete");

  //Left OCI
  //3'b001
  digitalWrite(Atype2,LOW);
  digitalWrite(Atype1,LOW);
  digitalWrite(Atype0,HIGH);
  delayMicroseconds(12800); //0.128ms for 0.064 *2 bits/clk cycles
  Serial.println("Left OCI Complete");

  //Rear OCI
  //3'b010
  digitalWrite(Atype2,LOW);
  digitalWrite(Atype1,HIGH);
  digitalWrite(Atype0,LOW);
  delayMicroseconds(12800); //0.128ms for 0.064 *2 bits/clk cycles
  Serial.println("Rear/Upper OCI Complete");

  //Right OCI
  // 3'b011
  digitalWrite(Atype2,LOW);
  digitalWrite(Atype1,HIGH);
  digitalWrite(Atype0,HIGH);
  delayMicroseconds(12800); //0.128ms for 0.064 *2 bits/clk cycles
  Serial.println("Right OCI Complete");

  //Skip Morse Code???
  digitalWrite(DPSK, LOW);
  delayMicroseconds(6400);//0.064ms for 0.064*1bits
  Serial.println("Morse Code Complete");

  //Skipping Test Pulse
  digitalWrite(DPSK, LOW);
  delayMicroseconds(6400);//0.064ms for 0.064*1bits
  Serial.println("Test Pulse Complete");

  //To Scanning Beam
  //Turn Beam on
  //3'b100
  digitalWrite(Atype2,HIGH);
  digitalWrite(Atype1,LOW);
  digitalWrite(Atype0,LOW);

  //Set ToAndFro High for To Scan
  digitalWrite(ToAndFro,LOW);

  //Scan for 6.2 ms
  delayMicroseconds(620000);
  Serial.println("Scan To Complete");

  //Turn Off Scanning Beam
  //3'b101 
  digitalWrite(Atype2,HIGH);
  digitalWrite(Atype1,LOW);
  digitalWrite(Atype0,HIGH);
  delayMicroseconds(30000);
  Serial.println("Turn off");

  //Fro Scanning Beam

  //Set ToAndFro LOW for Fro Scan
  digitalWrite(ToAndFro,HIGH);

  //Turn Antenna Back On
  //3'b100
  digitalWrite(Atype2,HIGH);
  digitalWrite(Atype1,LOW);
  digitalWrite(Atype0,LOW);

  //Scan For 6.2ms
  delayMicroseconds(620000);
  Serial.println("Scan Fro Complete");

  //15.9 ms sequence Complete 
  digitalWrite(transmitEnable,LOW);
  //Set Antenna Type to 3'd0 for Iden/Data Funtion
  digitalWrite(Atype2, HIGH);
  digitalWrite(Atype1, LOW);
  digitalWrite(Atype0, HIGH);
  //Scan Complete
  delayMicroseconds(876000);
  Serial.println("Scan Complete");
  Serial.println("Sequence Complete");
}



// BACK AZ FUCNTION
void bkAZfunction(){
  //Set Station Type Bits 2'b10 for AZ
  //digitalWrite(Stype1, HIGH);
  //digitalWrite(Stype0, LOW);
  digitalWrite(transmitEnable,HIGH);
  //Set Antenna Type to 3'd0 for Iden/Data Funtion
  digitalWrite(Atype2, LOW);
  digitalWrite(Atype1, LOW);
  digitalWrite(Atype0, LOW);
  Serial.println("Iden/Data Funtion");

  //Send Preamble Accross DPSK line
  Serial.println("Sending Preamble");

  //Carrier Acquisition Period
  digitalWrite(DPSK, LOW);
  delayMicroseconds(83200);//0.832ms for 0.064*13bits
  Serial.println("Carrier Acquisition Complete");

  //Send Time Sync/Barker Code//InDPSK
  digitalWrite(DPSK, HIGH);
  delayMicroseconds(6400);// 0.192ms for 0.064 * 1bits
  digitalWrite(DPSK, HIGH);
  delayMicroseconds(6400);// 0.192ms for 0.064 * 1bits
  digitalWrite(DPSK, HIGH);
  delayMicroseconds(6400);// 0.192ms for 0.064 * 1bits
  digitalWrite(DPSK, LOW);
  delayMicroseconds(6400);//0.064ms for 0.064*1bits
  digitalWrite(DPSK, HIGH);
  delayMicroseconds(6400);//0.128ms for 0.064*2bits
  Serial.println("Time Sync/Barker Code Complete");

  //Send Function ID//BAZ Function ID
  digitalWrite(DPSK, HIGH);
  delayMicroseconds(6400);//0.128ms for 0.064*2bits
  digitalWrite(DPSK, LOW);
  delayMicroseconds(6400);//0.128ms for 0.064*2bits
  digitalWrite(DPSK, LOW);
  delayMicroseconds(6400);//0.128ms for 0.064*2bits
  digitalWrite(DPSK, HIGH);
  delayMicroseconds(6400);//0.128ms for 0.064*2bits
  digitalWrite(DPSK, LOW);
  delayMicroseconds(6400);//0.128ms for 0.064*2bits
  digitalWrite(DPSK, LOW);
  delayMicroseconds(6400);//0.128ms for 0.064*2bits
  digitalWrite(DPSK, HIGH);
  delayMicroseconds(6400);//0.192ms for 0.064*3bits
  Serial.println("Function ID Complete");

  //Antenna Select 
  digitalWrite(DPSK, LOW);
  delayMicroseconds(38400); //0.384ms for 0.064*6bits
  Serial.println("Antenna Select Complete");

  //Left OCI
  //3'b001
  digitalWrite(Atype2,LOW);
  digitalWrite(Atype1,LOW);
  digitalWrite(Atype0,HIGH);
  delayMicroseconds(12800); //0.128ms for 0.064 *2 bits/clk cycles
  Serial.println("Left OCI Complete");

  //Rear OCI
  //3'b010
  digitalWrite(Atype2,LOW);
  digitalWrite(Atype1,HIGH);
  digitalWrite(Atype0,LOW);
  delayMicroseconds(12800); //0.128ms for 0.064 *2 bits/clk cycles
  Serial.println("Rear/Upper OCI Complete");

  //Right OCI
  // 3'b011
  digitalWrite(Atype2,LOW);
  digitalWrite(Atype1,HIGH);
  digitalWrite(Atype0,HIGH);
  delayMicroseconds(12800); //0.128ms for 0.064 *2 bits/clk cycles
  Serial.println("Right OCI Complete");

  //Skip Morse Code???
  digitalWrite(DPSK, LOW);
  delayMicroseconds(6400);//0.064ms for 0.064*1bits
  Serial.println("Morse Code Complete");

  //Skipping Test Pulse
  digitalWrite(DPSK, LOW);
  delayMicroseconds(6400);//0.064ms for 0.064*1bits
  Serial.println("Test Pulse Complete");

  //To Scanning Beam
  //Turn Beam on
  //3'b100
  digitalWrite(Atype2,HIGH);
  digitalWrite(Atype1,LOW);
  digitalWrite(Atype0,LOW);

  //Set ToAndFro High for To Scan
  digitalWrite(ToAndFro,LOW);

  //Scan for 6.2 ms
  delayMicroseconds(620000);
  Serial.println("Scan To Complete");

  //Turn Off Scanning Beam
  //3'b101 
  digitalWrite(Atype2,HIGH);
  digitalWrite(Atype1,LOW);
  digitalWrite(Atype0,HIGH);
  delayMicroseconds(30000);
  Serial.println("Turn off");

  //Fro Scanning Beam

  //Set ToAndFro LOW for Fro Scan
  digitalWrite(ToAndFro,HIGH);

  //Turn Antenna Back On
  //3'b100
  digitalWrite(Atype2,HIGH);
  digitalWrite(Atype1,LOW);
  digitalWrite(Atype0,LOW);

  //Scan For 6.2ms
  delayMicroseconds(620000);
  Serial.println("Scan Fro Complete");

  //15.9 ms sequence Complete 
  digitalWrite(transmitEnable,LOW);
  //Set Antenna Type to 3'd0 for Iden/Data Funtion
  digitalWrite(Atype2, HIGH);
  digitalWrite(Atype1, LOW);
  digitalWrite(Atype0, HIGH);
  //Scan Complete
  delayMicroseconds(876000);
  Serial.println("Scan Complete");
  Serial.println("Sequence Complete");
}
//11.9 sec sequence



void basicDataWord1(){
  int nums [] = {0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,0,0,1,1,0,0,0,0,1,1,0,1,0,1,1,1,0,1,0,0,0,1,0,1,0,1,0,1};
  for(int i = 0; i < sizeof(nums)/sizeof(nums[0]);i++){
    if(nums[i] == 1){
      digitalWrite(DPSK,HIGH);
    }else{
      digitalWrite(DPSK,LOW);
    }
    delayMicroseconds(6400);//0.064ms for 0.064*1bits
  }
}


void basicDataWord2(){
  int nums [] = {0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,0,0,1,0,1,0,1,0,0,0,1,1,1,1,1,0,1,1,1,0,0,1,1,1,0,0,0,0};
  for(int i = 0; i < sizeof(nums)/sizeof(nums[0]);i++){
    if(nums[i] == 1){
      digitalWrite(DPSK,HIGH);
    }else{
      digitalWrite(DPSK,LOW);
    }
    delayMicroseconds(6400);//0.064ms for 0.064*1bits
  }
}

void basicDataWord3(){
  int nums [] = {0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,0,1,1,0,1,0,1,0,0,0,1,1,1,1,1,0,1,1,1,0,0,1,1,1,0,0,0,0};
  for(int i = 0; i < sizeof(nums)/sizeof(nums[0]);i++){
    if(nums[i] == 1){
      digitalWrite(DPSK,HIGH);
    }else{
      digitalWrite(DPSK,LOW);
    }
    delayMicroseconds(6400);//0.064ms for 0.064*1bits
  }

}

void basicDataWord4(){
  int nums [] = {0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,0,1,0,0,0,0,1,0,1,0,1,1,0,1,1,0,1,1,0,1,0,1,0,1,0,0,0,0};
  for(int i = 0; i < sizeof(nums)/sizeof(nums[0]);i++){
    if(nums[i] == 1){
      digitalWrite(DPSK,HIGH);
    }else{
      digitalWrite(DPSK,LOW);
    }
    delayMicroseconds(6400);//0.064ms for 0.064*1bits
  }
}

void basicDataWord5(){
  int nums [] = {0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,0,1,0,0,1,0,1,0,1,0,1,1,0,0,1,0,1,1,1,1,0,1,0,1,0,0,0,0};
  for(int i = 0; i < sizeof(nums)/sizeof(nums[0]);i++){
    if(nums[i] == 1){
      digitalWrite(DPSK,HIGH);
    }else{
      digitalWrite(DPSK,LOW);
    }
    delayMicroseconds(6400);//0.064ms for 0.064*1bits
  }
}

void basicDataWord6(){
  int nums [] = {0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,1,1,0,0,1,1,1,0,1,0,1,0,0,1,1,0,0,1,0,1,0,1,0,1,0,0,0,0};
  for(int i = 0; i < sizeof(nums)/sizeof(nums[0]);i++){
    if(nums[i] == 1){
      digitalWrite(DPSK,HIGH);
    }else{
      digitalWrite(DPSK,LOW);
    }
    delayMicroseconds(6400);//0.064ms for 0.064*1bits
  }
}

void auxDataWord(){
  //Function Preamble
  digitalWrite(DPSK,LOW);
  delayMicrosecond(83200);// 0.064*13bits
  digitalWrite(DPSK,HIGH);
  delayMicrosecond(19200); //0.064*three bits
  digitalWrite(DPSK,LOW);
  delayMicrosecond(6400);
  digitalWrite(DPSK,HIGH);
  delayMicrosecond(25600);//0.064*four bits
  digitalWrite(DPSK,LOW);
  delayMicrosecond(12800); //0.064*two bits
  digitalWrite(DPSK,HIGH);
  delayMicrosecond(6400);
  digitalWrite(DPSK,LOW);
  delayMicrosecond(6400);
  digitalWrite(DPSK,HIGH);
  delayMicrosecond(6400);
  digitalWrite(DPSK,LOW);
  delayMicrosecond(6400);
  //Function Preamble Complete
	digitalWrite(DPSK,LOW);
	delayMicrosecond(25600);//0.064*4
	digitalWrite(DPSK,HIGH);
	delayMicrosecond(32000);//0.064*5
	digitalWrite(DPSK,LOW);
	delayMicrosecond(12800); //0.064*2
	digitalWrite(DPSK,HIGH);
	delayMicrosecond(12800); //0.064*2
	digitalWrite(DPSK,LOW);
  	delayMicrosecond(6400);
  	digitalWrite(DPSK,HIGH);
  	delayMicrosecond(6400);
	digitalWrite(DPSK,LOW);
  	delayMicrosecond(44800); //0.064*7
  	digitalWrite(DPSK,HIGH);
  	delayMicrosecond(19200); //0.064*3
  	digitalWrite(DPSK,LOW);
	delayMicrosecond(12800); //0.064*2
	digitalWrite(DPSK,HIGH);
  	delayMicrosecond(6400); //0.064*10
  	digitalWrite(DPSK,LOW);
	delayMicrosecond(12800); //0.064*2
	digitalWrite(DPSK,HIGH);
  	delayMicrosecond(6400);
  	digitalWrite(DPSK,LOW);
	delayMicrosecond(19200); //0.064*3
	digitalWrite(DPSK,HIGH);
  	delayMicrosecond(6400);
  	digitalWrite(DPSK,LOW);
  	delayMicrosecond(6400);
  	digitalWrite(DPSK,HIGH);
	delayMicrosecond(12800); //0.064*2
	digitalWrite(DPSK,LOW);
	delayMicrosecond(19200); //0.064*3
	digitalWrite(DPSK,HIGH);
	delayMicrosecond(12800); //0.064*2
	digitalWrite(DPSK,LOW);
	delayMicrosecond(12800); //0.064*2
	digitalWrite(DPSK,HIGH);
	delayMicrosecond(25600); //0.064*4
	digitalWrite(DPSK,LOW);
	delayMicrosecond(38400); //0.064*6  
}