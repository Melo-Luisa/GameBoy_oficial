#include <Arduino.h>
#include <TFT_eSPI.h>
#include <SPI.h>

#include "logic.h"
#include "config.h"

TFT_eSPI d = TFT_eSPI();
TFT_eSprite user = TFT_eSprite(&d);
TFT_eSprite obstaculos = TFT_eSprite(&d);

int x = 0, vx = 5;
int leap;
logic mylogic;


void setup() {
    Serial.begin(115200);
    d.init();
    d.fillScreen(TFT_ORANGE);
    d.setRotation(1);

    user.setColorDepth(8);
    user.createSprite(100,100);

    obstaculos.setColorDepth(8);
    obstaculos.createSprite(50,50);
}

void loop() {
    mylogic.drawUser(user);
    mylogic.drawObstacles(obstaculos);
}
