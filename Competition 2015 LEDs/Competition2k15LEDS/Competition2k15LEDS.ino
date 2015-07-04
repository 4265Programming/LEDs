#include <pt.h>

#include "FastLED.h"

#define NUM_LEDS 79
CRGB leds[NUM_LEDS];

#define DATA_PIN 3
#define CLOCK_PIN 4
#define MAX_BRIGHTNESS 255
#define LEFT_START 0
#define LEFT_END 33
#define MID_START 34
#define MID_END 44
#define RIGHT_START 45
#define RIGHT_END 78

unsigned int mode = 3;

static struct pt pt1, pt2;

void setup() {
  PT_INIT(&pt1);
  PT_INIT(&pt2);
  FastLED.addLeds<WS2801, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
  Serial.begin(9600);
}

static int threadCylon(){
  PT_BEGIN(pt)
  while(1) {
    PT_WAIT_UNTIL(pt, updateCylon());
  }
  PT_END(pt)
}
static int threadStrips(){
  PT_BEGIN(pt)
  while(1) {
    PT_WAIT_UNTIL(pt, updateStrips());
  }
  PT_END(pt)
}

void loop(){
  threadCylon(&pt1);
  threadStrips(&pt2);
}

boolean updateStrips(){
  switch(mode){
    case 0:
        
  }  
}
