#ifndef PONG
#define PONG

#include <Arduino.h>
#include <TFT_eSPI.h> 
#include <SPI.h>
#define EIXO_X  33
#define EIXO_Y  32


TFT_eSPI d = TFT_eSPI();  //init display

TFT_eSprite ball = TFT_eSprite(&d);
TFT_eSprite barra1 = TFT_eSprite(&d);
TFT_eSprite barra2 = TFT_eSprite(&d);
TFT_eSprite placar = TFT_eSprite(&d);

//Ball Settings
int circleRadius =10; 
int vx = 10, vy = 10; //velocidade da bolinha
int x = 100, y = 50;

int square_Width = 10;
int square_Height = 60;

//Barra joystick
int coordX_B1 = 15;
int coordY_B1 = 100;

int coordY_B1_atual = 100;
int coordY_B1_antiga = 100;


//Barra botoes
int coordY_B2 = 100; //eh y

int botao_azul = 34; //azul
int botao_amarelo = 35; // amarelo

//SCORE PLAYERS
int countBlack = 0;
int countWhite = 0;


class Pong{
public:
/*Falta parametros*/
    void update_Score(TFT_eSprite placar, int countBlack, int countWhite);

    boolean hit_direita(int x, int circleRadius, int coordY_B2, int square_Height);

    boolean hit_esquerda(int x, int circleRadius, int coordY_B2, int square_Height, int square_Width);

    void ball_a(int x, int y, int vy, int vx, int countBlack, int countWhite, int circleRadius, TFT_eSprite barra2);

    void joystick_m(int coordY_B1, int coordY_B1_antiga, TFT_eSprite barra1, int square_Width, int square_Height);

    void button_m(int botao_azul, int botao_amarelo, int coordY_B2, TFT_eSprite barra2);
};

#endif
