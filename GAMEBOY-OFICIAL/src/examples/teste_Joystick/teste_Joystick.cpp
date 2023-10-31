/*#include <Arduino.h>
#include <TFT_eSPI.h> // Graphics and font library for ILI9341 driver chip
#include <SPI.h>

#define EIXO_X  33
#define EIXO_Y  32

TFT_eSPI d = TFT_eSPI();  // Invoke library

int circleX = 120;  // Initial circle position
int circleY = 160;  // Initial circle position
int circleRadius = 10;

void setup(){
    d.init();
    d.setRotation(2);
    pinMode(EIXO_X, INPUT);
    pinMode(EIXO_Y, INPUT);
    Serial.begin(115200);
}

void loop(){

    Serial.print("X: ");
    Serial.print(analogRead(EIXO_X));
    Serial.print(" Y: ");
    Serial.println(analogRead(EIXO_Y));
    //delay(100);
    
    //pega a coordenada
    int coordX = map(analogRead(EIXO_X), 0, 4095, 0, 220);
    int coordY = map(analogRead(EIXO_Y), 0, 4095, 0, 310);

    d.drawCircle(coordX, coordY, 15, TFT_WHITE);
    d.fillCircle(coordX, coordY, 10, TFT_SKYBLUE);
    d.fillCircle(200, 200, 10, TFT_RED);
    delay(10);


     int old_x, old_y;

    Serial.print("X: ");
    Serial.print(analogRead(EIXO_X));
    Serial.print(" Y: ");
    Serial.println(analogRead(EIXO_Y));

    int coordX = map(analogRead(EIXO_X), 0, 4095, 0, 220);
    int coordY = map(analogRead(EIXO_Y), 0, 4095, 0, 310);

    old_x = coordX;
    old_y = coordY;
    if()


   
    d.fillCircle(old_x, old_y, circleRadius, TFT_BLACK);
    //d.fillCircle(coordX, coordY, circleRadius, TFT_SKYBLUE);
    //d.fillCircle(200, 200, 10, TFT_RED);

    //delay(10);
}*/

#include <Arduino.h>
#include <TFT_eSPI.h> 
#include <SPI.h>
#define EIXO_X  33
#define EIXO_Y  32

TFT_eSPI d = TFT_eSPI();  

int circleRadius = 10;
int squareWidth = 5;
int vx = 1, vy = 1;
int x = 100, y = 50;



void setup() {
    d.init();
    d.setRotation(2);
    pinMode(EIXO_X, INPUT);
    pinMode(EIXO_Y, INPUT);
    Serial.begin(115200);
    d.fillScreen(TFT_BLACK);
   
}

void loop(void) {
    int old_x = x;
    int old_y = y;

    int barX = 0;
    int barY = 10; // distancia no eixo y
    int coordX = 0;
    int oldX_bar = coordX;
   //nt oldY_bar = EIXO_Y;

/*JOYSTICK*/
    coordX = map(analogRead(EIXO_Y), 0, 550, 0, 25);
    barX += coordX;
    d.fillRect(oldX_bar, barY, 240,100, TFT_BLACK); // baixo
    d.fillRect(barX, barY, 70, 10, TFT_WHITE); // cima, coordenada X altera , controla pelo joy
    delay(10);

/*BOTOES*/


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

