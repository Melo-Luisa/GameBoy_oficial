#pragma once

#include "config.h"

//obstaculos na tela
class obstacles{
    private:
        int x, vx;
    public:
        obstacles(int x, int vx): x(x), vx(vx){}
        void move();

        int getX() const {return x;}
        int getVX() const {return vx;}

        void setX(int newX) { x = newX; }


};

/*Move para frente, inicia em 480 (direita) e termina em < 0*/
void obstacles::move(){
    x -= vx;
    if(x < -vx){
        x = 490;
    }
    // Serial.print("X:");
    // Serial.println(x);

    // Serial.print("Velocidade:");
    // Serial.println(vx);    
}