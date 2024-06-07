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
TFT_eSprite abertura = TFT_eSprite(&d);

//compila

int x = 0; // valor inicial de x
int y = 0; // valor inicial de y
int vx = 5; // valor inicial de vx
int vy = 5; // valor inicial de vy
int circleRadius = 10; // raio do círculo
int countBlack = 0; // contador de pontos preto
int countWhite = 0; // contador de pontos branco
int coordY = 100;

Juiz meujuiz(x, y, vx ,vy, countBlack, countWhite, circleRadius, coordY);

Joystick joy(32, 33);

void startgame();

void setup() {
    Serial.begin(115200);
    d.init();
    d.fillScreen(TFT_ORANGE);
    d.setRotation(1);

    abertura.setColorDepth(8);
    abertura.createSprite(367, 300); //faixa na tela

    ball.setColorDepth(8);
    ball.createSprite(40, 40);

    placar.setColorDepth(8);
    placar.createSprite(120, 50);
    placar.setTextDatum(MC_DATUM); 

    barra_joy.setColorDepth(8);
    barra_joy.createSprite(50, 100);

    barra_button.setColorDepth(8);
    barra_button.createSprite(100, 100);

    pinMode(button::azul, INPUT_PULLUP);
    pinMode(button::vermelho, INPUT_PULLUP);
    meujuiz.init(abertura);
    delay(1000);

   d.fillScreen(TFT_BLACK);
}

void loop() {
        
        int xAxisValue = analogRead(32);
        int yAxisValue = analogRead(33);

        joy.checkAndPrintDirections(xAxisValue, yAxisValue);
        meujuiz.draw_Ball(ball); // desenha bola
        meujuiz.draw_button( barra_button, coordY);
        meujuiz.placar(placar, countBlack, countWhite); // desenha placar
        // //meujuiz.hit_esquerda(); // retorna valor se atingiu esq
        // //meujuiz.hit_direita(); // retorna valor se atingiu na dire
        meujuiz.atingir(); // verifica se atingiu
        meujuiz.count(); // conta os pontos
        meujuiz.draw_joy( barra_joy);



    
}

