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

void setup() {
  //Initializes FastLED with the Comm type, pin for data, pin for clock, and an array of LEDs
  //Leave the comm type as WS2801, unless there is some reason not to (e.g. Too many LEDs, Different variety)
  //Documentation on what comm type to use can be found in the FastLED documentation, or on the manufacturer's website
  FastLED.addLeds<WS2801, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
  Serial.begin(9600);
}

void loop() {
  //Basical looping structure that alternates through different cycles. Each case is a different effect.
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
        three_pair(CRGB::Red, CRGB::White, CRGB::Blue, 15);
        three_pair_off(10);
      }
      break;
    case 3:
      for(int i=3; i>0; i--){
        sided_strip(CRGB::Red, 15);
        sided_strip(CRGB::White, 15);
        sided_strip(CRGB::Blue, 15);
      }
      break;
    case 4:
      for(int i=4; i>0; i--){
        cylon(45);
      }
      break;
    case 5:
      stripped_led_fight(CRGB::Red, CRGB::White, 10);
      stripped_led_fight(CRGB::White, CRGB::Blue, 10);
      stripped_led_fight(CRGB::Blue, CRGB::Red, 10);
      stripped_led_fight(CRGB::Red, CRGB::Blue, 10);
      stripped_led_fight(CRGB::Blue, CRGB::White, 10);
      stripped_led_fight(CRGB::White, CRGB::Red, 10);
      break;
    case 6:
      for(int i=2; i>0; i--){
        fade_ripple(CRGB::Red, 10);
        fade_ripple(CRGB::White, 10);
        fade_ripple(CRGB::Blue, 10);
      }
      break;
    case 7:
      for(int i=2; i>0; i--){
        gradient(4);
      }
  }
  //provides a temporary pause between the cycles
  delay(250);
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  delay(250);
  mode++;
  if(mode>6){
    mode=0;
  }
}

//sends 2 different colors across opposing sides of the strip, taking over each other when they meet.
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

//Sets all the LEDs of full brightness on fadeOutColor, fades out for a duration of 255*del, then sets to fadeInColor
//and fades in for the same duration 255*del
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

//Sets every third LED to colorA, every third LED (offset 1) to colorB, and every third LED (Offset 2) to colorC
//One LED turns on every time milliseconds
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
//does the opposite of the above method.
//TODO merge with above method.
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

void sided_strip(uint32_t a, uint8_t del){
  for(int i = 0; i<LEFT_END+1; i++){
    leds[i] = a;
    leds[NUM_LEDS - 1 - i] = a;
    FastLED.show();
    delay(del);
  }
}


void cylon(uint8_t del){ //0.5 second across
  int prev = MID_START;
  for(int i=MID_START; i<MID_END; i++){
    leds[prev] = CRGB::Black;
    leds[i] = CRGB::Red;
    prev = i;
    FastLED.show();
    delay(del);
  }
  delay(del*2);
  for(int i=MID_END; i>MID_START; i--){
    leds[prev] = CRGB::Black;
    leds[i] = CRGB::Red;
    prev = i;
    FastLED.show();
    delay(del);
  }
}

//This method is specific to the LED setup on the 2015 Robot.
//TODO Provide better documentation
void stripped_led_fight(uint32_t a, uint32_t b, uint8_t del){
  fill_solid(leds, NUM_LEDS, a);
  FastLED.show();
  delay(del);
  for(int j = 0; j<LEFT_END; j++){
    leds[j] = b;
    leds[NUM_LEDS-1-j] = b;
    FastLED.show();
    delay(del);
  }
  for(int j = LEFT_END; j>0; j++){
    leds[j] = a;
    leds[NUM_LEDS-1-j] = a;
    FastLED.show();
    delay(del);
  }
}

//sends out a "pulse" on the LED strip 7 leds long. center LED is full brightness,
//each consecutive one outward is 3/4, 2/4 and 1/4 brightness, respectively
//
//Does not work with Reds at the moment, will debug
void fade_ripple(uint32_t a, uint8_t del){
  for(int i=-7; i<7+NUM_LEDS; i++){
    setRespective(a, i);
    FastLED.show();
    delay(del);
  }
}
//Helper method for the above function that assigned brightnesses to the septet of LEDs
void setRespective(uint32_t color, int index){
  for(int i = 0; i<6; i++){
    int bright = color;
    if(i == 0 || i==6){
      bright = round(color/0x000004);
    }
    if(i == 1 || i==5){
      bright = round(color/0x000002);
    }
    if(i==2 || i==4){
      bright = round((0x000003*color)/0x000004);
    }
    if(!(i+index<0)&&!(i+index>NUM_LEDS)){
      leds[i+index] = bright;
    }
  }
}

//Does a standard HSV gradient on all LEDs simultaneously
void gradient(uint8_t del){
  CHSV color;
  color.hue = 0;
  color.saturation = 255;
  color.value = 255;
  for(int i = 0; i<255; i++){
    for(int j = 0; j<NUM_LEDS; j++){
      hsv2rgb_raw(color, leds[j]);
    }
    FastLED.show();
    delay(del);
  }
}
