#include <Arduino.h>
#include <TFT_eSPI.h> 
#include <SPI.h>
// #include "pongConfig.h"
// #include "bola/ball.h"
#include "juiz/utils.h"
#include "pongConfig.h"


TFT_eSPI d = TFT_eSPI();
TFT_eSprite ball = TFT_eSprite(&d);
TFT_eSprite barra_joy = TFT_eSprite(&d);
TFT_eSprite barra_button = TFT_eSprite(&d);
TFT_eSprite placar = TFT_eSprite(&d);

// Crie um objeto da classe Juiz
// Crie um objeto da classe Juiz
Juiz juiz = Juiz(x, y, vx, vy, circleRadius, countBlack, countWhite);

void setup(){
    //precisa de nada
    pinMode(button::azul, PULLUP);
    pinMode(button::amarelo, PULLUP);

}

void loop(){
    //trazer main
    juiz.draw_ball(TFT_eSprite &ball); // desenha bola
    juiz.placar( TFT_eSprite &placar, int countBlack, int countWhite); // desenha placar
    juiz.hit_esquerda(); // retorna valor se atingiu esq
    juiz.hit_direita(); // retorna valor se atingiu na dire
    juiz.atingir(); // verifica se atingiu
    juiz.count(int circleRadius, int countWhite, int countBlack); //conta os pontos
    juiz.draw_joy(TFT_eSprite &barra_joy);
    juiz.draw_button(TFT_eSprite &barra_button);

}