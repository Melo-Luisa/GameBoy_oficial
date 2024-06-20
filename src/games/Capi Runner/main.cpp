#include <Arduino.h>
#include <TFT_eSPI.h>
#include <SPI.h>

#include "logic.h"
#include "config.h"

TFT_eSPI d = TFT_eSPI();
TFT_eSprite capiSprite = TFT_eSprite(&d);
TFT_eSprite obstaculosSprite = TFT_eSprite(&d);

int x = 490, vx = 5;
int numObstaculos;
logic mylogic(x, vx, numObstaculos);


void setup() {
    Serial.begin(115200);
    d.init();
    d.fillScreen(TFT_ORANGE);
    d.setRotation(1);
    d.setSwapBytes(true);

    pinMode(button::azul, INPUT);

    capiSprite.setColorDepth(8);
    capiSprite.createSprite(120,120);
    capiSprite.setSwapBytes(true);

    obstaculosSprite.setColorDepth(8);
    obstaculosSprite.createSprite(50,70);
}

void loop() {
    numObstaculos = mylogic.randomObstaculos(0);
    mylogic.drawCapi(capiSprite);
    mylogic.drawObstacles(obstaculosSprite, numObstaculos);
    mylogic.randomObstaculos(numObstaculos);
}
