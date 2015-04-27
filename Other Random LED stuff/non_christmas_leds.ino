#include "FastLED.h"
#define NUM_LEDS 80
CRGB leds[NUM_LEDS];

#define DATA_PIN 3
#define CLOCK_PIN 4
#define MAX_BRIGHTNESS 255

void setup(){
  FastLED.addLeds<WS2801, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
  Serial.begin(9600);
}

void loop(){
  comet(CRGB::Red, 20);
}

void comet(uint8_t r, uint8_t g, uint8_t b, uint8_t trailLength, uint8_t time){
  double modR = r/trailLength;
  double modG = g/trailLength;
  double modB = b/trailLength;
  for(int i = 0; i<NUM_LEDS; i++){
    for(int j = i; i-j < 0 || j > trailLength; j++){
      leds[i-j].rgb(r*(r/modR), g*(g/modG), b*(b/modB));  
    }
    FastLED.show();
  }
}
