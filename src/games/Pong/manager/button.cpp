#include "button.h"

BUTTON::BUTTON(int botao_azul, int botao_amarelo, int coordY, int square_Width, int square_Height){
    this->botao_azul = botao_azul;
    this->botao_amarelo = botao_amarelo;
    this->coordY = coordY;
    this->square_height = square_height;
    this->square_width = square_width;
    pinMode(botao_azul, PULLUP);
    pinMode(botao_amarelo, PULLUP);


}

void BUTTON::move(){
    if(digitalRead(botao_azul) == 0){ //se o botao azul for apertado 
        if(coordY+ (square_height) <= 230){ 
            coordY += 10;
        }
    
    }
    else if(digitalRead(botao_amarelo) == 0){ //se o botao azul for apertado 
        coordY -= 10;
        if(coordY+(square_height) == 50){ 
            coordY += 10;
        }
    
    }
}

void BUTTON::draw(TFT_eSprite &barra_button, int square_Width, int square_Height){
    barra_button.fillRect(80, coordY, square_Width, square_Height, TFT_WHITE);
    // não esta puxando a classe ball
    barra_button.pushToSprite(&ball, 220, 0);
    barra_button.fillRect(80, coordY, square_Width, square_Height, TFT_BLACK);
}