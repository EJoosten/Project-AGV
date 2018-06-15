
/*
  Bluetooh Basic: LED ON OFF - Avishkar
  Coder - Mayoogh Girish
  Website - http://bit.do/Avishkar
  Download the App : https://github.com/Mayoogh/Arduino-Bluetooth-Basic
  This program lets you to control a LED on pin 13 of arduino using a bluetooth module
*/


#include <Stepper.h>
#include <NewPing.h>

#define TRIGGER_PIN  9  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     8  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

#include <Servo.h>

Servo myservo;
int pos = 0;
int dir = 0;
int radar;
int objx[5], objy[5];
int i, j, k;
int mode = 0;
int closestDir, closestDis = 200;
int tempClosestDir, tempClosestDis = 200;
const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution for your motor

#define trig 10
#define led 12
#define echo 13
#define servo 11
#define potL A1
#define potR A0


// initialize the stepper library on pins 8 through 11:
Stepper myStepperR(stepsPerRevolution, 6, 7, 8, 9);
Stepper myStepperL(stepsPerRevolution, 2, 3, 4, 5);
volatile int Mspeed, MspeedL, MspeedR, Mcycle, navigation=1, turn, situation=1, potangleL, potangleR;
volatile float Mangle;
char data = 0;            //Variable for storing received data
void setup()
{
 myservo.attach(5);
  Serial.begin(9600);

  Serial.begin(9600);   //Sets the baud for serial data transmission
  // set the speed at 60 rpm:
  myStepperR.setSpeed(60);
  myStepperL.setSpeed(60);
  pinMode(13, OUTPUT);  //Sets digital pin 13 as output pin
}

void movement()
{
  if (Mcycle % 15 == 0) {
    if (Mangle < -1)
    {
      if (MspeedL < Mspeed + 10) {
        MspeedL++;
      }
      else if (MspeedL > Mspeed + 10) {
        MspeedL--;
      }
      if (MspeedR < Mspeed - 10) {
        MspeedR++;
      }
      else if (MspeedR > Mspeed - 10) {
        MspeedR--;
      }
    }
    else if (Mangle > 1)
    {
      if (MspeedL < Mspeed - 10) {
        MspeedL++;
      }
      else if (MspeedL > Mspeed - 10) {
        MspeedL--;
      }
      if (MspeedR < Mspeed + 10) {
        MspeedR++;
      }
      else if (MspeedR > Mspeed + 10) {
        MspeedR--;
      }
    }
    else
    {
      if (MspeedL < Mspeed) {
        MspeedL++;
      }
      else if (MspeedL > Mspeed) {
        MspeedL--;
      }
      if (MspeedR < Mspeed) {
        MspeedR++;
      }
      else if (MspeedR > Mspeed) {
        MspeedR--;
      }
    }
  }

  if (MspeedL > 0) {
    if ((Mcycle % (100 / MspeedL)) == 0)
    {
      myStepperL.step(-1);
      Mangle += 0.23;
    }
  }
  else if (MspeedL < 0) {
    if ((Mcycle % (100 / MspeedL)) == 0)
    {
      myStepperL.step(1);
      Mangle -= 0.23;
    }
  }

  if (MspeedR > 0) {
    if ((Mcycle % (100 / MspeedR)) == 0)
    {
      myStepperR.step(1);
      Mangle -= 0.23;
    }
  }
  else if (MspeedR < 0) {
    if ((Mcycle % (100 / MspeedR)) == 0)
    {
      myStepperR.step(-1);
      Mangle += 0.23;
    }
  }
  if (-2 < Mangle && Mangle < 2)
  {
    Mangle = 0;
  }
  if (Mcycle >= 100) {
    Mcycle = 0;
  }
  Mcycle++;


}
void bluetooth(){
   navigation = 1;
   if (Serial.available() > 0)     // Send data only when you receive data:
  {
    data = Serial.read();        //Read the incoming data & store into data
    switch (data)
    {
      case 'f':
        navigation = 0;
        Mangle = 0;
        Mspeed = 20;
        break;

      case 'b':
        navigation = 0;
        Mangle = 0;
        Mspeed = -20;
        break;

      case 'l':
        navigation = 0;
        Mangle = -45;
        break;
      case 'r':
        navigation = 0;
        Mangle = 45;
        break;
      case 'o':
        navigation = 0;
        Mangle = 0;
        Mspeed = 0;
        break;
      case 's':
        navigation = 1;
        break;
        

      default:
        break;


    }


  }
}

void nav(){
  switch(situation)
  {
  case 0:
  Mangle = 0;
  Mspeed = 0;
  break;

  case 1:
  Mspeed = 50;
  Mangle = 0;
  break;

  case 2:
  Mspeed = 50;
  Mangle = 2;
  break;

  case 3:
  Mspeed = 50;
  Mangle = -2;
  break;

  case 4:
  Mspeed = 0;
  Mangle = 0;
  turn = 1;
  break;

  default:
  break;
  }
  
}

void potread(){
  potangleL = analogRead(potL);
  potangleR = analogRead(potR);

  if ((potangleR + potangleL)< 1550 && potangleL < potangleR +5 && potangleR < potangleL +5){
    situation = 1;
  }
  else if(potangleL < potangleR){
    situation = 2;
  }
  else if(potangleR < potangleL){
    situation = 3;
  }
  else if((potangleR + potangleL)< 1550){
    situation = 4;
  }
}

void radarRead() {
  myservo.write(pos * 30);
  delay(1);
  radar = sonar.convert_cm(sonar.ping_median(10));
  
  if (pos == 6) {
    dir = 1;
  }
  else if (pos == 0) {
    dir = 0;
    closestDis = tempClosestDis;
    closestDir = tempClosestDir;
    tempClosestDis = 200;
  }
  if (dir == 0) {
    pos++;
  }
  else {
    pos--;
  }
  if (radar > 1){
  if (radar < tempClosestDis){
    tempClosestDir = pos;
    tempClosestDis = radar;
  }
  Serial.print(pos);
  Serial.println(radar);
  Serial.print(closestDir);
  Serial.println(closestDis);
  }
}

void loop()
{

 bluetooth();
 if(navigation==1){
  nav();
 }
 potread();
 radarRead();
 
  /* serial.print(analogRead(potL));
    Serial.print("   ");
    Serial.println(analogRead(potR));*/
  movement();
  delay(1);
}

