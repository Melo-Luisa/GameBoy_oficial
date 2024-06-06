#include "botoes.h"
#include <TFT_eSPI.h> // Graphics and font library for ILI9341 driver chip
#include <SPI.h>

TFT_eSPI d = TFT_eSPI();  // Invoke library

const int pin_botaoA = 36;


//Cria instancia botao A
BOTAO botaoA(pin_botaoA);



bool estadoA = 0;

/*
void setup(){
    d.init();
    d.setRotation(2);
    Serial.begin(115200);
}

void loop(){
    d.fillScreen(TFT_BLACK);
    if(botaoA.read() == 0){
        estadoA = !estadoA;
        while(botaoA.read() == 0){
            d.setCursor(60, 130, 2);
            d.setTextColor(TFT_WHITE);
            d.setTextSize(2);
            d.print("Botao Branco Pressionado");
            Serial.println("apertei");
        }
    } else {
        d.fillScreen(TFT_BLACK);
    }

  
}
*/





void setup() {
  Serial.begin(115200);
  pinMode(34, INPUT); //azul
  pinMode(35, INPUT); //amarelo
  pinMode(36, INPUT); //branco- n funciona
  pinMode(39, INPUT); //vermelho

  

}

void loop() {
  Serial.print(digitalRead(34));
  Serial.print(digitalRead(35));
  Serial.print(digitalRead(36));
  Serial.println(digitalRead(39));

  
}
