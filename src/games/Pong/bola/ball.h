#pragma once 

#ifndef BALL
#define BALL
#include <Arduino.h>
#include <TFT_eSPI.h> 
#include <SPI.h>
class Ball{
    private:
        int _x, _y, _vx, _vy, _circleRadius;
        
    public:
        Ball(int x, int y, int vx, int vy, int circleRadius){}

        //funções
        void move();
};


void BALL::move(){
    if (y <= 0 || y >= 240 - circleRadius) {
        vy = -vy;
    }
    x += vx;
    y += vy;  

}
#endif
