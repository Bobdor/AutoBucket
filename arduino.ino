#include <Adafruit_Si7021.h>
#include <Wire.h>
#include <Stepper.h>

// distance probe pins
#define trigPin0 2
#define echoPin0 3

/* water level, if used
#define trigPin1 4
#define echoPin1 5
*/

//stepper motor
#define STEPS 510 // the number of steps in one revolution of your motor (28BYJ-48)
Stepper stepper(STEPS, 6, 12, 7, 13);

// relays
#define RELAY1 4
#define RELAY2 5
#define RELAY3 8
#define RELAY4 15

//define pins for pumps
int motorPin1 = 9;
int motorPin2 = 10;
int motorPin3 = 11;

Adafruit_Si7021 sensor = Adafruit_Si7021();

// serial setup
int incomingByte=0;

//set vars for ph sensor

const int phPin = A0;
int phSensorValue = 0;
unsigned long int avgValue;
float b;
int buf[10],temp;


void setup()
{
  Serial.begin(9600);
  sensor.begin();
  Wire.begin();
  pinMode(trigPin0, OUTPUT);
  pinMode(echoPin0, INPUT);
//  uncomment for water level  
//  pinMode(trigPin1, OUTPUT);
//  pinMode(echoPin1, INPUT);
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(RELAY1,OUTPUT);
  pinMode(RELAY2,OUTPUT);
  pinMode(RELAY3,OUTPUT);
  pinMode(RELAY4,OUTPUT);  
}

void loop()
{
  /*
   This first block checks to see if there is an imput from serial and does something
   0 - pump 1ml liquid from pump on pin 9
   1 - pump 1ml liquid from pump on pin 10
   2 - pump 1ml liquid from pump on pin 11
   A - Relay 1 on -- Light
   B - Relay 1 off
   C - Relay 2 on -- Fans
   D - Relay 2 off
   E - Relay 3 on -- Air pump
   F - Relay 3 off
   G - Relay 4 on -- Water pump
   H - Relay 4 off
   I - Relay 5 on --
   J - Relay 5 off
   K - Relay 6 on
   L - Relay 6 off
   M - Relay 7 on
   N - Relay 8 off
   O - Raise light
   P - Lower light

  */

  if (Serial.available() > 0 ){
     incomingByte = Serial.read();
     if (incomingByte == 48){
      Serial.println(incomingByte);
      analogWrite(motorPin1, 255);
      delay(1000); // set how long you want the motor to run... 1000 = aprox 1ml
      analogWrite(motorPin1, 0);
     }
     if (incomingByte == 49){
      Serial.println(incomingByte);
      analogWrite(motorPin2, 255);
      delay(1000); // set how long you want the motor to run... 1000 = aprox 1ml
      analogWrite(motorPin2, 0);
     }
     if (incomingByte == 50){
      Serial.println(incomingByte);
      analogWrite(motorPin3, 255);
      delay(1000); // set how long you want the motor to run... 1000 = aprox 1ml
      analogWrite(motorPin3, 0);
     }
     if (incomingByte == 65){
      Serial.println(incomingByte);
      digitalWrite(RELAY1,HIGH);
     }
      if (incomingByte == 66){
      Serial.println(incomingByte);
      digitalWrite(RELAY1,LOW);
     }
      if (incomingByte == 67){
      Serial.println(incomingByte);
      digitalWrite(RELAY2,HIGH);
     }
      if (incomingByte == 68){
      Serial.println(incomingByte);
      digitalWrite(RELAY2,LOW);
     }
      if (incomingByte == 69){
      Serial.println(incomingByte);
      digitalWrite(RELAY3,HIGH);
     }
      if (incomingByte == 70){
      Serial.println(incomingByte);
      digitalWrite(RELAY3,LOW);
     }    
      if (incomingByte == 71){
      Serial.println(incomingByte);
      digitalWrite(RELAY4,HIGH);
     }
      if (incomingByte == 72){
      Serial.println(incomingByte);
      digitalWrite(RELAY4,LOW);
     }           
      if (incomingByte == 79){
      Serial.println(incomingByte);
      stepper.setSpeed(10); // 10 rpm
      stepper.step(STEPS); // do 400 steps -- corresponds to one revolution in one minute
     }
      if (incomingByte == 80){
      Serial.println(incomingByte);        
      stepper.setSpeed(10); // 10 rpm
      stepper.step(-STEPS); // do 400 steps -- corresponds to one revolution in one minute
     }

      else{
       //Serial.println(incomingByte);
      }
  }
  else {





  //plant distance probe
  long duration0, plantDistance;
  digitalWrite(trigPin0, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin0, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin0, LOW);
  duration0 = pulseIn(echoPin0, HIGH);
  plantDistance = (duration0/2) / 29.1;

  /*water distance probe
  long duration1, waterDistance;
  digitalWrite(trigPin1, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);
  waterDistance = (duration1/2) / 29.1;
*/


  float airTemp;
  float humidity;
  double T,p0,a;

  /* uncomment for turbidity
  int turValue = analogRead(A1);
  float turVolt = turValue * (5.0 / 1024.0);
  */

  //ph

  for(int i=0;i<10;i++)
   {
    buf[i]=analogRead(phPin);
    delay(10);
   }
   for(int i=0;i<9;i++)
   {
    for(int j=i+1;j<10;j++)
    {
     if(buf[i]>buf[j])
     {
      temp=buf[i];
      buf[i]=buf[j];
      buf[j]=temp;
     }
    }
   }
   avgValue=0;
   for(int i=2;i<8;i++)
   avgValue+=buf[i];
   float pHVol=(float)avgValue*5.0/1024/6;
   float phValue = -5.70 * pHVol + 21.34;

//temperature


  airTemp = sensor.readTemperature();
  humidity = sensor.readHumidity();
  delay(humidity);
    // Print out the measurements :
  Serial.print((9.0/5.0)*airTemp+32.0,2);
  Serial.print(':');
  Serial.print(humidity);
  Serial.print(':');
  Serial.print(phValue);
//  Serial.print(':');
//  Serial.print(turVolt);
  Serial.print(':');
  Serial.println(plantDistance);
//  Serial.print(':');
//  Serial.println(waterDistance);

  delay(100);  // Pause for 10 seconds.
  }
}
