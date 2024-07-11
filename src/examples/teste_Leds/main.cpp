
#include <Arduino.h>
#include<FastLED.h> // header file

#define NUM_LEDS 21 // number of led present in your strip - PRIMOS
#define LED_PIN 23 // digital pin of your arduino

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2811, LED_PIN, RGB>(leds, NUM_LEDS);
  

}

void loop() {

  for(int i = 0; i < NUM_LEDS; i++){
    leds[i] = CRGB::White;
    FastLED.show();
    delay(1000);
  }


delay(30);



}






