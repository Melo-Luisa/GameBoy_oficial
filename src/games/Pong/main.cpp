#include <Arduino.h>
#include <TFT_eSPI.h> 
#include <SPI.h>
#include "pongConfig.h"
// #include "bola/ball.h"



void setup(){
    //precisa de nada
    pinMode(button::azul, PULLUP);
    pinMode(button::amarelo, PULLUP);

    TFT_eSPI d = TFT_eSPI();  //init display
    TFT_eSprite ball = TFT_eSprite(&d);
    TFT_eSprite barra1 = TFT_eSprite(&d);
    TFT_eSprite barra2 = TFT_eSprite(&d);
    TFT_eSprite placar = TFT_eSprite(&d);
}

void loop(){
    //trazer main

}