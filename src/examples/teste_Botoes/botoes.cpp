#include "botoes.h"

//Construtor da Classe BOTAO
BOTAO::BOTAO(int pin){
    this-> pin = pin;
    pinMode(pin, INPUT);

}

//Ler botão
boolean BOTAO::read(){
    return(digitalRead(pin));
}

