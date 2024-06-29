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
    int valueY = analogRead(joystick::eixo_y); //joystick se refere ao namespace
    Direction directionY = joy.getDirectionY(valueY);
    
    switch (directionY) {
        case UP:
            coordY -= 10;
            break;
        case DOWN:
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
    if (digitalRead(button::verde) == LOW) { 
        if (coordY_button + bar::square_Height <= 250) {
            coordY_button += 10;
        }
    }
    //baixo
    else if (digitalRead(button::azul) == LOW) { // botão amarelo pressionado
        coordY_button -= 15;
        if (coordY_button + bar::square_Height == 50) { 
            coordY_button += 15;
        }
    }

    return coordY_button;
}