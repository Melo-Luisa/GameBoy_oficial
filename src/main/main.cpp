#include <Arduino.h>
#include <TFT_eSPI.h>
#include <SPI.h>
#include <stdlib.h>

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


//capi
TFT_eSprite capiSprite = TFT_eSprite(&d);
TFT_eSprite obstaculosSprite = TFT_eSprite(&d);
TFT_eSprite scoreSprite = TFT_eSprite(&d);
TFT_eSprite groundSprite = TFT_eSprite(&d);


//QUIZ

/*MENU*/
bool geral = false; //inicia no menu inicial
bool games = true; //menu games
bool settings = false; //menu settings
bool credits = false; //menu credits

bool var = true;
bool capi = true;

//começa em 1 pra já ter algo pré selecionado
int geral_index = 0;
int games_index = 0;
int settings_index = 1;


/*PONG*/
int x = 0; // valor inicial de x
int y = 0; // valor inicial de y
int vx = 10; // valor inicial de vx
int vy = 10; // valor inicial de vy
int circleRadius = 10; // raio do círculo
int countBlack = 0; // contador de pontos preto
int countWhite = 0; // contador de pontos branco
int coordY = 100;
int coordY_button = 100;

/*capi*/
int capix = 490, capivx = 5;
int numObstaculos;
int capiplacar = 0;


Juiz juizPong(x, y, vx, vy, circleRadius, coordY, coordY_button);

JuizCapi juizcapi(capix, capivx, numObstaculos);

Menu menu(geral, games, settings, credits, geral_index, games_index, settings_index);

bool gamePongOn = false;
bool gameCapiOn = false;
bool menuOn = true; 


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

  

  pinMode(button::azul, INPUT_PULLUP);
  pinMode(button::vermelho, INPUT_PULLUP);
  pinMode(button::verde, INPUT_PULLUP);

  menu.init(d);
  


}

void loop(){

  menu.select(games_index, gamePongOn, var, gameCapiOn, capi, game);
  menu.drawMenuGames(game, games_index);
  menu.trackPosition(games, games_index);


  while(gamePongOn){
    menuOn = false;
    if(var){
      menu.backgroundPong(d,abertura);
      ball.setColorDepth(8);
      ball.createSprite(65, 65);

      placar.setColorDepth(8);
      placar.createSprite(120, 50);
      placar.setTextDatum(MC_DATUM); 

      barra_joy.setColorDepth(8);
      barra_joy.createSprite(85, 180);

      barra_button.setColorDepth(8);
      barra_button.createSprite(100, 180);
      var = false;

      
    }
   
    juizPong.draw_Ball(ball); // desenha bola
    juizPong.draw_button( barra_button, coordY_button);
    juizPong.placar(placar, countBlack, countWhite); // desenha placar
    juizPong.atingir(); // verifica se atingiu
    juizPong.count(abertura); // conta os pontos
    juizPong.draw_joy(barra_joy);
    if(juizPong.getCountBlack() > 9 || juizPong.getCountWhite() > 9){
      gamePongOn = false;
      menu.backgroundEndPong(d, gamePongOn);
      menuOn = true;
    }
  }

  while(gameCapiOn){
    menuOn = false;
    if(capi){
      menu.backgroundCapi(d);
      capiSprite.setColorDepth(8);
      capiSprite.setSwapBytes(true);
      capiSprite.createSprite(70,130);

      obstaculosSprite.setColorDepth(8);
      obstaculosSprite.createSprite(85,70);

      scoreSprite.setColorDepth(8);
      scoreSprite.createSprite(230,70);
      scoreSprite.setTextDatum(MC_DATUM);

      groundSprite.setColorDepth(8);
      groundSprite.setSwapBytes(true);
      groundSprite.createSprite(85, 70);
      capi = false;
    }
    juizcapi.drawCapi(capiSprite);
    juizcapi.drawObstacles(obstaculosSprite);
    //juizcapi.background(groundSprite);
    juizcapi.colision();
    juizcapi.score();
    juizcapi.drawScore(scoreSprite);
    juizcapi.level_speed();
   
  }
  





}




