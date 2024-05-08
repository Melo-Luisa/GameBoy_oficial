#include <Arduino.h>
#include <TFT_eSPI.h> 
#include <SPI.h>
#include "pong_config.h"
#include "bola/ball.h"
#include "barra/barra.h"


void setup(){
    //precisa de nada
    pinMode(button::azul, PULLUP);
    pinMode(button::amarelo, PULLUP);
}

void loop(){
    //trazer main

}