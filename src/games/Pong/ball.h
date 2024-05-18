#pragma once
#include <Arduino.h>
#include <TFT_eSPI.h> 
#include <SPI.h>
#include "config.h"
class Ball{
    private:
        int x , y , vx , vy , circleRadius ;
        
    public:
        Ball(int x, int y, int vx, int vy, int circleRadius) 
            : x(x), y(y), vx(vx), vy(vy), circleRadius(circleRadius) {}

        void move();
        int getX() const { return x; }
        int getY() const { return y; }
        int getvx() const { return vx; }
        int getvy() const { return vy; }
        int getCircleRadius() const { return circleRadius; }
        
        void setX(int newX) { x = newX; }
        void setY(int newY) { y = newY; }
        void setVX(int newVX) { vx = newVX; }
        void setVY(int newVY) { vy = newVY; }
};


void Ball::move(){
    if (y <= 0 || y >= tela::height - circleRadius) {
        vy = -vy;
    }
    x += vx;
    y += vy;  

}
