// Nkosi & Seth
// MLS Signal Generation
// Arduino Nano Board

/*
Required Functionality:
    - Sine wave generation
*/

void setup(){
    
const int ARRAY_SIZE = 256;
const int NEGATION_MULTIPLIER = -1;
const int QUARTER_DEGREE_VAL = 90;
const double PI = 3.14159265;
float a_type[6] = {1, 0.5, 0.25, 0.125, 10, 0};
float s_type[3] = {1.5, 2, 2};
double data_points[ARRAY_SIZE] = {0};
double data_point_multiplier = QUARTER_DEGREE_VAL/ARRAY_SIZE;
double amplitude_multiplier = 1;

}

void loop(){
    /populate array
for(int i = 0; i < ARRAY_SIZE; i++){
	ARRAY_SIZE[i] = i;
}

//pins for output siganls
//use digital pins and wire up to DAC
//int Atype_1 = 


//do whateve we have to do divide sine wave and populate array here

//generate first quarter of wave
for (int i = 0; i < ARRAY_SIZE; i++){
	pulse_out(data_points[i * data_point_multiplier]);
}

//generate second quarter of wave
for (int i = ARRAY_SIZE; i > 0; i--){
	pulse_out(data_points[i * data_point_multiplier]);
}

//generate third quarter of wave
for (int i = 0; i < ARRAY_SIZE; i++){
	pulse_out(NEGATION_MULTIPLIER * data_points[i * data_point_multiplier]);
}

//generate fourth quarter of wave
for (int i = ARRAY_SIZE; i > 0; i--){
	pulse_out(NEGATION_MULTIPLIER * data_points[i * data_point_multiplier]);
}

//615 mili secs between each demo

return 0;

}
