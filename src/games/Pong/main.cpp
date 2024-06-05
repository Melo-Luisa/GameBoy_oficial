#include <Arduino.h>
#include <TFT_eSPI.h> 
#include <SPI.h>

#include "juiz.h"
#include "barra.h"
#include "config.h"
#include "joystick.h"

TFT_eSPI d = TFT_eSPI();
TFT_eSprite screen = TFT_eSprite(&d); // aparece na tela
TFT_eSprite ball = TFT_eSprite(&d);
TFT_eSprite barra_joy = TFT_eSprite(&d);
TFT_eSprite barra_button = TFT_eSprite(&d);
TFT_eSprite placar = TFT_eSprite(&d);

//compila

int x = 100; // valor inicial de x
int y = 50; // valor inicial de y
int vx = 10; // valor inicial de vx
int vy = 10; // valor inicial de vy
int circleRadius = 10; // raio do círculo
int countBlack = 0; // contador de pontos preto
int countWhite = 0; // contador de pontos branco
int coordY ;

Juiz meujuiz(x, y, vx ,vy, countBlack, countWhite, circleRadius, coordY);

Joystick joy(32, 33);


void setup() {
    Serial.begin(115200);
    d.init();
    d.fillScreen(TFT_ORANGE);
    d.setRotation(1);

    screen.setColorDepth(8);
    screen.createSprite(367, 301);

    // ball.setColorDepth(8);
    // ball.createSprite(30, 24);

    // screen.setColorDepth(8);
    // screen.createSprite(300,300);

    placar.setColorDepth(8);
    placar.createSprite(120, 50);
    placar.setTextDatum(MC_DATUM); 

    // barra_joy.setColorDepth(8);
    // barra_joy.createSprite(50, 300);

    // barra_button.setColorDepth(8);
    // barra_button.createSprite(100, tela::width);

    pinMode(button::azul, INPUT_PULLUP);
    pinMode(button::amarelo, INPUT_PULLUP);
}

void loop() {
    int xAxisValue = analogRead(32);
    int yAxisValue = analogRead(33);

    joy.checkAndPrintDirections(xAxisValue, yAxisValue);


    meujuiz.draw_Ball(screen); // desenha bola
    meujuiz.placar(placar, countBlack, countWhite, screen); // desenha placar
    meujuiz.hit_esquerda(); // retorna valor se atingiu esq
    meujuiz.hit_direita(); // retorna valor se atingiu na dire
    meujuiz.atingir(); // verifica se atingiu
    meujuiz.count(); // conta os pontos
    meujuiz.draw_joy( screen);
    meujuiz.draw_button( screen);

    screen.pushSprite(60,10);


    
}
