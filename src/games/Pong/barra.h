#pragma once
#include <Arduino.h>
#include <TFT_eSPI.h> 
#include <SPI.h>

#include "config.h"


class Barra{
    private:
        int coordY_old, coordY_new; //JOYSTICK
        int coordY; //BUTTON
    public:
        Barra(int coordY_old, int coordY_new, int coordY): coordY_old(coordY_old), coordY_new(coordY_new), coordY(coordY){}

        //funções
        int move_joy(int coordY_old, int coordY_new);

        int move_button(int coordY);
        
        
};


int Barra::move_joy(int coordY_old, int coordY_new){
    int coordY = 100;//map(analogRead(joystick::eixo_y), 0, 4095, 0, 220);

    coordY_old = 100;//map(analogRead(joystick::eixo_y), 0, 4095, 0, 220);

    //barra do joystick
    
    //Serial.println(analogRead(EIXO_Y));

    coordY_new = map(analogRead(joystick::eixo_x), 0, 4095, 0, 220);
    //cima
    if(coordY_new > coordY_old){
        coordY += 10;
    }//baixo
    if(coordY_new < coordY_old){
        coordY -= 10;

    }
    return coordY;
}

int Barra::move_button(int coordY){
    if(digitalRead(button::azul) == 0){ //se o botao azul for apertado 
        if(coordY+ (bar::square_Height) <= 230){ 
            coordY += 10;
        }
    
    }
    if(digitalRead(button::amarelo) == 0){ //se o botao azul for apertado 
        coordY -= 10;
        if(coordY+(bar::square_Height) == 50){ 
            coordY += 10;
        }
        
    
    }
    return coordY;
}
