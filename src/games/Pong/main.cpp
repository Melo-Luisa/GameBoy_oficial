#include <Arduino.h>
#include <TFT_eSPI.h> 
#include <SPI.h>

#include "juiz/utils.h"
#include "pongConfig.h"

TFT_eSPI d = TFT_eSPI();
TFT_eSprite ball = TFT_eSprite(&d);
TFT_eSprite barra_joy = TFT_eSprite(&d);
TFT_eSprite barra_button = TFT_eSprite(&d);
TFT_eSprite placar = TFT_eSprite(&d);

// Defina valores para as variáveis ​​que serão passadas para o construtor de Juiz
int x = 60; // valor inicial de x
int y = 50; // valor inicial de y
int vx = 10; // valor inicial de vx
int vy = 10; // valor inicial de vy
int circleRadius = 10; // raio do círculo
int countBlack = 0; // contador de pontos preto
int countWhite = 0; // contador de pontos branco

// Crie um objeto da classe Juiz com os valores definidos
Juiz juiz( x,  y,  vx,  vy,  circleRadius,  countBlack,  countWhite);

void setup(){
    //precisa de nada
    pinMode(button::azul, PULLUP);
    pinMode(button::amarelo, PULLUP);

}

void loop(){
    //trazer main
    juiz.draw_ball(ball); // desenha bola
    juiz.placar(placar, countBlack, countWhite); // desenha placar
    juiz.hit_esquerda(); // retorna valor se atingiu esq
    juiz.hit_direita(); // retorna valor se atingiu na dire
    juiz.atingir(); // verifica se atingiu
    juiz.count(circleRadius, countWhite, countBlack); //conta os pontos
    juiz.draw_joy(barra_joy);
    juiz.draw_button(barra_button);

}
