#include <Stepper.h>

#define RPM 360
#define soortStep 1       //full step, half step, quarter step, gebruikt in de for loops
#define DIRL  1           //random waarde voor code check
#define DIRR 2            //random waarde voor code check
#define STEPL 3           //random waarde voor code check 
#define STEPR 4           //random waarde voor code check
#define num_of_steps 10   //random waarde voor code check

const int stappenPerRondje = 200;  // change this to fit the number of steps per revolution
char data = 0;

Stepper stepperL(stappenPerRondje, DIRL, STEPL );
Stepper stepperR(stappenPerRondje, DIRR, STEPR );



void forwardStep(int steps) {    // 1 stap vooruit voor beide motoren
  stepperL.step(1);
  stepperR.step(1);
  delay(5);
}
void backwardStep(int steps) { // 1 stap achteruit voor beide motoren
  stepperL.step(-1);
  stepperR.step(-1);
  delay(5);
}
void rightStep(int steps) {    // 1 stap met de linkermotor, draaien rond het rechterwiel
  stepperL.step(1);
  delay(5);
}
void leftStep(int steps) {     // 1 stap met de rechtermotor, draaien rond het linkerwiel
  stepperR.step(1);
  delay(5);
}

void setup() {
  Serial.begin(9600);   //Sets the baud for serial data transmission
  stepperL.setSpeed(RPM);
  stepperR.setSpeed(RPM);
}

void loop() {
  if (Serial.available() > 0)     // Send data only when you receive data:
  {
    data = Serial.read();        //Read the incoming data & store into data

    switch (data) {
      case 'f':
        forwardStep(num_of_steps);
        break;

      case 'b':
        backwardStep(num_of_steps);
        break;

      case 'l':
        leftStep(num_of_steps);
        break;

      case 'r':
        rightStep(num_of_steps);
        break;

      default:
        break;

    }
  }


}

