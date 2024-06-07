#include <Arduino.h>
#include <TFT_eSPI.h>
#include <SPI.h>

#include "config.h"
#include "menu.h"
#include "joystick.h"


TFT_eSPI d = TFT_eSPI();  // Define Display
TFT_eSprite text = TFT_eSprite(&d);
TFT_eSprite game = TFT_eSprite(&d);
//TFT_eSprite abertura = TFT_eSprite(&d); 

bool geral = false; //inicia no menu inicial
bool games = true; //menu games
bool settings = false; //menu settings
bool credits = false; //menu credits
bool inGameMenu = true;

//começa em 1 pra já ter algo pré selecionado
int geral_index = 0;
int games_index = 0;
int settings_index = 1;

Menu menu(geral, games, settings, credits, geral_index, games_index, settings_index);

Joystick joy(joystick::eixo_x, joystick::eixo_y, joystick::botao_joy);



void setup() {
  Serial.begin(115200);
  d.init();
  d.setRotation(1);
  d.setSwapBytes(true);
  d.fillScreen(TFT_BLACK);

  text.setColorDepth(8);
  text.createSprite(480, 100); //faixa na tela

  game.setColorDepth(8);
  game.createSprite(480, 100); //faixa na tela

  // abertura.setColorDepth(8);
  // abertura.createSprite(367,300);

  menu.init(d);

}

void loop(){

  menu.select(games_index, abertura);
  menu.drawMenuGames(game, games_index);
  menu.trackPosition(games, games_index);

}




