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
TFT_eSprite two = TFT_eSprite(&d);

//TELAS NOVAS
TFT_eSPI p = TFT_eSPI();

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
int games_index_two = 0;
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

/*QUIZ*/

int alternativa_index = 0;
bool quizz = true;



Juiz juizPong(x, y, vx, vy, circleRadius, coordY, coordY_button);

JuizCapi juizcapi(capix, capivx, numObstaculos);

Menu menu(geral, games, settings, credits, geral_index, games_index, settings_index);

JuizQuiz quiz(perguntas, 5);


bool gamePongOn = false;
bool gameCapiOn = false;
bool gameQuizOn = false;
bool menuOn = true; 


void setup() {
  Serial.begin(115200);
  d.init();
  d.setRotation(1);
  d.setSwapBytes(true);
  d.fillScreen(TFT_ORANGE);

  text.setColorDepth(8);
  text.createSprite(480, 100); //faixa na tela

  game.setColorDepth(8);
  game.createSprite(480, 100); //faixa na tela4

  two.setColorDepth(8);
  two.createSprite(480, 100);

  abertura.setColorDepth(8);
  abertura.createSprite(367, 300); //faixa na tela


  

  pinMode(button::azul, INPUT_PULLUP);
  pinMode(button::vermelho, INPUT_PULLUP);
  pinMode(button::verde, INPUT_PULLUP);
  pinMode(button::amarelo, INPUT_PULLUP);

  menu.init(d);
  


}

void initializePong(){
 
  //menu.backgroundPong(d, abertura);
  barra_button.setColorDepth(8);
  barra_button.setSwapBytes(true);
  barra_button.createSprite(100, 180);

  ball.setColorDepth(8);
  ball.setSwapBytes(true);
  ball.createSprite(80, 80);

  placar.setColorDepth(8);
  placar.setSwapBytes(true);
  placar.createSprite(120, 50);
  placar.setTextDatum(MC_DATUM);

  barra_joy.setColorDepth(4);
  barra_joy.setSwapBytes(true);
  barra_joy.createSprite(85, 180);
}



void initializeCapi() {
  //menu.backgroundCapi(d);

  capiSprite.setColorDepth(8);
  capiSprite.setSwapBytes(true);
  capiSprite.createSprite(70, 150);

  obstaculosSprite.setColorDepth(8);
  obstaculosSprite.setSwapBytes(true);
  obstaculosSprite.createSprite(85, 70);

  scoreSprite.setColorDepth(8);
  scoreSprite.createSprite(230, 70);
  scoreSprite.setSwapBytes(true);
  scoreSprite.setTextDatum(MC_DATUM);
}

void pong(int games_index){
  
  while (gamePongOn) {
    initializePong();
    while (gamePongOn) {
      juizPong.draw_joy(barra_joy);
      juizPong.draw_Ball(ball);
      juizPong.draw_button(barra_button, coordY_button);
      juizPong.placar(placar, countBlack, countWhite);
      juizPong.atingir();
      juizPong.count(abertura);

      if (juizPong.getCountBlack() == 5 || juizPong.getCountWhite() == 5) {
          juizPong.setCountBlack(0);
          juizPong.setCountWhite(0);
          gamePongOn = false;
          gameCapiOn = false;
          menu.backgroundEndPong(d, gamePongOn);
          menuOn = true;
          d.fillScreen(TFT_WHITE);
      } else if (digitalRead(button::amarelo) == LOW) {
          d.fillScreen(TFT_WHITE);
          gamePongOn = false;
          gameCapiOn = false;
          menuOn = true;
          juizPong.setCountBlack(0);
          juizPong.setCountWhite(0);
          menu.select(games_index, gamePongOn, var, gameCapiOn, capi, two, gameQuizOn);
          menu.drawMenuGames(&two, games_index);
          //Serial.println(games_index);
          menu.trackPosition(games, games_index);
          //Serial.println(games_index_two);

      }
    }
  }
}

void capig(int games_index){
  while (gameCapiOn) {
    initializeCapi();
    while (gameCapiOn) {
      juizcapi.drawCapi(capiSprite);
      juizcapi.drawObstacles(obstaculosSprite);
      juizcapi.colision();
      juizcapi.score();
      juizcapi.drawScore(scoreSprite);
      juizcapi.level_speed();


      if (digitalRead(button::amarelo) == LOW) {
        gameCapiOn = false;
        gamePongOn = false;
        menuOn = true;
        d.fillScreen(TFT_WHITE);
        juizcapi.setplacar(0);
        menu.select(games_index_two, gamePongOn, var, gameCapiOn, capi, two, gameQuizOn);
        menu.drawMenuGames(&two, games_index);
        menu.trackPosition(games, games_index);
      }
    }
  }
}

void initializeQuiz(){
    quiz.showIntros(d);
    quiz.drawQuestions(d);
}

void quizG(int games_index){
  while (gameQuizOn){
    initializeQuiz();
    while (gameQuizOn){
      quiz.initQuiz(d);
      if(quiz.isFinished()){
        quiz.endQuiz(d);
        d.fillScreen(TFT_WHITE);
        gameQuizOn = false;
        menuOn = true;
      }else if(digitalRead(button::amarelo) == LOW){
        d.fillScreen(TFT_WHITE);
        gameQuizOn = false;
        menuOn = true;
        menu.select(games_index, gamePongOn, var, gameCapiOn, capi, two, gameQuizOn);
        menu.drawMenuGames(&two, games_index);
        menu.trackPosition(games, games_index);
      }
    }
    
  }
  

}

void loop() {
  //games_index = 0;
  menu.select(games_index, gamePongOn, var, gameCapiOn, capi, game, gameQuizOn);
  menu.drawMenuGames(&game, games_index);
  menu.trackPosition(games, games_index);
  //Serial.println(games_index);
  pong(games_index);
  capig(games_index);
  quizG(games_index);
}


