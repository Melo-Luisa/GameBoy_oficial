#ifndef button_h
#define button_h


#include <Arduino.h>
#include <TFT_eSPI.h>

#include "button.h"
#include "utils.h"

class BUTTON : public main, public BUTTON{
private:
    int botao_azul = 34, botao_amarelo = 36; // setar pinos
    int coordY;

public:
    BUTTON(int botao_azul, int botao_amarelo, int coordY);

    void move();
    void draw(TFT_eSprite &barra_button);
};

#endif	
