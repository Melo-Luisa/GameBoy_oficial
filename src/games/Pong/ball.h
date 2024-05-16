#define BALL
#include <Arduino.h>
#include <TFT_eSPI.h> 
#include <SPI.h>
class Ball{
    private:
        int x, y, vx, vy, circleRadius;
        
    public:
        Ball(int x, int y, int vx, int vy, int circleRadius);

        //funções
        int move(int y, int x, int vx, int vy, int circleRadius);
};


int Ball::move(int y, int x, int vx, int vy, int circleRadius){
    if (y <= 0 || y >= 240 - circleRadius) {
        vy = -vy;
    }
    x += vx;
    y += vy;  

    return x;
}