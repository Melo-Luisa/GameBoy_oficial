#include <Arduino.h>
#include <TFT_eSPI.h>
#include <SPI.h>

#include "juizQuiz.h"
#include "config.h"



TFT_eSPI tft = TFT_eSPI();  // Inicialização da tela

int alternativa_index = 0;

JuizQuiz quiz(perguntas, sizeof(perguntas) / sizeof(perguntas[0]));

void setup() {
    Serial.begin(115200);
    tft.init();
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);
    quiz.showIntros(tft);
    quiz.drawQuestions(tft);

}



void loop(){
    if (!quiz.isFinished()) {
        quiz.trackPosition(tft, alternativa_index);
        quiz.select(tft, alternativa_index);
        //Serial.println(alternativa_index);
    } else {
        tft.fillScreen(TFT_BLACK);
        tft.setTextColor(TFT_WHITE);
        tft.drawString("Fim do Quiz!", 10, 10, 2);
        tft.drawString("Pontuacao: " + String(quiz.score()), 10, 30, 2);
        while (true) {
            delay(1000); // Para evitar reinicialização constante
        }
    }
}