#pragma once
#include <Arduino.h>

#include "config.h"
#include "joystick.h"


class Barra{
    private:
       // int coordY_old, coordY_new; //JOYSTICK
        int coordY;
        int coordY_button = 100; //BUTTON
        int xAxisPin; int yAxisPin, central;
        Joystick joy;

        enum State {
            STOPPED,
            MOVING_UP,
            MOVING_DOWN
        };
        State currentState = STOPPED;
    public:
        Barra(int coordY, int coordY_button): coordY(coordY), coordY_button(coordY_button),joy(xAxisPin, yAxisPin, central){}

        //funções
        int move_joy();

        int move_button();
        
        
};


int Barra::move_joy(){
    int valueY = analogRead(joystick::eixo_x); //joystick se refere ao namespace
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


    switch (currentState) {
        case STOPPED:
            if (digitalRead(button::verde) == LOW) {
                currentState = MOVING_UP;
            } else if (digitalRead(button::azul) == LOW) {
                currentState = MOVING_DOWN;
            }
        break;

        case MOVING_UP:
            if (digitalRead(button::verde) == HIGH) {
                currentState = STOPPED;
            } else {
                coordY_button+=15;  // Mover a barra para cima
                //Serial.println("Movendo para cima");
            }
        break;

        case MOVING_DOWN:
            if (digitalRead(button::azul) == HIGH) {
                currentState = STOPPED;
            } else {
                coordY_button-=15;  // Mover a barra para baixo
                //Serial.println("Movendo para baixo");
            }
        break;
    }

    if (coordY_button < 0) {
        coordY_button = 0;  // Limite superior
    }
    if (coordY_button > 320 - 60) {
        coordY_button = 320 - 60;  // Limite inferior
    }


    //Serial.println(currentState);
    return coordY_button;

    //Serial.println(coordY_button);
}