#include <TFT_eSPI.h> // Graphics and font library for ILI9341 driver chip
#include <SPI.h>

#include "config.h"
#include "menu.h"




TFT_eSPI d = TFT_eSPI();  // Define Display
TFT_eSprite text = TFT_eSprite(&d);


bool geral = true; //inicia no menu inicial
bool games = false; //menu games
bool settings = false; //menu settings
bool credits = false; //menu credits

//começa em 1 pra já ter algo pré selecionado
int geral_index = 0;
int games_index = 1;
int settings_index = 1;

Menu menu(geral, games, settings, credits, geral_index, games_index, settings_index);





void setup() {
  Serial.begin(115200);
  d.init();
  d.setRotation(1);
  d.setSwapBytes(true);
  d.fillScreen(TFT_BLACK);

  text.setColorDepth(8);
  text.createSprite(480, 100); //faixa na tela


  menu.init(d);

}

void loop() {
  //menu.drawMenuInicial(d, text);
  menu.trackPosition(geral, geral_index);
  //Serial.print(String(analogRead(32)) + " ");
  //Serial.println(String(analogRead(33)) + " ");

}




