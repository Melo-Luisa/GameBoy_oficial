#pragma once
#include <Arduino.h>

#include "config.h"


class Capivara {
    private:
        int leap ;
        bool isJumping;
        const int jumpHeight;
        const int groundLevel;
        int velocity;
    public:
        Capivara(int initialLeap, int jumpHeight, int groundLevel) 
            : leap(initialLeap), isJumping(false), jumpHeight(jumpHeight), groundLevel(groundLevel), velocity(0) {}

        int jump();
        int getY() const { return leap; }
};

int Capivara::jump() {
    // Verifique se o botão está pressionado
    if (digitalRead(button::azul) == LOW && !isJumping) {
        isJumping = true;
        velocity = -10; // Valor negativo para iniciar o pulo
    }

    // Atualiza a posição vertical da bolinha
    if (isJumping) {
        leap += velocity;
        velocity += 2; // Aceleração para simular gravidade

        // Verifica se a bolinha chegou ao chão
        if (leap >= groundLevel) {
            leap = groundLevel;
            isJumping = false;
            velocity = 0;
        }
    }
    return leap;
    //Serial.println(leap); // Imprime a posição da bolinha para debug
}
