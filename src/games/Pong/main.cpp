#include <Arduino.h>
#include <TFT_eSPI.h> 
#include <SPI.h>

#include "juiz.h"

TFT_eSPI d = TFT_eSPI();
TFT_eSprite ball = TFT_eSprite(&d);
TFT_eSprite barra_joy = TFT_eSprite(&d);
TFT_eSprite barra_button = TFT_eSprite(&d);
TFT_eSprite placar = TFT_eSprite(&d);

//compila

int x = 60; // valor inicial de x
int y = 50; // valor inicial de y
int vx = 10; // valor inicial de vx
int vy = 10; // valor inicial de vy
int circleRadius = 10; // raio do círculo
int countBlack = 0; // contador de pontos preto
int countWhite = 0; // contador de pontos branco

void setup() {
    d.init();
    d.fillScreen(TFT_ORANGE);
    d.setRotation(1);

    ball.setColorDepth(8);
    ball.createSprite(320, 240);

    placar.setColorDepth(8);
    placar.createSprite(120, 50);
    placar.setTextDatum(MC_DATUM); 

    barra_joy.setColorDepth(8);
    barra_joy.createSprite(100, 240);

    barra_button.setColorDepth(8);
    barra_button.createSprite(100, 80);//+

    pinMode(button::azul, INPUT_PULLUP);
    pinMode(button::amarelo, INPUT_PULLUP);
}

void loop() {
    Juiz meujuiz(x, y, vx ,vy, countBlack, countWhite, circleRadius);
   
    meujuiz.draw_Ball(ball, x, y, circleRadius); // desenha bola
//    // meujuiz.placar(placar, countBlack, countWhite, ball); // desenha placar
//     meujuiz.hit_esquerda(); // retorna valor se atingiu esq
//     meujuiz.hit_direita(); // retorna valor se atingiu na dire
//     meujuiz.atingir(); // verifica se atingiu
//     meujuiz.count(countWhite, countBlack); // conta os pontos
    //meujuiz.draw_joy(barra_joy, ball);
    meujuiz.draw_button(barra_button, ball);

}
