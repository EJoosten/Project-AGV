#include <Stepper.h>

#define RPM 360
#define soortStep 1       //full step, half step, quarter step, gebruikt in de for loops
#define num_of_steps 1
#define DIRL 6
#define DIRR 7
#define STEPL 2
#define STEPR 3
#define buttonForward 8
#define buttonBackwards 9
#define buttonLeft 10
#define buttonRight  11


const int stappenPerRondje = 200;  // change this to fit the number of steps per revolution
char data;

Stepper stepperL(stappenPerRondje,DIRL,STEPL );
Stepper stepperR(stappenPerRondje,DIRR,STEPR );



void forwardStep(int steps){     // 1 stap vooruit voor beide motoren
  stepperL.step(steps);
  stepperR.step(steps);
  delay(10);
}
void backwardStep(int steps){  // 1 stap achteruit voor beide motoren
  stepperL.step(-steps);
  stepperR.step(-steps);
  delay(10);
}
void rightStep(int steps){     // 1 stap met de linkermotor, draaien rond het rechterwiel
  stepperL.step(steps);
  delay(10);
}
void leftStep(int steps){      // 1 stap met de rechtermotor, draaien rond het linkerwiel
  stepperR.step(steps);
  delay(10);
}

void setup() {
  stepperL.setSpeed(RPM);
  stepperR.setSpeed(RPM); 
  pinMode(buttonForward,INPUT);
  pinMode(buttonBackwards,INPUT);
  pinMode(buttonLeft,INPUT);
  pinMode(buttonRight,INPUT);
  pinMode(DIRL,OUTPUT);
  pinMode(DIRR,OUTPUT);
  pinMode(STEPL,OUTPUT);
  pinMode(STEPR,OUTPUT);
  
}

void loop() {
  if(digitalRead(buttonForward) == HIGH){
    data = 'f';
  }
  if(digitalRead(buttonBackwards) == HIGH){
    data = 'b';
  }
  if(digitalRead(buttonLeft) == HIGH){
    data = 'l';
  }
  if(digitalRead(buttonRight) == HIGH){
    data = 'r';
  }
 switch(data) {
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
    forwardStep(num_of_steps);
  break;
}
 
 data = "" ;
}


