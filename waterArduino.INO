#include <Servo.h>  
Servo waterServo;  //creates the name of your servo
int sensPin = 0;  //assignes a pin for the soil sensor
int servoPin = 3; //sets the servo pin, this must be a PWM pin
int powerPin = 2; //assignes a pin to power the sensor. optional
//int wetVal = 500; //the sensor value where the soil is sufficiently wet
//int dryVal = 300; //the value where the soil is dry and needs watering
int dirtVal;    //variable to store one sensor reading
int waterPosition = 170;
int waterHold = 10;
double avgDirt; //variable to store average of 10 sensor readings
//long loopDelay = 300000; // 5 minutes in milliseconds
//int numReads = 10;

// below are test values to make debugging easier / faster:
long loopDelay = 3000; // 3 seconds in milliseconds
int numReads = 1;
int wetVal = 850; //the sensor value where the soil is sufficiently wet
int dryVal = 700; //the value where the soil is dry and needs watering

void setup() 
{
  Serial.begin(9600);   //serial monitor for debugging purposes
  waterServo.attach(servoPin);  //sets the servo pin as output
  pinMode(sensPin, INPUT);  //sets the sensor pin as input
  pinMode(powerPin, OUTPUT);
  delay(10);
  digitalWrite(powerPin, HIGH); //provides power to the sensor
}

void loop() 
{
  avgDirt = analogRead(sensPin);
  Serial.print("first dirt value: ");
  Serial.println(avgDirt);
  for(int i = 0; i < numReads; i++)   //for loop to calculate average of ten soil readings
  {
    dirtVal = analogRead(sensPin);
//    delay(30*1000);
    Serial.print("partial dirt value: ");
    Serial.println(dirtVal);
    avgDirt += dirtVal;
    Serial.print("sum value: ");
    Serial.println(avgDirt);
  }
  avgDirt = avgDirt / (numReads + 1.0);     //gets average value of 10 sensor readings
  Serial.print("avgDirt before water: "); //for debugging
  Serial.println(avgDirt);

  if(avgDirt <= dryVal)   //if the average soil value is dry
  {
    waterServo.write(waterPosition);  //start watering the plants
    while(dirtVal <= wetVal)  //while loop to keep watering until the soil is wet
    {
      dirtVal = analogRead(sensPin);
      Serial.print("dirtVal during water: ");
      Serial.println(dirtVal);
      delay(2000);
    }
    waterServo.write(waterHold);  //stops watering the plants
    avgDirt = dirtVal;  //resets average soil value
  }
  Serial.print("final avgDirt: ");
  Serial.println(avgDirt);
  delay(loopDelay);
}