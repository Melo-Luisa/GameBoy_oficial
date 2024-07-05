#include <Arduino.h>
#include<FastLED.h> // header file

#define NUM_LEDS 60 // number of led present in your strip
#define LED_PIN 33 // digital pin of your arduino

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2811, LED_PIN, RGB>(leds, NUM_LEDS);

}

void loop() {

leds[0] = CRGB::Blue; //glow 1st led as green

FastLED.show(); // apply the function on led strip

delay(30);

}