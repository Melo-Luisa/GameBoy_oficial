#include <TFT_eSPI.h> // Graphics and font library for ILI9341 driver chip
#include <SPI.h>

#include "config.h"
#include "menu.h"
#include "joystick.h"

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

Joystick joy(joystick::eixo_x, joystick::eixo_y, joystick::botao_joy);



void setup() {
  Serial.begin(115200);
  d.init();
  d.setRotation(1);
  d.setSwapBytes(true);
  d.fillScreen(TFT_WHITE);

  text.setColorDepth(8);
  text.createSprite(480, 100); //faixa na tela



  menu.init(d);

}

void loop(){

  // int xValue = joy.read_raw_X();
  // int yValue = joy.read_raw_Y();
  // int buttonState = joy.read_button_central();

  // Verificar e imprimir direções
  //joy.checkAndPrintDirections(xValue, yValue);
  menu.trackPosition(geral, geral_index);
  menu.drawMenuInicial(d, text, geral_index);
  menu.select(geral_index, text);
  //menu.drawMenuGames(text, geral_index);
  delay(100);
  //Serial.print(String(analogRead(32)) + " ");
  //Serial.println(String(analogRead(33)) + " ");
  //Serial.println(digitalRead(joystick::botao_joy));
}




