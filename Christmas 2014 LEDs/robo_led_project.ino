//Import and use FastLED lib
#include "FastLED.h"
//Total Number of LEDS. Change if Nessessary
#define NUM_LEDS 80
CRGB leds[NUM_LEDS];

//DO NOT CHANGE BELOW
unsigned int mode = 2;

#define DATA_PIN 3
#define CLOCK_PIN 4
#define MAX_BRIGHTNESS 255



//EDIT AS NESSESSARY
void setup()
{
  FastLED.addLeds<WS2801, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
  Serial.begin(9600);
}

void loop()
{
  int r = rand()%7;
  switch (mode)
  {
    case 0:
      color_chase(CRGB::Red, 10);
      color_chase(CRGB::Green, 10);
      color_chase(CRGB::White, 10);
      mode = 1;
      break;
    case 1:
      missing_dot_chase(CRGB::Red, 25);
      missing_dot_chase(CRGB::Green, 25);
      missing_dot_chase(CRGB::White, 25);
      mode= 2;
      break;
    case 2:
      bounce_colors(CRGB::White, CRGB::Green, 15);
      bounce_colors(CRGB::Red, CRGB::White, 15);
      bounce_colors(CRGB::Green, CRGB::Red, 15);
      bounce_colors(CRGB::White, CRGB::Green, 15);
      bounce_colors(CRGB::Red, CRGB::White, 15);
      bounce_colors(CRGB::Green, CRGB::Red, 15);
      mode = 4;
      break;
    case 4:
      three_pair(CRGB::Red, CRGB::Green, CRGB::White, 25);
      mode = 5;
      break;
    case 5:
      wipe(CRGB::Red, 20);
      wipe(CRGB::Green, 20);
      wipe(CRGB::White, 20);
      mode = 6;
      break;
    case 6:
      fade_to(CRGB::White, CRGB::Red, 5);
      fade_to(CRGB::Red, CRGB::Green, 5);
      fade_to(CRGB::Green, CRGB::White, 5);
      mode = 0;
      break;
    default:
      color_chase(CRGB::Red, 50);
      color_chase(CRGB::Green, 50);
      color_chase(CRGB::White, 50);
      break;
  }
}
//ADD CUSTOM FUNCTIONS BELOW
//AndyMark Pre-built
void color_chase(uint32_t color, uint8_t wait)
{
  //Turns LEDs off
  FastLED.clear();
  //Sets all brightnesses
  FastLED.setBrightness(MAX_BRIGHTNESS);
  //Individual LED control
  for(int led_number = 0; led_number < NUM_LEDS; led_number++)
  {
    //Sets a color to a defined LED
    leds[led_number] = color;
    //Turns any set LEDs on
    FastLED.show();
    //Wait
    delay(wait);
    //Sets the LED to black (Off)
    //leds[i] = 0xFF00FF  -- Sets a color via hexcode
    //leds[i] = CRGB::HotPink -- Sets a color via HTML
    //leds[i].setRGB(r,g,b) -- Sets a color via raw values where r,g,b=[0,255]
    leds[led_number] = CRGB::Black;
  }
}

void missing_dot_chase(uint32_t color, uint8_t wait)
{
  fill_solid(leds, NUM_LEDS, color);
    for(int led_number = 0; led_number<NUM_LEDS; led_number++)
    {
      leds[led_number] = CRGB::Black;
      if(led_number > 0 && led_number < NUM_LEDS)
      {
        leds[led_number-1] = color;
      }
      FastLED.show();
      delay(wait);
    }
}

void bounce_colors(uint32_t colorA, uint32_t colorB, uint8_t time)
{
  for(int offset = 0; offset<(NUM_LEDS/2); offset++)
  {
    leds[offset] = colorA;
    leds[(NUM_LEDS-1)-offset] = colorA;
    delay(time);
    FastLED.show();
  }
  for(int offset = NUM_LEDS/2; offset>0; offset--)
  {
    leds[offset] = colorB;
    leds[(NUM_LEDS-1)-offset] = colorB;
    delay(time);
    FastLED.show();
  }
}

void three_pair(uint32_t colorA, uint32_t colorB, uint32_t colorC, uint8_t time)
{
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  for(int i = 0; i<NUM_LEDS; i+=3){
    leds[i] = colorA;
    delay(time);
    FastLED.show();
  }
  for(int i = 1; i<NUM_LEDS; i+=3){
    leds[i] = colorB;
    delay(time);
    FastLED.show();
  }
  for(int i = 2; i<NUM_LEDS; i+=3){
    leds[i] = colorC;
    delay(time);
    FastLED.show();
  }
  delay(50);
}

void wipe(uint32_t color, uint8_t time)
{
  for(int i = 0; i<NUM_LEDS; i++)
  {
    leds[i] = color;
    delay(time);
    FastLED.show();
  }
}

void fade_to(uint32_t colorA, uint32_t colorB, uint8_t time)
{
  fill_solid(leds, NUM_LEDS, colorA);
  FastLED.setBrightness(MAX_BRIGHTNESS);
  for(int i = MAX_BRIGHTNESS; i>0; i--){
    FastLED.setBrightness(i);
    delay(time);
    FastLED.show();
  }
  fill_solid(leds, NUM_LEDS, colorB);
  delay(time);
  for(int i = 0; i<MAX_BRIGHTNESS; i++){
    FastLED.setBrightness(i);
    delay(time);
    FastLED.show();
  }
}

