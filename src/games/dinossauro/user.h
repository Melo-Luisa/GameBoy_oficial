#pragma once
#include <Arduino.h>

#include "config.h"

class User{
    private:
        int leap;
    public:
        User( int leap):leap(leap){}
        int jump();
};


int User::jump(){
    if(digitalRead(button::azul) == LOW){
        leap += 10;
    }else{
        leap -= 10;
    }

    return leap;
}