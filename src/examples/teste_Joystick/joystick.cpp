#include "joystick.h"

//Construtor classe JOYSTICK
JOYSTICK::JOYSTICK(int EIXO_X, int EIXO_Y){
    this->EIXO_X = EIXO_X;
    this->EIXO_Y = EIXO_Y;

    pinMode(EIXO_X, INPUT);
    pinMode(EIXO_Y, INPUT);
}

void JOYSTICK::debug(){
    Serial.print("X: " + String(analogRead(EIXO_X)));
    Serial.println(" - Y: " + String(analogRead(EIXO_Y)));

}

int JOYSTICK::read_raw_X(){
    int readRawX = analogRead(EIXO_X);
    return readRawX;
}

int JOYSTICK::read_raw_Y(){
    int readRawY = analogRead(EIXO_Y);
    return readRawY;
}

int JOYSTICK::coord_X(){ 
    int coordX = map(analogRead(EIXO_X), 0, 4095, 0, 300); //NÃO ESTÁ O VALOR CHEIO DA TELA P/ A BOLINHA NÃO PASSAR. VISTO QUE 0,0 DA BOLINHA É SUP. ESQ.
    //NÃO SEI SE É A MELHOR FORMA DE IMPLEMENTAR ESSE CÓDIGO, SEM O VALOR CHEIO DA TELA. 
    return coordX;

};

int JOYSTICK::coord_Y(){
    //MESMO "PROBLEMA DO COORD X EM RELAÇÃO AO TAMANHO DA TELA/LIMITES DO MAP"
    int coordY = map(analogRead(EIXO_Y), 0, 4095, 0, 220);
    return coordY;

}





