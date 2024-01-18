#include <Arduino.h>
#include <TFT_eSPI.h> 
#include <SPI.h>
#define EIXO_X  33
#define EIXO_Y  32

TFT_eSPI d = TFT_eSPI();  

TFT_eSprite ball = TFT_eSprite(&d);

int coordX, coordY;

void setup() {
    Serial.begin(115200);
    d.init();
    d.fillScreen(TFT_BLACK);
    d.setRotation(1); //Origem no canto superior esquerdo (Fita Verde)
    ball.setColorDepth(8);
    ball.createSprite(320, 240); //sprite funcionando full width and height
    //joystick
    pinMode(EIXO_X, INPUT);
    pinMode(EIXO_Y, INPUT);
}


void loop() {
    
    //Visualização sistema de coordenadas com orientação = 1
    //Flickering pq não está como sprite
    d.setCursor(0, 0);
    d.setTextSize(3);
    d.setTextColor(TFT_BLUE);
    d.print("A");

    d.setCursor(300, 0);
    d.setTextSize(3);
    d.setTextColor(TFT_RED);
    d.print("B");

    d.setCursor(0, 220); //Ao colocar 240, ele vai para 240, mas o ponto inicial é o superior, dai não aparece
    d.setTextSize(3);
    d.setTextColor(TFT_GREEN);
    d.print("C");

    d.setCursor(300, 220); //Ao colocar 240, ele vai para 240, mas o ponto inicial é o superior, dai não aparece
    d.setTextSize(3);
    d.setTextColor(TFT_YELLOW);
    d.print("D");

    //JOYSTICK
    int coordX = 0;
    int coordY = 0;




    /*JOYSTICK*/
    coordX = map(analogRead(EIXO_X), 0, 4095, 0, 300);
    coordY = map(analogRead(EIXO_Y), 0, 4095, 0, 220);

    Serial.print("X: "+String(analogRead(EIXO_X)));
    Serial.println("Y: "+String(analogRead(EIXO_Y)));


    ball.fillCircle(coordX, coordY, 10, TFT_WHITE);




    ball.pushSprite(0,0);
    ball.fillCircle(coordX, coordY, 10, TFT_BLACK); //Pra apagar a antiga. Só foi se colocado abaixo do push



}


//essa função desse jogo aqui https://github.com/dorsheed455k/programs/blob/master/Hardware/Arduino%20Pong%20Ball/Pongball.ino
//ele pega a leitura do joy, e usa alguns IFs pra determinar se ta indo pra um lado ou pro outro
//a depender disso, ele mexe o quadrado

/*
void joyStickControl() {


  if(millis() - lastToggle > 50) {

    currentPos = xPosition;
  
    if(currentPos > 512 && (currentPos != 512 || prevPos != 512)) {
        xPaddle += 10;
      }
    
      if(currentPos < 512 && (currentPos != 512 || currentPos != 512)) {
        xPaddle -= 10;
      }
    
      if(xPaddle < 0) {
        xPaddle = 0;
      }
    
      if(xPaddle + 40 > WIDTH) {
        xPaddle = WIDTH - 40;
      }
  
    prevPos = currentPos;
  }

  //lastToggle = millis();


  tft.fillRect(xPaddle, yPaddle, 40, 10, color);
  
}
*/