#include <Servo.h>


#define switchpin 0 // digital
#define TempPin 0 // analog
#define Buzzer 5 // digital
#define MoistPin 1 // analog
#define ServoPin 7 // digital


Servo Servo1;
int value; //switch HIGH/LOW
double angle = 45; //Servo  initial angle
int offtime=100; //delay time
float voltage =5.0;

void setup() 
{
  Servo1.attach(ServoPin);
  Servo1.write(angle);
  pinMode(switchpin, INPUT); 	//Slideswitch
  pinMode(TempPin,INPUT);		//Temp sensor input
  pinMode(Buzzer, OUTPUT);		//buzzer
  pinMode(MoistPin,INPUT);		// Soil moisture sensor
  Serial.begin(9600);
}

void loop() 
{
  //Switch control
  value = digitalRead(switchpin);
  if(value == HIGH) {
    
    //SERVO  movements
    for(int angle=45; angle<90; angle++){ //clockwise
    	Servo1.write(angle); 	//rotate pin of servo motor (1m) 
    	delay(50); 				//for 0.05 second (1m)
  	}
  	for(int angle=90; angle>0; angle--){ //anti-clockwise
    	Servo1.write(angle);
    	delay(50); 
  	}
  	for(int angle=0; angle<45; angle++){
      	Servo1.write(angle);
      	delay(50);
  	}
  	delay(offtime);
  }
  else {    
    Servo1.write(45);   
    delay(offtime);
  }
  
  //Temperature sensor code
  int sensorRead = analogRead(TempPin);
  float voltageOut = sensorRead * (voltage / 1024.0);
  float temp = (voltageOut - 0.5) * 100;
  
  if(temp < 36.8 || temp > 37.3){
  	Serial.print("Not Normal temperature\n");
    tone(Buzzer, 500);
  }
  else{
    Serial.print("Normal Temperature\n");
    noTone(Buzzer);
  }
  
  Serial.print("Temperature : ");
  Serial.print(temp);
  Serial.print("\n");
  
  
  //Fluid detection code
  int Moisture=analogRead(MoistPin);
  if(Moisture>0)
    tone(Buzzer, 220);
  else
    noTone(Buzzer);
  Serial.print("Moisture val : ");
  Serial.print(Moisture);
  Serial.print("\n");
}
