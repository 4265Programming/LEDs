#include "FastLED.h"

#define NUM_LEDS 79
CRGB leds[NUM_LEDS];

#define DATA_PIN 3
#define CLOCK_PIN 4
#define MAX_BRIGHTNESS 255
#define LEFT_START 0
#define LEFT_END 33
#define MID_START 34
#define MID_END 43
#define RIGHT_START 44
#define RIGHT_END 78

unsigned int mode = 1;

void setup() {
  FastLED.addLeds<WS2801, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
  Serial.begin(9600);
}

void loop() {
  switch(mode)
  {
    case 0:
      for(int i=4; i>0; i--){
        two_color_bounce(CRGB::Red, CRGB::Blue, 30);
        two_color_bounce(CRGB::Blue, CRGB::White, 30);
        two_color_bounce(CRGB::White, CRGB::Red, 30);
      }
      break;
    case 1:
      for(int i=2; i>0; i--){
        color_fade(CRGB::Red, CRGB::White, 5);
        color_fade(CRGB::White, CRGB::Blue, 5);
        color_fade(CRGB::Blue, CRGB::Red, 5);
      }
      break;
    case 2:
      for(int i=2; i>0; i--){
        three_pair(CRGB::Red, CRGB::White, CRGB::Blue, 10);
        three_pair_off(10);
      }
      break;
    case 3:
      for(int i=1; i>0; i--){
        three_train(CRGB::Red, CRGB::White, CRGB::Blue, 15);
        three_train(CRGB::White, CRGB::Blue, CRGB::Red, 15);
        three_train(CRGB::Blue, CRGB::Red, CRGB::White, 15);
      }
      break;
  }
  mode++;
  if(mode>3){
    mode=0;
  }
}

void two_color_bounce(uint32_t colorLeft, uint32_t colorRight, uint8_t del)
{
  FastLED.setBrightness(MAX_BRIGHTNESS);
  for(int i=0; i<NUM_LEDS; i++){
    leds[i] = colorLeft;
    leds[NUM_LEDS-1-i] = colorRight;
    delay(del);
    FastLED.show();
  }
  for(int i=NUM_LEDS; i>0; i--){
    leds[i] = colorRight;
    leds[NUM_LEDS-1-i] = colorLeft;
    delay(del);
    FastLED.show();
  }
}

void color_fade(uint32_t fadeOutColor, uint32_t fadeInColor, uint8_t del){
  fill_solid(leds, NUM_LEDS, fadeOutColor);
  FastLED.setBrightness(MAX_BRIGHTNESS);
  for(int i = MAX_BRIGHTNESS; i>0; i--){
    FastLED.setBrightness(i);
    delay(del);
    FastLED.show();
  }
  fill_solid(leds, NUM_LEDS, fadeInColor);
  delay(del);
  for(int i = 0; i<MAX_BRIGHTNESS; i++){
    FastLED.setBrightness(i);
    delay(del);
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

void three_pair_off(uint8_t time)
{
  for(int i = 0; i<NUM_LEDS; i+=3){
    leds[i] = CRGB::Black;
    delay(time);
    FastLED.show();
  }
  for(int i = 1; i<NUM_LEDS; i+=3){
    leds[i] = CRGB::Black;
    delay(time);
    FastLED.show();
  }
  for(int i = 2; i<NUM_LEDS; i+=3){
    leds[i] = CRGB::Black;
    delay(time);
    FastLED.show();
  }
  delay(50);
}

void three_train(uint32_t a, uint32_t b, uint32_t c, uint8_t del){
  //FIX LATER
}