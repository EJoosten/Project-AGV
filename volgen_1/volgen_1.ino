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

void volgMeten() {
  //Sensor Rechts
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);

  //Calculate the distance (in mm) based on the speed of sound.
  distance = duration / 58.2 * 10;

  distance = constrain(distance, 20, 2000);

  Serial.print(distance);
  Serial.print(" mm ");
  Serial.println();

  if (distance => 101) {
    volg = 0;
  }

  if (distance <= 100) {
    volg = 1;
  }
  /*if (distance > 200 && distance < 1000) {
    volg = 2;
    }*/
}

void loop()
{
  volgMeten();

  switch (volg) {
    case 0:

      for (int i = 0; i < 100; i++) {
        myStepperR.step(-1);
        myStepperL.step(-1);
      }
      break;

    case 1:
      myStepperR.step(0);
      myStepperL.step(0);
      break;

  }
}

