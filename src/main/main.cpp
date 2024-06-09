#include <Arduino.h>
#include <TFT_eSPI.h>
#include <SPI.h>

#include <config.h>

#include <joystick.h>
#include "menu.h"

//MENU
TFT_eSPI d = TFT_eSPI();  // Define Display
TFT_eSprite text = TFT_eSprite(&d);
TFT_eSprite game = TFT_eSprite(&d);

//PONG
TFT_eSprite ball = TFT_eSprite(&d);
TFT_eSprite barra_joy = TFT_eSprite(&d);
TFT_eSprite barra_button = TFT_eSprite(&d);
TFT_eSprite placar = TFT_eSprite(&d);
TFT_eSprite abertura = TFT_eSprite(&d);

/*MENU*/
bool geral = false; //inicia no menu inicial
bool games = true; //menu games
bool settings = false; //menu settings
bool credits = false; //menu credits

bool var = true;

//começa em 1 pra já ter algo pré selecionado
int geral_index = 0;
int games_index = 0;
int settings_index = 1;


/*PONG*/
int x = 0; // valor inicial de x
int y = 0; // valor inicial de y
int vx = 5; // valor inicial de vx
int vy = 5; // valor inicial de vy
int circleRadius = 10; // raio do círculo
int countBlack = 0; // contador de pontos preto
int countWhite = 0; // contador de pontos branco
int coordY = 100;



Juiz juiz(x, y, vx, vy, circleRadius, coordY);
Menu menu(geral, games, settings, credits, geral_index, games_index, settings_index);

bool gamePongOn = false;


void setup() {
  Serial.begin(115200);
  d.init();
  d.setRotation(1);
  d.setSwapBytes(true);
  d.fillScreen(TFT_BLACK);

  text.setColorDepth(8);
  text.createSprite(480, 100); //faixa na tela

  game.setColorDepth(8);
  game.createSprite(480, 100); //faixa na tela4

  abertura.setColorDepth(8);
  abertura.createSprite(367, 300); //faixa na tela

  ball.setColorDepth(8);
  ball.createSprite(45, 45);

  placar.setColorDepth(8);
  placar.createSprite(120, 50);
  placar.setTextDatum(MC_DATUM); 

  barra_joy.setColorDepth(8);
  barra_joy.createSprite(85, 130);

  barra_button.setColorDepth(8);
  barra_button.createSprite(100, 100);

  pinMode(button::azul, INPUT_PULLUP);
  pinMode(button::vermelho, INPUT_PULLUP);

  menu.init(d);
  


}

void loop(){

  menu.select(games_index, abertura, gamePongOn, game, var);
  menu.drawMenuGames(game, games_index);
  menu.trackPosition(games, games_index);

     

  if(gamePongOn){
    //Serial.println("Funciona");
   
    if(var){
      menu.backgroundPong(d);
      var = false;
      
    }
     
    juiz.draw_Ball(ball); // desenha bola
    juiz.draw_button( barra_button, coordY);
    juiz.placar(placar, countBlack, countWhite); // desenha placar
    //juiz.atingir(); // verifica se atingiu
    juiz.count(); // conta os pontos
    juiz.draw_joy(barra_joy);
  }


}




