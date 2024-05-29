#include <TFT_eSPI.h> // Graphics and font library for ILI9341 driver chip
#include <SPI.h>

#include "inputs.h"
#include "initGB_black.h"


TFT_eSPI d = TFT_eSPI();  // Define Display




int menuIndex = 0;

void init();
void drawMenu();
void menu();

void setup() {
  d.init();
  d.setRotation(1);
  d.setSwapBytes(true);
  d.fillScreen(TFT_BLACK);




  pinMode(botaoA, INPUT_PULLUP);

  init();
  delay(1000);
}

void loop() {
  drawMenu();
  menu();
  
}

void init() {
  d.setCursor(100, 120, 2);
  d.setTextColor(TFT_WHITE);
  d.setTextSize(5);
  

  String word = "GAMEBOY";

  for (int i = 0; i < word.length(); i++) {
    d.print(word[i]);
    delay(100);
  }

  delay(1000);
}


