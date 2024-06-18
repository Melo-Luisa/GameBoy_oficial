#include <Arduino.h>
#include <TFT_eSPI.h>
#include <SPI.h>

#include "logic.h"
#include "config.h"

TFT_eSPI d = TFT_eSPI();
TFT_eSprite capiSprite = TFT_eSprite(&d);
TFT_eSprite obstaculos = TFT_eSprite(&d);

int x = 0, vx = 5;
int leap;
logic mylogic;


void setup() {
    Serial.begin(115200);
    d.init();
    d.fillScreen(TFT_ORANGE);
    d.setRotation(1);
    d.setSwapBytes(true);

    pinMode(button::azul, INPUT);

    capiSprite.setColorDepth(8);
    capiSprite.createSprite(96,96);
    capiSprite.setSwapBytes(true);

    obstaculos.setColorDepth(8);
    obstaculos.createSprite(50,50);
}

void loop() {
    mylogic.drawCapi(capiSprite);
    //mylogic.drawObstacles(obstaculos);
}
