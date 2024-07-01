#include <Arduino.h>

class BOTAO{
    private:
        int pin;
    
    public:
        //Construtor da classe BOTAO
        BOTAO(int pin);

        //Função pra ler os botões
        boolean read();
};