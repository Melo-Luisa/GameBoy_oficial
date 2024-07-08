#pragma once
#include <Arduino.h>

#include "config.h"
#include "joystick.h"


class Barra{
    private:
       // int coordY_old, coordY_new; //JOYSTICK
        int coordY, coordY_button; //BUTTON
        int xAxisPin; int yAxisPin, central;
        Joystick joy;
    public:
        Barra(int coordY, int coordY_button): coordY(coordY), coordY_button(coordY_button),joy(xAxisPin, yAxisPin, central){}

        //funções
        int move_joy();

        int move_button();
        
        
};


int Barra::move_joy(){
    int valueY = joy.read_raw_Y();//analogRead(joystick::eixo_x); //joystick se refere ao namespace
    Direction directionY = joy.getDirectionX(valueY);
    
    switch (directionY) {
        case LEFT:
            coordY -= 10;
            break;
        case RIGHT:
            coordY += 10;
            break;
        case NONE:
            // Do nothing
            break;
    }

    // Ensure coordY is within valid bounds
    if (coordY < -10) {
        coordY = -10;
    } else if (coordY > 240) { // Assumindo que 220 é o limite superior da barra?
        coordY = 240;
    }
    
    return coordY;
}

int Barra::move_button() {
    //cima
    if (digitalRead(button::azul) == LOW) { 
        if (coordY_button + bar::square_Height <= 290) {
            coordY_button += 10;
        }
    }
    //baixo
    else if (digitalRead(button::verde) == LOW) { // botão amarelo pressionado
        coordY_button -= 15;
        if (coordY_button + bar::square_Height <= 5) { 
            coordY_button += 15;
        }
    }

    return coordY_button;
    //Serial.println(coordY_button);
}