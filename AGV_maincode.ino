/*
  Main code. kaas
*/

#include <Stepper.h>
#include <NewPing.h>
#include <Servo.h>
#include <FAB_LED.h>

#define TRIGGER_PIN  9  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     8  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define trig 10
#define led 12      //LED tied to pin 12
#define echo 13
#define servo 11    //Servo pin is tied to arduino pin 11
#define potL A1     //Potio meter on the left on arduino pin A1
#define potR A0     //Potio meter on the right on arduino pin A0


/// @brief This parameter says how many LEDs will be lit up in your strip.
const uint8_t numPixels = 2;

/// @brief This says how bright LEDs will be (max is 255)
const uint8_t maxBrightness = 100;
apa104<B, 4>   LEDstrip;
grb  pixels[numPixels] = {};

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

Servo myservo;
int pos = 0;
int dir = 0;
int radar;
int objx[5], objy[5];
int i, j, k;
int mode = 0;
int closestDir, closestDis = 200;
int tempClosestDir, tempClosestDis = 200;
const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution for your motor

// initialize the stepper library on pins 8 through 11:
Stepper myStepperR(stepsPerRevolution, 6, 7, 8, 9);
Stepper myStepperL(stepsPerRevolution, 2, 3, 4, 5);
volatile int Mspeed, MspeedT, MspeedL, MspeedR, Mcycle, navigation = 1, turn, situation = 1, potangleL, potangleR, mills, leds;
volatile float Mangle;
char data = 0;            //Variable for storing received data
void setup()
{

  for (uint8_t pos = 0; pos < numPixels; pos++) {
    pixels[pos].g = 0;
    pixels[pos].b = 0;
    pixels[pos].r = 0;
  }
  LEDstrip.refresh(); // Hack: needed for apa102 to display last pixels
  // Clear display
  LEDstrip.sendPixels(numPixels, pixels);
  LEDstrip.refresh(); // Hack: needed for apa102 to display last pixels
  myservo.attach(5);
  Serial.begin(9600);

  Serial.begin(9600);   //Sets the baud for serial data transmission
  // set the speed at 60 rpm:
  myStepperR.setSpeed(60);
  myStepperL.setSpeed(60);
  pinMode(13, OUTPUT);  //Sets digital pin 13 as output pin
}
void ledRed()
{
  if (leds != 1) {
    leds = 1;
    pixels[0].g = 255;
    pixels[0].r = 0;
    pixels[0].b = 0;
    pixels[1].g = 255;
    pixels[1].r = 0;
    pixels[1].b = 0;
    LEDstrip.sendPixels(numPixels, pixels);
    LEDstrip.refresh();

  }
}

