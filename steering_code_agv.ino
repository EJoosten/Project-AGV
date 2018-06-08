/*
  Bluetooh Basic: LED ON OFF - Avishkar
  Coder - Mayoogh Girish
  Website - http://bit.do/Avishkar
  Download the App : https://github.com/Mayoogh/Arduino-Bluetooth-Basic
  This program lets you to control a LED on pin 13 of arduino using a bluetooth module
*/


#include <Stepper.h>

const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution for your motor

// initialize the stepper library on pins 8 through 11:
Stepper myStepperR(stepsPerRevolution, 6, 7, 8, 9);
Stepper myStepperL(stepsPerRevolution, 2, 3, 4, 5);
volatile int Mspeed, MspeedL, MspeedR, Mcycle;
volatile float Mangle;
char data = 0;            //Variable for storing received data
void setup()
{
  Serial.begin(9600);   //Sets the baud for serial data transmission
  // set the speed at 60 rpm:
  myStepperR.setSpeed(60);
  myStepperL.setSpeed(60);
  pinMode(13, OUTPUT);  //Sets digital pin 13 as output pin
}

void movement()
{
  if (Mangle < -1)
  {
    MspeedL = (Mspeed + 10);
    MspeedR = (Mspeed - 10);
  }
  else if (Mangle > 1)
  {
    MspeedL = (Mspeed - 10);
    MspeedR = (Mspeed + 10);
  } 
  else
  {
    MspeedL = Mspeed;
    MspeedR = Mspeed;
  }

  if (MspeedL > 0) {
    if ((Mcycle % (100 / MspeedL)) == 0)
    {
      myStepperL.step(-1);
      Mangle+= 0.23;
    }
  }
  else if (MspeedL < 0) {
    if ((Mcycle % (100 / -MspeedL)) == 0)
    {
      myStepperL.step(1);
      Mangle -= 0.23;
    }
  }

  if (MspeedR > 0) {
    if ((Mcycle % (100 / MspeedR)) == 0)
    {
      myStepperR.step(1);
      Mangle-= 0.23;
    }
  }
 else if (MspeedR < 0) {
    if ((Mcycle % (100 / -MspeedR)) == 0)
    {
      myStepperR.step(-1);
      Mangle += 0.23;
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
}

void loop()
{

  if (Serial.available() > 0)     // Send data only when you receive data:
  {
    data = Serial.read();        //Read the incoming data & store into data

    switch (data)
    {
      case 'f':
        Mangle = 0;
        Mspeed = 50;
        break;

      case 'b':
        Mangle = 0;
        Mspeed = -50;
        break;

      case 'l':
        Mangle = -45;
        break;
      case 'r':
        Mangle = 45;
        break;
      case 'o':
        Mangle = 0;
        Mspeed = 0;
        break;

      default:
        break;


    }


  }
  movement();
  delay(1);
}
