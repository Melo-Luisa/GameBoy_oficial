#pragma once
#include <Arduino.h>

#include "config.h"

class Capivara{
    private:
        int leap = 220;
    public:
        Capivara( int leap):leap(leap){}
        int jump();
        int getLeap() const {return leap;}
};


int Capivara::jump(){
    if(digitalRead(button::azul) == LOW){
        Serial.println(digitalRead(button::azul));
        leap -= 20;
    }
    if(leap == 0){
        leap = 220;
    }
    return leap;
}