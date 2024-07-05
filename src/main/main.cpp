#include <Arduino.h>
#include <TFT_eSPI.h>
#include <SPI.h>
#include <stdlib.h>

#include <config.h>
#include <joystick.h>
#include "menu.h"

// MENU
TFT_eSPI d = TFT_eSPI();  // Define Display

// PONG
TFT_eSprite* ball = nullptr;
TFT_eSprite* barra_joy = nullptr;
TFT_eSprite* barra_button = nullptr;
TFT_eSprite* placar = nullptr;
TFT_eSprite* abertura = nullptr;

// capi
TFT_eSprite* capiSprite = nullptr;
TFT_eSprite* obstaculosSprite = nullptr;
TFT_eSprite* scoreSprite = nullptr;

// MENU FLAGS
bool geral = false; // inicia no menu inicial
bool games = true; // menu games
bool settings = false; // menu settings
bool credits = false; // menu credits

bool var = true;
bool capi = true;

// começa em 1 pra já ter algo pré-selecionado
int geral_index = 0;
int games_index = 0;
int settings_index = 1;

// PONG VARIABLES
int x = 0; // valor inicial de x
int y = 0; // valor inicial de y
int vx = 10; // valor inicial de vx
int vy = 10; // valor inicial de vy
int circleRadius = 10; // raio do círculo
int countBlack = 0; // contador de pontos preto
int countWhite = 0; // contador de pontos branco
int coordY = 100;
int coordY_button = 100;

// capi VARIABLES
int capix = 490, capivx = 5;
int numObstaculos;
int capiplacar = 0;

// QUIZ
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

  pinMode(button::azul, INPUT_PULLUP);
  pinMode(button::vermelho, INPUT_PULLUP);
  pinMode(button::verde, INPUT_PULLUP);
  pinMode(button::amarelo, INPUT_PULLUP);

  menu.init(d);
}

void back() {
  delete game;
  game = new TFT_eSprite(&d);
  game->setColorDepth(8);
  game->createSprite(480, 100);
  d.init();
  d.setRotation(1);
  d.setSwapBytes(true);
  menu.select(games_index, gamePongOn, var, gameCapiOn, capi, *game, gameQuizOn);
  menu.drawMenuGames(*game, games_index);
  menu.trackPosition(games, games_index);
  gamePongOn = false;
  gameCapiOn = false;
  menuOn = true;
}

void initializePong() {
  menu.backgroundPong(d, *abertura);
  barra_button = new TFT_eSprite(&d);
  barra_button->setColorDepth(4);
  barra_button->setSwapBytes(true);
  barra_button->createSprite(100, 180);

  ball = new TFT_eSprite(&d);
  ball->setColorDepth(8);
  ball->setSwapBytes(true);
  ball->createSprite(80, 80);

  placar = new TFT_eSprite(&d);
  placar->setColorDepth(8);
  placar->setSwapBytes(true);
  placar->createSprite(120, 50);
  placar->setTextDatum(MC_DATUM);

  barra_joy = new TFT_eSprite(&d);
  barra_joy->setColorDepth(4);
  barra_joy->setSwapBytes(true);
  barra_joy->createSprite(85, 180);
}

void destroyPongSprites() {
  delete ball;
  delete barra_button;
  delete barra_joy;
  delete placar;
  delete abertura;
}

void initializeCapi() {
  menu.backgroundCapi(d);

  capiSprite = new TFT_eSprite(&d);
  capiSprite->setColorDepth(8);
  capiSprite->setSwapBytes(true);
  capiSprite->createSprite(70, 150);

  obstaculosSprite = new TFT_eSprite(&d);
  obstaculosSprite->setColorDepth(8);
  obstaculosSprite->setSwapBytes(true);
  obstaculosSprite->createSprite(85, 70);

  scoreSprite = new TFT_eSprite(&d);
  scoreSprite->setColorDepth(4);
  scoreSprite->createSprite(230, 70);
  scoreSprite->setSwapBytes(true);
  scoreSprite->setTextDatum(MC_DATUM);
}

void destroyCapiSprites() {
  delete capiSprite;
  delete obstaculosSprite;
  delete scoreSprite;
}

void pong() {
  while (gamePongOn) {
    initializePong();
    while (gamePongOn) {
      juizPong.draw_joy(*barra_joy);
      juizPong.draw_Ball(*ball);
      juizPong.draw_button(*barra_button, coordY_button);
      juizPong.placar(*placar, countBlack, countWhite);
      juizPong.atingir();
      juizPong.count(*abertura);

      // Certifique-se de que os sprites estão sendo empurrados para a tela
      barra_joy->pushSprite(0, 0);
      ball->pushSprite(0, 0);
      barra_button->pushSprite(0, 0);
      placar->pushSprite(0, 0);
      abertura->pushSprite(0, 0);

      if (juizPong.getCountBlack() == 5 || juizPong.getCountWhite() == 5) {
        juizPong.setCountBlack(0);
        juizPong.setCountWhite(0);
        gamePongOn = false;
        gameCapiOn = false;
        menu.backgroundEndPong(d, gamePongOn);
        menuOn = true;
        d.fillScreen(TFT_WHITE);
        destroyPongSprites();
      } else if (digitalRead(button::amarelo) == LOW) {
        gamePongOn = false;
        juizPong.setCountBlack(0);
        juizPong.setCountWhite(0);
        destroyPongSprites();
        back();
      }
    }
  }
}

void capig() {
  while (gameCapiOn) {
    initializeCapi();
    while (gameCapiOn) {
      juizcapi.drawCapi(*capiSprite);
      juizcapi.drawObstacles(*obstaculosSprite);
      juizcapi.colision();
      juizcapi.score();
      juizcapi.drawScore(*scoreSprite);
      juizcapi.level_speed();

      // Certifique-se de que os sprites estão sendo empurrados para a tela
      capiSprite->pushSprite(0, 0);
      obstaculosSprite->pushSprite(0, 0);
      scoreSprite->pushSprite(0, 0);

      if (digitalRead(button::amarelo) == LOW) {
        gameCapiOn = false;
        gamePongOn = false;
        menuOn = true;
        d.fillScreen(TFT_WHITE);
        juizcapi.setplacar(0);
        destroyCapiSprites();
      }
    }
  }
}

void loop() {
  menu.select(games_index, gamePongOn, var, gameCapiOn, capi, *game, gameQuizOn);
  menu.drawMenuGames(*game, games_index);
  menu.trackPosition(games, games_index);

  // Certifique-se de que os sprites do menu estão sendo empurrados para a tela
  game->pushSprite(0, 0);

  pong();
  capig();
}
