#include <Arduino.h>
#include <TFT_eSPI.h>
#include <SPI.h>

#include "juizQuiz.h"
#include "config.h"



TFT_eSPI tft = TFT_eSPI();  // Inicialização da tela

int alternativa_index = 0;


JuizQuiz quiz(perguntas, 5);

void setup() {
    Serial.begin(115200);
    tft.init();
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);
    
    quiz.showIntros(tft);
    quiz.drawQuestions(tft);

}



void loop(){
    quiz.initQuiz(tft);
    
    
}