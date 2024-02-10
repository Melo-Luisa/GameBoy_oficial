#include <Arduino.h>
#include <TFT_eSPI.h> 
#include <SPI.h>
#define EIXO_X  33
#define EIXO_Y  32

TFT_eSPI d = TFT_eSPI();  //init display

TFT_eSprite ball = TFT_eSprite(&d);
TFT_eSprite barra1 = TFT_eSprite(&d);
TFT_eSprite barra2 = TFT_eSprite(&d);

//Ball Settings
int circleRadius = 10;
int vx = 15, vy = 15; //velocidade da bolinha
int x = 100, y = 50;

int square_Width = 10;
int square_Height = 60;

//Barra 1 Settings 
int coordX_B1 = 0;
int coordY_B1 = 0;

//Barra 2 Settings
int coordX_B2 = 0;
int coordY_B2 = 0;



int botaoC = 34; //azul
int botaoD = 35; // amarelo



void setup() {
    Serial.begin(115200);
    d.init();
    d.fillScreen(TFT_BLACK);
    d.setRotation(1); //origem fita verde

    //Ball sprite
    ball.setColorDepth(8);
    ball.createSprite(320, 240);

    //Barra 1 Sprite
    barra1.setColorDepth(8);
    barra1.createSprite(50, 240);

    //Barra 2 Sprite
    barra2.setColorDepth(8);
    barra2.createSprite(100, 240);

    //joystick
    pinMode(EIXO_X, INPUT);
    pinMode(EIXO_Y, INPUT);
    //buttons
    pinMode(botaoC, INPUT_PULLUP);
    pinMode(botaoD, INPUT_PULLUP);

   
}

void loop() {
    ball.fillCircle(x, y, circleRadius, TFT_BLACK); //apaga a bola antiga
/*ANIMAÇÃO DA BOLA*/
    x += vx;
    y += vy;

    if((x<=0) || (x>= d.width() - circleRadius)){
        vx = -vx;
    }
    if((y<= 0)|| (y >= d.height() - circleRadius)){
        vy = -vy;
        //Serial.print("Toquei nos cantos - Y");
    }

    ball.fillCircle(x,y,circleRadius, TFT_RED);
    ball.pushSprite(0,0);

    coordX_B1 = map(analogRead(EIXO_X), 0, 4095, 0, 300);
    coordY_B1 = map(analogRead(EIXO_Y), 0, 4095, 0, 220);

    coordX_B2 = map(analogRead(EIXO_X), 0, 4095, 0, 300);
    coordY_B2 = map(analogRead(EIXO_Y), 0, 4095, 0, 220);

    barra1.fillRect(15, coordY_B1, square_Width, square_Height, TFT_WHITE);
    barra1.pushToSprite(&ball, 0, 0);
    barra1.fillRect(15, coordY_B1, square_Width, square_Height, TFT_BLACK);

    //não sei pq não está aparecendo a barra
    barra2.fillRect(80, coordY_B2, square_Width, square_Height, TFT_WHITE);
    barra2.pushToSprite(&barra1, 80, 0);
    barra2.fillRect(80, coordY_B2, square_Width, square_Height, TFT_BLACK);
    

    Serial.print("X: "+String(coordX_B1));
    Serial.println("  Y: "+String(coordY_B1));



}

/* CODIGO EXEMPLO DAS SPRITES

    img.fillCircle(x, 50, 10, TFT_BLACK); //desenha um circulo preto pra apagar o antigo
    //atualiza as coordenadas pra ele se mover
    x=x+1;
    if(x>320){
      x=0;
    }

    img.fillCircle(x, 50, 10, TFT_WHITE); //circulo branco, que está aparecendo
    img.fillRect(18, 70, 100, 100, TFT_BLACK); //retangulo preto pra apagar os numeros antigos
    img.drawString(String(x), 20, 74, 7); //posicao do circulo

*/