void ledGreen()
{
  if (leds != 2) {
    leds = 2;
    pixels[0].g = 0;
    pixels[0].r = 200;
    pixels[0].b = 0;
    pixels[1].g = 0;
    pixels[1].r = 200;
    pixels[1].b = 0;
    LEDstrip.sendPixels(numPixels, pixels);
    LEDstrip.refresh();
  }
}
void ledOrangeLeft()
{
  if (leds != 3) {
    leds = 3;
    pixels[0].g = 255;
    pixels[0].r = 62;
    pixels[0].b = 0;
    pixels[1].g = 0;
    pixels[1].r = 0;
    pixels[1].b = 0;
    LEDstrip.sendPixels(numPixels, pixels);
    LEDstrip.refresh();
  }
}
void ledOrangeRight()
{
  if (leds != 4) {
    leds = 4;
    pixels[0].g = 0;
    pixels[0].r = 0;
    pixels[0].b = 0;
    pixels[1].g = 255;
    pixels[1].r = 62;
    pixels[1].b = 0;
    LEDstrip.sendPixels(numPixels, pixels);
    LEDstrip.refresh();
  }
}
void ledBlue()
{
  if (leds != 5) {
    leds = 5;
    pixels[0].g = 0;
    pixels[0].r = 0;
    pixels[0].b = 255;
    pixels[1].g = 0;
    pixels[1].r = 0;
    pixels[1].b = 255;
    LEDstrip.sendPixels(numPixels, pixels);
    LEDstrip.refresh();
  }
}
void ledOff()
{
  if (leds != 0) {
    leds = 0;
    pixels[0].g = 0;
    pixels[0].r = 0;
    pixels[0].b = 0;
    pixels[1].g = 0;
    pixels[1].r = 0;
    pixels[1].b = 0;
    LEDstrip.sendPixels(numPixels, pixels);
    LEDstrip.refresh();
  }
}
void movement()
{
  mills = millis();
  /*if(Mspeed == 0){
    ledRed();
    }*/
  if (Mcycle % 15 == 0) {
    if (MspeedT < Mspeed) {
      MspeedT++;
    }
    else if (MspeedT > Mspeed) {
      MspeedT--;
    }
  }
  if (Mangle < -1)
  {
    if (mills % 1000 < 500)
    {
      ledOrangeLeft();
    }
    else
    {
      ledOff();
    }
    if (MspeedL < MspeedT + 10) {
      MspeedL++;
    }
    else if (MspeedL > MspeedT + 10) {
      MspeedL--;
    }
    if (MspeedR < MspeedT - 10) {
      MspeedR++;
    }
    else if (MspeedR > MspeedT - 10) {
      MspeedR--;
    }
  }
  else if (Mangle > 1)
  {
    if (mills % 1000 < 500)
    {
      ledOrangeRight();
    }
    else
    {
      ledOff();
    }
    if (MspeedL < MspeedT - 10) {
      MspeedL++;
    }
    else if (MspeedL > MspeedT - 10) {
      MspeedL--;
    }
    if (MspeedR < MspeedT + 10) {
      MspeedR++;
    }
    else if (MspeedR > MspeedT + 10) {
      MspeedR--;
    }
  }
  else
  {
    ledBlue();
    if (MspeedL < MspeedT) {
      MspeedL++;
    }
    else if (MspeedL > MspeedT) {
      MspeedL--;
    }
    if (MspeedR < MspeedT) {
      MspeedR++;
    }
    else if (MspeedR > MspeedT) {
      MspeedR--;
    }
  }


  if (MspeedL > 0) {
    if ((Mcycle % (100 / MspeedL)) == 0)
    {
      myStepperL.step(-1);
      Mangle += 0.11;
    }
  }
  else if (MspeedL < 0) {
    if ((Mcycle % (100 / MspeedL)) == 0)
    {
      myStepperL.step(1);
      Mangle -= 0.11;
    }
  }

  if (MspeedR > 0) {
    if ((Mcycle % (100 / MspeedR)) == 0)
    {
      myStepperR.step(1);
      Mangle -= 0.11;
    }
  }
  else if (MspeedR < 0) {
    if ((Mcycle % (100 / MspeedR)) == 0)
    {
      myStepperR.step(-1);
      Mangle += 0.11;
    }
  }
  if (-2 < Mangle && Mangle < 2)
  {
    Mangle = 0;
  }
  if (Mcycle >= 100) {
    Mcycle = 0;
  }
  Mcycle++;


}
void bluetooth() {              //Function which converts the bluetooth signals to signals to the steppers
  // navigation = 1;
  if (Serial.available() > 0)     // Send data only when you receive data:
  {
    data = Serial.read();        //Read the incoming data & store into data
    switch (data)
    {
      case 'f':                 //Signal straight forward
        navigation = 0;
        Mangle = 0;
        Mspeed = 20;
        break;

      case 'b':                 //Signal straight backwards
        navigation = 0;
        Mangle = 0;
        Mspeed = -20;
        break;

      case 'l':                 //Signal 45 degrees left turn
        navigation = 0;
        Mangle = -45;
        break;

      case 'r':                 //Signal 45 degrees right turn
        navigation = 0;
        Mangle = 45;
        break;
      case 'o':                 //Signal to stop
        navigation = 0;
        Mangle = 0;
        Mspeed = 0;
        break;
      case 's':                 //Signal to stop using bluetooth
        navigation = 1;
        break;


      default:
        break;


    }


  }
}

void nav() {                    //Function that makes shure the AVG stays in the middle of the path
  switch (situation)            //Switch case with al the situations the AGV can be in
  {
    case 0:                     //The AGV encounters an object and stops
      Mangle = 0;
      Mspeed = 0;
      break;

    case 1:                     //The AGV drives straigt
      Mspeed = 50;
      Mangle = 0;
      break;

    case 2:                     //The AGV needs to adjust its course to the right
      Mspeed = 50;
      Mangle = 2;
      break;

    case 3:                     //The AGV needs to adjust its course to the left
      Mspeed = 50;
      Mangle = -2;
      break;

    case 4:                     //The AGV needs to turn
      Mspeed = 0;
      Mangle = 0;
      turn = 1;
      break;

    default:
      break;
  }

}

void potread() {                //Function to see if the AGV drives straight
  potangleL = analogRead(potL);
  potangleR = analogRead(potR);
  if ((potangleR + potangleL) < 1580) {   //Only goes further if AGV is not at a turn)
    if (potangleL < potangleR + 15 && potangleR < potangleL + 15) {   //AGV is in het middle
      situation = 1;
      //Serial.println("sit1");
    }
    else if (potangleL < potangleR) {   //AGV needs to turn to the right
      situation = 2;
      //Serial.println("sit2");
    }
    else if (potangleR < potangleL) {   //AGV needs to rurn to the left
      situation = 3;
      //Serial.println("sit3");
    }
  }
  else { //Both arms turn outwards(AGV needs to turn)  Can be changed to else right??
    situation = 4;
    //Serial.println("sit4");
  }
}
/*
  void radarRead() {
  myservo.write(pos * 30);
  delay(1);
  radar = sonar.convert_cm(sonar.ping_median(10));
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
*/
void loop()
{

  bluetooth();
  if (navigation == 1) {
    nav();
  }
  potread();
  //radarRead();

  /* serial.print(analogRead(potL));
    Serial.print("   ");
    Serial.println(analogRead(potR));*/
  movement();
  delay(1);
}

