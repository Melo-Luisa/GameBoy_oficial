


#include <TFT_eSPI.h> // Graphics and font library for ILI9341 driver chip
#include <SPI.h>

#include "inputs.h"
#include "initGB_black.h"

#define TFT_GREY 0x5AEB // New colour

TFT_eSPI tft = TFT_eSPI();  // Invoke library



int menuIndex = 0;

void init();
void drawMenu();
void menu();

void setup() {
  tft.init();
  tft.setRotation(1);
  pinMode(botaoA, INPUT_PULLUP);

  init();
  delay(1000);
  //tft.fillScreen(TFT_BLACK);
}

void loop() {
  drawMenu();
  menu();
  
}

void init() {
  tft.pushImage(0,0,320,240,initGB_black);
  delay(3000);
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(60, 130, 2);
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(2);

  String word = "GAMEBOY";

  for (int i = 0; i < word.length(); i++) {
    tft.print(word[i]);
    delay(100);
  }

}
//menu 
void drawMenu() {
  tft.fillScreen(TFT_WHITE);

  tft.setTextColor(TFT_BLACK);
  tft.setTextSize(2);
  tft.setCursor(60, 20);
  tft.print("MENU");

  tft.setCursor(60, 80);
  if (menuIndex == 0) {
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.println(" GAMES ");
    tft.setTextColor(TFT_BLACK);
  } else {
    tft.println(" GAMES ");
  }

  tft.setCursor(60, 120);
  if (menuIndex == 1) {
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.println(" SETTINGS ");
    tft.setTextColor(TFT_BLACK);
  } else {
    tft.println(" SETTINGS ");
  }

  tft.setCursor(60, 150);
  if (menuIndex == 2) {
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.println(" CREDITS ");
    tft.setTextColor(TFT_BLACK);
  } else {
    tft.println(" CREDITS ");
  }
  tft.fillCircle(200, 225, 10, TFT_RED);
  tft.setCursor(60, 255);
  tft.print("select");
  delay(1000);

  
}

//Faz as funções do menu
void menu(){
   if (analogRead(eixoY) == 4095) { // Botão do joystick para cima
    menuIndex--;
    if (menuIndex < 0) {
      menuIndex = 2;
    }
    drawMenu();
    delay(200); // Aguarde um curto período para evitar pressionamentos repetidos
  }

  if (analogRead(eixoY) == 0) { // Botão do joystick para baixo
    menuIndex++;
    if (menuIndex > 2) {
      menuIndex = 0;
    }
    drawMenu();
    delay(200); // Aguarde um curto período para evitar pressionamentos repetidos
  }

  // Lógica para executar a ação selecionada no menu
  if (digitalRead(botaoA) == HIGH) {
    // Executar a ação com base na opção selecionada no menu
    Serial.print("Funciona");
    switch (menuIndex) {
      case 0:
        tft.print("Acesso 1");
        delay(7000);
        //Serial.print("Funciona1");
        break;
      case 1:
        tft.print("Acesso 2");
        //Serial.print("Funciona2");
        delay(5000);
        break;
      case 2:
        tft.print("Acesso 3");
        delay(5000);
        //rial.println("Funciona3");
        break;
    }
    // Após executar a ação, redesenhar o menu
    drawMenu();
    delay(200); // Aguarde um curto período para evitar pressionamentos repetidos
  }
}


void joy(){
   if(digitalRead(botaoA) == 0){

    tft.println("Botao Joy acionado");
  }
  //EIXO Y
  if(analogRead(eixoY) == 4095){
    tft.println("Cima acionado");
  }
  if (analogRead(eixoY) == 0){
    tft.println("Baixo acionado");
  }
  //EIXO X
   if(analogRead(eixoX) == 4095){
    tft.println("Direita acionado");
  }
  if (analogRead(eixoX) == 0){
    tft.println("Esquerda acionado");
  }
}
