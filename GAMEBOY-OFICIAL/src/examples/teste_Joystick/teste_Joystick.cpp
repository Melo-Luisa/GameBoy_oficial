#include <Arduino.h>
#include <TFT_eSPI.h> 
#include <SPI.h>
#define EIXO_X  33
#define EIXO_Y  32

TFT_eSPI d = TFT_eSPI();  

int circleRadius = 10;
int squareWidth = 5;
int vx = 5, vy = 5; //velocidade da bolinha
int x = 100, y = 50;

int botaoC = 34; //azul
int botaoD = 35; // amarelo



void setup() {
    d.init();
    d.setRotation(2);
    //joystick
    pinMode(EIXO_X, INPUT);
    pinMode(EIXO_Y, INPUT);
    //buttons
    pinMode(botaoC, INPUT_PULLUP);
    pinMode(botaoD, INPUT_PULLUP);
    Serial.begin(115200);
    d.fillScreen(TFT_BLACK);
   
}

void loop(void) {
    //JOYSTICK
    int old_x = x;
    int old_y = y;

    int barX = 0;
    int barY = 10; // distancia no eixo y
    int coordX = 0;
    int oldX_bar = coordX;

    //BOTOES
    int barX_botton = 0;
    int barY_botton = 30;
    

    /*JOYSTICK*/
    coordX = map(analogRead(EIXO_Y), 0, 550, 0, 25);
    barX += coordX;
    d.fillRect(oldX_bar, barY, 240,100, TFT_BLACK); // baixo
    d.fillRect(barX, barY, 70, 10, TFT_WHITE); // cima, coordenada X altera , controla pelo joy
    delay(100);

    /*BOTOES*/
    //1 - NÃO PRESSIONADO
    //0 - PRECIONADO 
    d.fillRect(barX, barY, 70, 10, TFT_WHITE);
    if(digitalRead(botaoC)==0){
        d.fillRect(barX_botton, barY_botton, 100, 10, TFT_WHITE);
    }else if(digitalRead(botaoD) == 0){
        d.print("Botão amarelo");
        d.print("oi");
    }


/*ANIMAÇÃO DA BOLA*/
    x += vx;
    y += vy;

    if((x<=0) || (x>= d.width() - squareWidth)){
        vx = -vx;
    }
    if((y<= 0)|| (y >= d.height() - squareWidth)){
        vy = -vy;
        Serial.print("Toquei nos cantos - Y");
    }


    d.fillCircle(old_x, old_y, squareWidth, TFT_BLACK);
    d.fillCircle(x,y,squareWidth, TFT_RED);
    delay(20);
}

