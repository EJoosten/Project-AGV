#include <Servo.h>
#include <NewPing.h>

#define trigger_pin  12   // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define echo_pin     11   // Arduino pin tied to echo pin on the ultrasonic sensor.
#define servo_pin     9
#define MAX_DISTANCE 400  // max afstand die wordt gemeten
#define led_R         3   // rode led
#define led_G         4   // groene led

NewPing ultrasoon(trigger_pin, echo_pin, MAX_DISTANCE);
Servo myservo;

int pos = 0; // positie servo
int distance;
int fase = 0;
void setup() {
  myservo.attach(servo_pin);
  Serial.begin(9600);
  myservo.write(pos);
  pinMode(led_R, OUTPUT);
  pinMode(led_G, OUTPUT);
  digitalWrite(led_R, LOW);
  digitalWrite(led_G, LOW);
}

void sonar() {
  distance = ultrasoon.ping_cm();
  Serial.print(distance);
  switch (fase) {
    case 0:
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      pos += 1;
      delay(10);
      if (pos >= 180) {
        fase = 1;
        break;
      }
      else {
        break;
      }
    case 1:
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      pos -= 1;
      delay(10);
      if (pos <= 0) {
        fase = 0;
        break;
      }
      else {
        break;
      }

  }
}

void loop() {
  sonar();

  if ((pos <= 60 || pos >= 120) && (distance <= 10)) {
    digitalWrite(led_R, LOW);
    digitalWrite(led_G, HIGH);
  }

  else if ((60 < pos < 120) && (distance <= 10)) {
    digitalWrite(led_R, HIGH);
    digitalWrite(led_G, LOW);
  }

  else
  {
    digitalWrite(led_R, LOW);
    digitalWrite(led_G, LOW);
  }

}
