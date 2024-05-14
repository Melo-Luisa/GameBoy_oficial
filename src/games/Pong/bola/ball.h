#ifdef BALL
#define BALL
#include <Arduino.h>
#include <TFT_eSPI.h> 
#include <SPI.h>
class BALL{
    private:
        int x, y, vx, vy, circleRadius;
        
    public:
        BALL(int x, int y, int vx, int vy, int circleRadius);

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
