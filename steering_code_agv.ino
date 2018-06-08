/*
  Bluetooh Basic: LED ON OFF - Avishkar
  Coder - Mayoogh Girish
  Website - http://bit.do/Avishkar
  Download the App : https://github.com/Mayoogh/Arduino-Bluetooth-Basic
  This program lets you to control a LED on pin 13 of arduino using a bluetooth module
*/


#include <Stepper.h>

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
  /* Serial.print(analogRead(potL));
    Serial.print("   ");
    Serial.println(analogRead(potR));*/
  movement();
  delay(1);
}
