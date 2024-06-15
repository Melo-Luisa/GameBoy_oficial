#pragma once
#include <Arduino.h>

#include "config.h"

class Capivara{
    private:
        int leap;
    public:
        Capivara( int leap):leap(leap){}
        int jump();
        int getLeap() const {return leap;}
};


int Capivara::jump(){
    if(digitalRead(button::azul) == LOW){
        leap += 10;
    }else{
        leap -= 10;
    }

    return leap;
}