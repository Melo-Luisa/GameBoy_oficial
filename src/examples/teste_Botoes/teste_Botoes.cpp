#include <Arduino.h>

#include <TFT_eSPI.h> // Graphics and font library for ILI9341 driver chip
#include <SPI.h>

TFT_eSPI d = TFT_eSPI();  // Invoke library

int botaoA = 36;
int botaoB = 39;
int botaoC = 34; //azul
int botaoD = 35; // amarelo

bool estadoA = 0;
bool estadoB = 0;
bool estadoC = 0;
bool estadoD = 0;



void setup(){
    d.init();
    d.setRotation(2);
    pinMode(botaoA, INPUT_PULLUP);
    pinMode(botaoB, INPUT_PULLUP);
    pinMode(botaoC, INPUT_PULLUP);
    pinMode(botaoD, INPUT_PULLUP);
    Serial.begin(115200);
    Serial.println("Inicio");
}

void loop(){
    Serial.print(digitalRead(botaoA));
    Serial.print(digitalRead(botaoB));
    Serial.print(digitalRead(botaoC));
    Serial.println(digitalRead(botaoD));



    d.fillScreen(TFT_BLACK);
    if(digitalRead(botaoA) == 0){
        estadoA = !estadoA;
        while(digitalRead(botaoA) == LOW){
            d.setCursor(60, 130, 2);
            d.setTextColor(TFT_WHITE);
            d.setTextSize(2);
            d.print("Botao Branco Pressionado");
        }
    } else {
        d.fillScreen(TFT_BLACK);
    }

    if(digitalRead(botaoB) == 0){
        estadoB = !estadoB;
        while(digitalRead(botaoB) == LOW){
            d.setCursor(60, 130, 2);
            d.setTextColor(TFT_RED);
            d.setTextSize(2);
            d.print("Botao Vermelho Pressionado");
        }
    } else {
        d.fillScreen(TFT_BLACK);
    }

    if(digitalRead(botaoC) == 0){
        estadoC = !estadoC;
        while(digitalRead(botaoC) == LOW){
            d.setCursor(60, 130, 2);
            d.setTextColor(TFT_BLUE);
            d.setTextSize(2);
            d.print("Botao Azul Pressionado");
        }
    } else {
        d.fillScreen(TFT_BLACK);
    }

   if(digitalRead(botaoD) == 0){
    estadoD = !estadoD;
    while (digitalRead(botaoD) == LOW){
        d.setCursor(60, 130, 2);
        d.setTextColor(TFT_YELLOW);
        d.setTextSize(2);
        d.print("Botao Amarelo Pressionado");
    }
   } else {
    d.fillScreen(TFT_BLACK);
   }
    
}