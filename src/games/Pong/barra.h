#pragma once
#include <Arduino.h>
#include <TFT_eSPI.h> 
#include <SPI.h>

#include "config.h"
#include "joystick.h"


class Barra{
    private:
       // int coordY_old, coordY_new; //JOYSTICK
        int coordY; //BUTTON
        int xAxisPin; int yAxisPin, central;
        Joystick joy;
    public:
        Barra(int coordY): coordY(coordY),joy(xAxisPin, yAxisPin, central){}

        //funções
        int move_joy();

        int move_button(int coordY);
        
        
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
    if (coordY < 0) {
        coordY = 0;
    } else if (coordY > 220) { // Assumindo que 220 é o limite superior da barra?
        coordY = 220;
    }
    
    return coordY;
}

int Barra::move_button(int coordY) {
    if (digitalRead(button::azul) == LOW) { // botão azul pressionado
        if (coordY + bar::square_Height <= 320) {
            coordY += 10;
        }
        Serial.println("azul");
    }
    else if (digitalRead(button::vermelho) == LOW) { // botão amarelo pressionado
        coordY -= 10;
        if (coordY + bar::square_Height == 50) { 
            coordY += 10;
        }
        Serial.println("vermelho");
    }

    return coordY;
}
