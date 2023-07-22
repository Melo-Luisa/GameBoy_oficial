/*  
 Test the tft.print() viz embedded tft.write() function

 This sketch used font 2, 4, 7

 Make sure all the display driver and pin connections are correct by
 editing the User_Setup.h file in the TFT_eSPI library folder.

 #########################################################################
 ###### DON'T FORGET TO UPDATE THE User_Setup.h FILE IN THE LIBRARY ######
 #########################################################################
 */


#include <TFT_eSPI.h> // Graphics and font library for ILI9341 driver chip
#include <SPI.h>
#include <Adafruit_GFX.h>    // Biblioteca gráfica para o display


#define background 0x0000 // preto background
#define velocidade 5

TFT_eSPI tft = TFT_eSPI();  // Invoke library


int eixoY = 33;
int eixoX = 25;
int botao_JOY = 26;



// Inicialize o objeto para o display TFT


int menuIndex = 0; // Índice do item de menu selecionado



void setup(void) {
  tft.init();
  tft.begin();
  tft.setRotation(3);
  Serial.begin(115200);
  pinMode(botao_JOY, INPUT_PULLUP);
  

  init();
  delay(1000);
  tft.fillScreen(TFT_BLACK);

  //pinMode(buttonPin, INPUT_PULLUP);
  
}

void loop() {
  //drawMenu();
  
  if(digitalRead(botao_JOY) == 0){

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
  delay(1000);
}


void init(){
 
  tft.fillScreen(background);

  tft.setCursor(100, 100, 2);
  tft.setTextColor(TFT_WHITE);  
  tft.setTextSize(2);

  String word = "GameBoy";
  
  for (int i = 0; i < word.length(); i++) {
    tft.print(word[i]);
    delay(100); 
  }
  
}

 
void drawMenu() {
  // Limpar a tela
  tft.fillScreen(TFT_BLACK);
  
  // Definir cor e tamanho do texto
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(2);
  
  // Desenhar as opções do menu
  tft.setCursor(10, 50);
  if (menuIndex == 0) {
    tft.setTextColor(TFT_GREEN);
    tft.println("> Opção 1");
    tft.setTextColor(TFT_WHITE);
  } else {
    tft.println("Opção 1");
  }
  
  tft.setCursor(10, 80);
  if (menuIndex == 1) {
    tft.setTextColor(TFT_GREEN);
    tft.println("> Opção 2");
    tft.setTextColor(TFT_WHITE);
  } else {
    tft.println("Opção 2");
  }
  
  tft.setCursor(10, 110);
  if (menuIndex == 2) {
    tft.setTextColor(TFT_GREEN);
    tft.println("> Opção 3");
    tft.setTextColor(TFT_WHITE);
  } else {
    tft.println("Opção 3");
  }
  delay(1000);
}

void joy(){
  Serial.print("Leitura do eixo X: ");
  Serial.println( analogRead(eixoX));
  delay(500);
  Serial.print("Leitura do eixo Y: ");
  Serial.println( analogRead(eixoY));
  delay(500);
  Serial.print("BOTÂO: ");
  Serial.println( analogRead(botao_JOY));
  delay(500);
}




