#include <Arduino.h>
#include <TFT_eSPI.h>
#include <SPI.h>

#include "juizVelha.h"
#include "config.h"



TFT_eSPI tft = TFT_eSPI();  // Inicialização da tela

int alternativa_index = 0;

JuizVelha velha;

void setup() {
    Serial.begin(115200);
    tft.init();
    tft.setRotation(1);
    tft.fillScreen(TFT_BLUE);

    velha.drawLines(tft);
    

}



void loop(){



    
    
}
