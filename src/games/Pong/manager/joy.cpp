#include "joy.h"

JOY::JOY(int coordY_old, int coordY_new){
    this->coordY_old= coordY_old;
    this->coordY_new = coordY_new;
}

void JOY::move(TFT_eSprite &barra_joy){
    int coordY = map(analogRead(EIXO_Y), 0, 4095, 0, 220);

    coordY_old = 100;//map(analogRead(EIXO_Y), 0, 4095, 0, 220);

    //barra do joystick
    
    //Serial.println(analogRead(EIXO_Y));

    coordY_new = map(analogRead(EIXO_Y), 0, 4095, 0, 220);
    //cima
    if(coordY_new > coordY_old){
        coordY += 10;
    }//baixo
    if(coordY_new < coordY_old){
        coordY -= 10;

    }
}

void JOY::draw(TFT_eSprite &barra_joy){
    barra_joy.setColorDepth(8);
    barra_joy.createSprite(100, 240);

    barra_joy.fillRect(15, coordY, square_Width, square_Height, TFT_WHITE);
    barra_joy.pushToSprite(&ball, 0, 0);
    barra_joy.fillRect(15, coordY, square_Width, square_Height, TFT_BLACK);
}