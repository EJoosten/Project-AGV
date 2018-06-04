#include <A4988.h>
#include <Arduino.h>

// Motor steps per revolution. Most steppers are 200 steps or 1.8 degrees/step
#define MOTOR_STEPS 200
// Target RPM for cruise speed
#define RPM 120
// Acceleration and deceleration values are always in FULL steps / s^2
#define MOTOR_ACCEL 2000
#define MOTOR_DECEL 1000

// Microstepping mode. If you hardwired it to save pins, set to the same value here.

#define DIRL 2
#define STEPL 3

#define DIRR 2
#define STEPR 3

#include "A4988.h"

A4988 stepperL(MOTOR_STEPS, DIRL, STEPL);
A4988 stepperR(MOTOR_STEPS, DIRR, STEPR);



#include <Servo.h>

Servo exampleServo;

char data = 0;            //Variable for storing received data
void setup()
{
  Serial.begin(9600);   //Sets the baud for serial data transmission
  pinMode(13, OUTPUT);  //Sets digital pin 13 as output pin
  exampleServo.attach(9);

  stepperL.begin(RPM);
  stepperR.begin(RPM);
  stepperL.enable();
  stepperR.enable();

  /*
     Set LINEAR_SPEED (accelerated) profile.
  */
  stepperL.setSpeedProfile(stepperL.LINEAR_SPEED, MOTOR_ACCEL, MOTOR_DECEL);
  stepperR.setSpeedProfile(stepperR.LINEAR_SPEED, MOTOR_ACCEL, MOTOR_DECEL);
  Serial.println("START");
  /*
     Using non-blocking mode to print out the step intervals.
     We could have just as easily replace everything below this line with
     stepper.rotate(360);
  */
  stepperR.startRotate(720);
  stepperL.startRotate(720);
}
void loop()
{
  if (Serial.available() > 0)     // Send data only when you receive data:
  {
    data = Serial.read();        //Read the incoming data & store into data

    switch (data)
    {
      case 'f':
        Serial.println("case: f");
        stepperR.rotate(180);
        stepperL.rotate(180);
        break;

      case 'b':
        Serial.print("case: b");
        stepperR.rotate(-180);
        stepperL.rotate(-180);
        break;

      case 'l':
        Serial.print("case: l");
        stepperR.rotate(-180);
        stepperL.rotate(180);
        break;
      case 'r':
        Serial.print("case: r");
        stepperR.rotate(180);
        stepperL.rotate(-180);
        break;
      default:
        break;


    }

  }
}
