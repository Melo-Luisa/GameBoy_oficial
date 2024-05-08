#include <Arduino.h>
#include <TFT_eSPI.h>

#include "utils.h"
#include "button.h"
#define EIXO_Y 32
#define EIXO_X 36


class JOY: public main, public BALL{
    private:
        int coordY_old, coordY_new; 
        int EIXO_Y = 32; int EIXO_X = 36;   
    public:
        JOY(int coordY_old, int coordY_new):;

        //funções
        void move();
        void draw(TFT_eSprite &barra_joy)
        
};