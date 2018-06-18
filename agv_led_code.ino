#include <FAB_LED.h>

/// @brief This parameter says how many LEDs will be lit up in your strip.
const uint8_t numPixels = 2;

/// @brief This says how bright LEDs will be (max is 255)
const uint8_t maxBrightness = 100;
apa104<B, 4>   LEDstrip;
grb  pixels[numPixels] = {};


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
}

void ledRed()
{
  pixels[0].g = 255;
  pixels[0].r = 0;
  pixels[0].b = 0;
  pixels[1].g = 255;
  pixels[1].r = 0;
  pixels[1].b = 0;
  LEDstrip.sendPixels(numPixels, pixels);
  LEDstrip.refresh();
}

void ledGreen()
{
  pixels[0].g = 0;
  pixels[0].r = 200;
  pixels[0].b = 0;
  pixels[1].g = 0;
  pixels[1].r = 200;
  pixels[1].b = 0;
  LEDstrip.sendPixels(numPixels, pixels);
  LEDstrip.refresh();
}
void ledOrangeLeft()
{
  pixels[0].g = 255;
  pixels[0].r = 62;
  pixels[0].b = 0;
  pixels[1].g = 0;
  pixels[1].r = 0;
  pixels[1].b = 0;
  LEDstrip.sendPixels(numPixels, pixels);
  LEDstrip.refresh();
}
void ledOrangeRight()
{
  pixels[0].g = 0;
  pixels[0].r = 0;
  pixels[0].b = 0;
  pixels[1].g = 255;
  pixels[1].r = 62;
  pixels[1].b = 0;
  LEDstrip.sendPixels(numPixels, pixels);
  LEDstrip.refresh();
}
void ledBlue()
{
  pixels[0].g = 0;
  pixels[0].r = 0;
  pixels[0].b = 255;
  pixels[1].g = 0;
  pixels[1].r = 0;
  pixels[1].b = 255;
  LEDstrip.sendPixels(numPixels, pixels);
  LEDstrip.refresh();
}
void loop()
{
  ///////////////////blue for plant///////////////////
  ledBlue();
  delay(1000);
  ///////////////////orange left///////////////////
  ledOrangeLeft();
  delay(1000);
  ///////////////////orange right///////////////////
  ledOrangeRight();
  delay(1000);
  ///////////////////green for driving///////////////////
  ledGreen();
  delay(1000);
  ///////////////////red for warning///////////////////
  ledRed();
  delay(2000);
}
