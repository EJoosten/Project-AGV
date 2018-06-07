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

char data = 0;            //Variable for storing received data
void setup()
{
  Serial.begin(9600);   //Sets the baud for serial data transmission
    // set the speed at 60 rpm:
  myStepperR.setSpeed(60);
  myStepperL.setSpeed(60);
  pinMode(13, OUTPUT);  //Sets digital pin 13 as output pin
}
void loop()
{
  if (Serial.available() > 0)     // Send data only when you receive data:
  {
    data = Serial.read();        //Read the incoming data & store into data

    switch (data)
    {
      case 'f':
        for(int i = 0; i < 100; i++){
  myStepperR.step(-1);
  myStepperL.step(1);
  }
        break;

      case 'b':
       for(int i = 0; i < 100; i++){
  myStepperR.step(1);
  myStepperL.step(-1);
  }
        break;
        
      case 'l':
          for(int i = 0; i < 100; i++){
  myStepperR.step(1);
  myStepperL.step(1);
  }
          break;
        case 'r':
          for(int i = 0; i < 100; i++){
  myStepperR.step(-1);
  myStepperL.step(-1);
  }
          break;
      default:
        break;


    }

  }
}
