#include <Arduino.h>
#include <TFT_eSPI.h>
#include <SPI.h>

#include "logic.h"
#include "config.h"

TFT_eSPI d = TFT_eSPI();
TFT_eSprite capiSprite = TFT_eSprite(&d);
TFT_eSprite obstaculosSprite = TFT_eSprite(&d);
TFT_eSprite scoreSprite = TFT_eSprite(&d);

int x = 490, vx = 5;
int numObstaculos;
int placar = 0;
logic mylogic(x, vx, numObstaculos);


void setup() {
    Serial.begin(115200);
    d.init();
    d.fillScreen(TFT_BLACK);
    d.setRotation(1);
    d.setSwapBytes(true);

    pinMode(button::azul, INPUT);

    capiSprite.setColorDepth(8);
    capiSprite.setSwapBytes(true);
    capiSprite.createSprite(70,150);
  

    obstaculosSprite.setColorDepth(8);
    obstaculosSprite.createSprite(85,70);

    scoreSprite.setColorDepth(8);
    scoreSprite.createSprite(230,70);
    scoreSprite.setTextDatum(MC_DATUM); 

}

void loop() {
    numObstaculos = mylogic.randomObstaculos(0);
    mylogic.drawCapi(capiSprite);
    mylogic.drawObstacles(obstaculosSprite, numObstaculos);
    mylogic.colision();
    mylogic.randomObstaculos(numObstaculos);
    mylogic.score();
    mylogic.drawScore(scoreSprite);
    mylogic.level_speed();

}
