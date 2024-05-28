#include <TFT_eSPI.h> // Graphics and font library for ILI9341 driver chip
#include <SPI.h>

#include "inputs.h"
#include "initGB_black.h"


TFT_eSPI d = TFT_eSPI();  // Define Display




int menuIndex = 0;

void init();
void drawMenu();
void menu();

void setup() {
  d.init();
  d.setRotation(1);
  d.setSwapBytes(true);
  d.fillScreen(TFT_BLACK);




  pinMode(botaoA, INPUT_PULLUP);

  init();
  delay(1000);
}

void loop() {
  drawMenu();
  menu();
  
}

void init() {
  d.setCursor(100, 120, 2);
  d.setTextColor(TFT_WHITE);
  d.setTextSize(5);
  

  String word = "GAMEBOY";

  for (int i = 0; i < word.length(); i++) {
    d.print(word[i]);
    delay(100);
  }

  delay(1000);
}


//menu 
void drawMenu() {
  d.fillScreen(TFT_WHITE);

  d.setTextColor(TFT_BLACK);
  d.setTextSize(2);
  d.setCursor(60, 20);
  d.print("MENU");

  d.setCursor(60, 80);
  if (menuIndex == 0) {
    d.setTextColor(TFT_WHITE, TFT_BLACK);
    d.println(" GAMES ");
    d.setTextColor(TFT_BLACK);
  } else {
    d.println(" GAMES ");
  }

  d.setCursor(60, 120);
  if (menuIndex == 1) {
    d.setTextColor(TFT_WHITE, TFT_BLACK);
    d.println(" SETTINGS ");
    d.setTextColor(TFT_BLACK);
  } else {
    d.println(" SETTINGS ");
  }

  d.setCursor(60, 150);
  if (menuIndex == 2) {
    d.setTextColor(TFT_WHITE, TFT_BLACK);
    d.println(" CREDITS ");
    d.setTextColor(TFT_BLACK);
  } else {
    d.println(" CREDITS ");
  }
  d.fillCircle(200, 225, 10, TFT_RED);
  d.setCursor(60, 255);
  d.print("select");
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
        d.print("Acesso 1");
        delay(7000);
        //Serial.print("Funciona1");
        break;
      case 1:
        d.print("Acesso 2");
        //Serial.print("Funciona2");
        delay(5000);
        break;
      case 2:
        d.print("Acesso 3");
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

    d.println("Botao Joy acionado");
  }
  //EIXO Y
  if(analogRead(eixoY) == 4095){
    d.println("Cima acionado");
  }
  if (analogRead(eixoY) == 0){
    d.println("Baixo acionado");
  }
  //EIXO X
   if(analogRead(eixoX) == 4095){
    d.println("Direita acionado");
  }
  if (analogRead(eixoX) == 0){
    d.println("Esquerda acionado");
  }
}
