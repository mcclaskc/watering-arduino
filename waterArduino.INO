Code: #include <Servo.h>  
Servo waterServo;  //creates the name of your servo
int sensPin = 0;  //assignes a pin for the soil sensor
int servoPin = 3; //sets the servo pin, this must be a PWM pin
int powerPin = 2; //assignes a pin to power the sensor. optional
int wetVal = 500; //the sensor value where the soil is sufficiently wet
int dryVal = 300; //the value where the soil is dry and needs watering
int dirtVal;    //variable to store one sensor reading
int waterPosition = 170;
int waterHold = 10;
double avgDirt; //variable to store average of 10 sensor readings

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
  for(int i = 0; i < 10; i++)   //for loop to calculate average of ten soil readings
  {
    dirtVal = analogRead(sensPin);
    delay(30*1000);
    avgDirt += dirtVal;
  }
  avgDirt = avgDirt / 10.0;     //gets average value of 10 sensor readings
  Serial.print("Sensor value: "); //for debugging
  Serial.print(avgDirt);

  if(avgDirt <= dryVal)   //if the average soil value is dry
  {
    waterServo.write(waterPosition);  //start watering the plants
    while(dirtVal <= wetVal)  //while loop to keep watering until the soil is wet
    {
      dirtVal = analogRead(sensPin);
      Serial.println(avgDirt);
      delay(20);
    }
    waterServo.write(waterHold);  //stops watering the plants
    avgDirt = dirtVal;  //resets average soil value
  }
  Serial.println(avgDirt);
  delay(5*60*1000);
}