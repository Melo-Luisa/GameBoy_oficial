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


};

void obstacles::move(){
    x += vx;
    if(x > tela::width){
        x = 0;
    }
}