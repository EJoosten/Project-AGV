/*
  Bluetooh Basic: LED ON OFF - Avishkar
  Coder - Mayoogh Girish
  Website - http://bit.do/Avishkar
  Download the App : https://github.com/Mayoogh/Arduino-Bluetooth-Basic
  This program lets you to control a LED on pin 13 of arduino using a bluetooth module
*/

#include <Servo.h>

Servo exampleServo;

char data = 0;            //Variable for storing received data
void setup()
{
  Serial.begin(9600);   //Sets the baud for serial data transmission
  pinMode(13, OUTPUT);  //Sets digital pin 13 as output pin
  exampleServo.attach(9);
}
void loop()
{
  if (Serial.available() > 0)     // Send data only when you receive data:
  {
    data = Serial.read();        //Read the incoming data & store into data

    switch (data)
    {
      case '0':
        Serial.println("case: 0");
        digitalWrite(13, LOW);
        break;

      case '1':
        Serial.println("case: 1");
        digitalWrite(13, HIGH);
        break;
        
      case 's':
          exampleServo.write(160);              
          delay(500);                       
          exampleServo.write(30);              
          delay(500);    
          break;
        
      default:
        break;


    }

  }
}
