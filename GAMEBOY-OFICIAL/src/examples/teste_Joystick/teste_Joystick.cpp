#include <Arduino.h>
#include <TFT_eSPI.h> // Graphics and font library for ILI9341 driver chip
#include <SPI.h>

TFT_eSPI d = TFT_eSPI();  // Invoke library

int eixoY = 33;
int eixoX = 32;

void setup(){
    d.init();
    d.setRotation(2);
    pinMode(eixoX, INPUT);
    pinMode(eixoY, INPUT);
    Serial.begin(115200);
}

void loop(){

    Serial.print("X: ");
    Serial.print(analogRead(eixoX));
    Serial.print(" Y: ");
    Serial.println(analogRead(eixoY));
    //delay(100);
    
    int coordX = map(analogRead(eixoX), 0, 4095, 0, 220);
    int coordY = map(analogRead(eixoY), 0, 4095, 0, 310);


    d.fillCircle(coordX, coordY, 10, TFT_SKYBLUE);
    d.fillCircle(200, 200, 10, TFT_RED);
}