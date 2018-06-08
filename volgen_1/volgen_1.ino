#include <Stepper.h>
#include <Servo.h>
#include <NewPing.h>

#include <Stepper.h>
#include <Servo.h>

#define trigPin  10  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define echoPin     13  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(trigPin, echoPin, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution for your motor

// initialize the stepper library on pins 8 through 11:
Stepper myStepperR(stepsPerRevolution, 6, 7, 8, 9);
Stepper myStepperL(stepsPerRevolution, 2, 3, 4, 5);


char data = 0;            //Variable for storing received data

#define echoPin 13 // Echo Pin
#define trigPin 10 // Trigger Pin

int potmeterR = A1;
int potmeterL = A2;
int PotValueR;
int PotValueL;

int duration; // Duration used to calculate the distance
int distance;
int DistanceR;
int DistanceL;

int servo_st = 0;


int turn;
char follow;
int pos = 0;    // variable to store the servo position
char way;


Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards


void setup()
{
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
  pinMode(13, OUTPUT);  //Sets digital pin 13 as output pin
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // set the speed at 60 rpm:
  myStepperR.setSpeed(60);
  myStepperL.setSpeed(60);

}

void MeasureP() {
  delay(30);
  Serial.print("Ping: ");
  distance = sonar.ping_cm( sonar.ping_median(10));
  Serial.print(distance); // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");

}

void Guiding() {

  PotValueR = analogRead(potmeterR); // Lees de analoge ingang uit.
  PotValueL = analogRead(potmeterL); // Lees de analoge ingang uit.
  Serial.print("Pot-meter Rechts: ");
  Serial.println(PotValueR); // print potmeter waarde via seriele monitor.
  Serial.print("Pot-meter Links:  ");
  Serial.println(PotValueL); // print potmeter waarde via seriele monitor.
  delay(15); // even wachten voor een nieuwe loop.

  if (PotValueR > 775 && PotValueL > 775) {
    turn = 0;
  }

  else {
    turn = 4;
  }
}

void followStand() {
  MeasureP();
  Guiding();
  if (distance > 10 && PotValueR < 770 ) {
    follow = 'f';
  }
  else if (distance > 10 && PotValueL < 770 ) {
    follow = 'f';
  }

  else if (distance <= 10) {
    follow = 's';
  }
}


void servo() {

  switch (turn) {
    case 0:
      for (pos = 0; pos <= 90; pos += 1) { // goes from 0 degrees to 180 degrees
        // in steps of 1 degree
        myservo.write(pos);              // tell servo to go to position in variable 'pos'
        delayMicroseconds(15);                       // waits 15us for the servo to reach the position
      }
      MeasureP();
      DistanceL = distance;
      turn = 1;
      break;

    case 1:
      for (pos = 90; pos <= -90; pos -= 1) { // goes from 0 degrees to 180 degrees
        // in steps of 1 degree
        myservo.write(pos);              // tell servo to go to position in variable 'pos'
        delayMicroseconds(15);                       // waits 15us for the servo to reach the position
      }
      MeasureP();
      DistanceR = distance;
      turn = 2;
      break;

    case 2:
      for (pos = -90; pos <= 0; pos += 1) { // goes from 0 degrees to 180 degrees
        // in steps of 1 degree
        myservo.write(pos);              // tell servo to go to position in variable 'pos'
        delayMicroseconds(15);                       // waits 15us for the servo to reach the position
      }
      turn = 3;

      break;

    case 3:
      if (DistanceL < DistanceR) {
        way = 'l';
      }
      else {
        way = 'r';
      }
      break;

    case 4:
      break;
  }
}

void Steppers() {
  switch (follow) {
    case 'f':
      for (int i = 0; i < 100; i++) {
        myStepperR.step(-1);
        myStepperL.step(1);
      }
      break;

    case 's':
      myStepperR.step(0);
      myStepperL.step(0);
      break;
  }
}

void Bend() {
  switch (way) {
    case 'l':
      for (int i = 0; i < 100; i++) {
        myStepperR.step(1);
        myStepperL.step(1);
      }
      break;

    case 'r':
      for (int i = 0; i < 100; i++) {
        myStepperR.step(-1);
        myStepperL.step(-1);
      }
      break;
  }
}



void loop()
{
  
  followStand() {


}

