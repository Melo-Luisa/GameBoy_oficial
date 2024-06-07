
#pragma once
#include <Arduino.h>

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


void Ball::move() {
    x +=vx;
    y +=vy;

    // Colisão com a parede superior
    if (y - circleRadius <= 0) {
        vy = -vy;
        y = circleRadius;
    }

    // Colisão com a parede inferior
    if (y + circleRadius >= 320) { // Supondo que a altura da tela seja 320
        vy = -vy;
        y = 320 - circleRadius;
    }
    if (vx == 0 && vy == 0) {
        // A bola está parada, não fazer nada
        return;
    }
}
