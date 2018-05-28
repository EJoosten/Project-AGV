#include <Stepper.h>

#define RPM 360
#define soortStep 1       //full step, half step, quarter step, gebruikt in de for loops
#define DIRL 
#define DIRR
#define STEPL
#define STEPR
#define commandoRechtdoor
#define commandoAchteruit
#define commandoLinks
#define commandoRechts
#define commandoStop


const int stappenPerRondje = 200;  // change this to fit the number of steps per revolution
int data;

Stepper stepperL(stappenPerRondje,DIRL,STEPL );
Stepper stepperR(stappenPerRondje,DIRR,STEPR );



void stapVooruit(int steps){     // 1 stap vooruit voor beide motoren
  stepperL.step(1);
  stepperR.step(1);
  delay(5);
}
void stapAchteruit(int steps){  // 1 stap achteruit voor beide motoren
  stepperL.step(-1);
  stepperR.step(-1);
  delay(5);
}
void stapRechts(int steps){     // 1 stap met de linkermotor, draaien rond het rechterwiel
  stepperL.step(1);
  delay(5);
}
void stapLinks(int steps){      // 1 stap met de rechtermotor, draaien rond het linkerwiel
  stepperR.step(1);
  delay(5);
}

void setup() {
  stepperL.setSpeed(RPM);
  stepperR.setSpeed(RPM); 
}

void loop() {
  
 switch(data) {
  case commandoRechtdoor:
    forwardStep(num_of_steps);
    break; 
  case commandoAchteruit:
    backwardStep(num_of_steps);
    break;
  case commandoLinks:
    leftStep(num_of_steps);
    break;
  case commandoRechts:
    rightStep(num_of_steps);
    break;
  default
}
 
 
}


