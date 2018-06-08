
#include <NewPing.h>

#define TRIGGER_PIN  9  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     8  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

#include <Servo.h>

Servo myservo;
int pos = 0;
int dir = 0;
int radar;
int objx[5], objy[5];
int i, j, k;
int mode = 0;
int closestDir, closestDis = 200;
int tempClosestDir, tempClosestDis = 200;

void setup() {
  // put your setup code here, to run once:
  myservo.attach(5);
  Serial.begin(9600);
}


void rad() {
  myservo.write(pos * 30);
  delay(500);
  radar = sonar.convert_cm(sonar.ping_median(10));
  
  delay(30);
  if (pos == 6) {
    dir = 1;
  }
  else if (pos == 0) {
    dir = 0;
    closestDis = tempClosestDis;
    closestDir = tempClosestDir;
    tempClosestDis = 200;
  }
  if (dir == 0) {
    pos++;
  }
  else {
    pos--;
  }
  if (radar > 1){
  if (radar < tempClosestDis){
    tempClosestDir = pos;
    tempClosestDis = radar;
  }
  Serial.print(pos);
  Serial.println(radar);
  Serial.print(closestDir);
  Serial.println(closestDis);
  }
}

/*void objClass() {
  for (int i = 0; i <= 5; i++) {
    objx[i] = 0;
    objy[i] = 0;
  }
  for (int i = 0; i <= 10; i++)
  {
    if (radar[i] < 100) {

      for (int j = 0; j <= 5; j++) {
        if (objx[j] = 0) {
          break;
        }
        objx[j] = (radar[i] * cos(pos * 18));
        objy[j] = (radar[i] * sin(pos * 18));

      }
    }
    //Serial.print(radar[i]);
    //Serial.print("  ");
  }
 // Serial.println("hello");
}
*/


void loop() {
  rad();
  //objClass();



}

