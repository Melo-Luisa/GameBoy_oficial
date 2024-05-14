#ifdef BARRA
#define BARRA
#include <Arduino.h>
#include <TFT_eSPI.h> 
#include <SPI.h>
#include "pong/pongConfig.h"

class BARRA{
    private:
        int coordY_old, coordY_new; //JOYSTICK
        int coordY; //BUTTON
    public:
        BARRA(int coordY_old, int coordY_new, int coordY);

        //funções
        void move_joy(int coordY_old, int coordY_new);

        void move_button(int coordY);
        
        
};


void BARRA::move_joy(int coordY_old, int coordY_new){
    int coordY = map(analogRead(joystick::eixo_y), 0, 4095, 0, 220);

    coordY_old = 100;//map(analogRead(EIXO_Y), 0, 4095, 0, 220);

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
}

void BARRA::move_button(int coordY){
    if(digitalRead(button::azul) == 0){ //se o botao azul for apertado 
        if(coordY+ (barra::square_Height) <= 230){ 
            coordY += 10;
        }
    
    }
    else if(digitalRead(button::amarelo) == 0){ //se o botao azul for apertado 
        coordY -= 10;
        if(coordY+(barra::square_Height) == 50){ 
            coordY += 10;
        }
    
    }
}


#endif