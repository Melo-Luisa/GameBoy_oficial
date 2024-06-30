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

    if (!quiz.isFinished()) {
        quiz.trackPosition(tft, alternativa_index);
        quiz.select(tft, alternativa_index);
        //Serial.println(alternativa_index);
    } else {
        tft.fillScreen(TFT_BLACK);
        tft.setTextColor(tft.color565(255, 150, 0));    
        tft.drawString("The End", 160, 10, 2);
        if(quiz.scoreGB() > quiz.scoreJogador()){ //gameboy ganhou
            tft.setTextSize(3);
            tft.setTextColor(TFT_GREEN);
            tft.drawString("GameBoy", 30, 80, 2);
            tft.drawString((String(quiz.scoreGB())), 80, 150);
            tft.setTextColor(TFT_WHITE);
            tft.drawString("x", 230, 80, 2);
            tft.setTextColor(TFT_RED);
            tft.drawString("Player", 320, 80, 2);
            tft.drawString(String(quiz.scoreJogador()), 360, 150);
            tft.setTextColor(TFT_WHITE);
            tft.setTextSize(2);
            tft.drawString("Aparentemente o GameBoy sabe mais...", 30, 250);

            
        }else{ //jogador ganhou
            tft.setTextSize(3);
            tft.setTextColor(TFT_RED);
            tft.drawString("GameBoy", 30, 80, 2);
            tft.drawString((String(quiz.scoreGB())), 80, 150);
            tft.setTextColor(TFT_WHITE);
            tft.drawString("x", 230, 80, 2);
            tft.setTextColor(TFT_GREEN);
            tft.drawString("Player", 320, 80, 2);
            tft.drawString(String(quiz.scoreJogador()), 360, 150);
            tft.setTextColor(TFT_WHITE);   
            tft.setTextSize(2);
            tft.drawString("Tu Realmente Entende de Jogos Hein...", 20, 250);
        }

        //tft.drawString("Pontuacao Player: " + String(quiz.scoreJogador()), 40, 50, 2);
        //tft.drawString("Pontuacao GB: " + String(quiz.scoreGB()), 40, 80, 2);


        while (true) {
            delay(1000); // Para evitar reinicialização constante
        }
    }
    
    
}