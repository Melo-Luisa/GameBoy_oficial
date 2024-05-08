#include <Arduino.h>
#include <TFT_eSPI.h>

#include "main.h"
#include "button.h"
#include "joy.h"


class BALL: public main, public BUTTON, public JOY{
    private:
        int x, y, vx, vy, circleRadius;
        int countWhite, countBlack;
        
    public:
        BALL(int x, int y, int vx, int vy, int circleRadius, int countWhite, int countBlack);

        //funções
        void move();
        void placar(TFT_eSprite &placar);
        void draw(TFT_eSprite &ball);
        boolean hit_direita();
        boolean hit_esquerda();
};