#pragma once
#include <Arduino.h>
#include <TFT_eSPI.h> 
#include <SPI.h>

#include "config.h"
#include "ball.h"
#include "barra.h"

class Juiz{

    private:
        int countBlack = 0; int countWhite = 0;
        int coordY_old, coordY_new, coordY;
        Ball bolinha; 
        Barra barra ;
        
    public:
        Juiz(int x, int y, int vx ,int vy, int countBlack, int countWhite, int circleRadius): bolinha(y, x, vx, vy, circleRadius), barra(coordY_old, coordY_new, coordY){}

        void draw_Ball(TFT_eSprite &ball); // desenha bola
        void placar(TFT_eSprite &placar, int countBlack, int countWhite,  TFT_eSprite &ball); // desenha placar
        boolean hit_esquerda(); // retorna valor se atingiu esq
        boolean hit_direita(); // retorna valor se atingiu na dire
        void atingir(); // verifica se atingiu
        void count(); //conta os pontos
        
        void draw_joy(TFT_eSprite &barra_joy, TFT_eSprite &ball);
        void draw_button(TFT_eSprite &barra_button, TFT_eSprite &ball);

        int getCountWhite() const;
        int getCountBlack() const;
};



void Juiz::draw_Ball(TFT_eSprite &ball){
    bolinha.move();
    ball.fillCircle(bolinha.getX(), bolinha.getY(), bolinha.getCircleRadius(), TFT_RED);
    ball.pushSprite(0, 0);
    ball.fillCircle(bolinha.getX(), bolinha.getY(), bolinha.getCircleRadius(), TFT_BLACK);
    
}

void Juiz::placar(TFT_eSprite &placar, int countBlack, int countWhite, TFT_eSprite &ball){

    placar.fillSprite(TFT_BLACK);
    // Desenhe texto no sprite
    placar.setTextColor(TFT_WHITE);
    placar.drawString(String(getCountBlack()), 20, 25, 7);
    placar.drawString("x", 50, 25, 4);
    placar.drawString(String(getCountWhite()), 80, 25, 7);

    // Exiba o sprite na tela
    placar.pushToSprite(&ball,120, 10, TFT_BLACK);
}

boolean Juiz::hit_esquerda() {
    return bolinha.getX() <= 0;
}

boolean Juiz::hit_direita() {
    return bolinha.getX() >= tela::height - bolinha.getCircleRadius();
}

void Juiz::atingir() {
    if (hit_direita() || hit_esquerda()) {
        bolinha.setVX(-bolinha.getvx()); // Inverter a direção horizontal
    }
}

void Juiz::count() {
    if (bolinha.getX() <= 0) { 
        bolinha.setX(tela::height - bolinha.getCircleRadius()); 
        bolinha.setY(tela::width / 2); // Centralizar verticalmente
        bolinha.setVX(-bolinha.getvx()); // Inverter a direção horizontal
        countWhite += 1;
        
        if (countWhite == 10 || countBlack == 10) {
            countBlack = 0;
            countWhite = 0; 
        }
    } else if (bolinha.getX() >= tela::width - bolinha.getCircleRadius()) { // Se a bola atinge a borda direita
        bolinha.setX(bolinha.getCircleRadius()); // Reiniciar a posição da bola para o centro
        bolinha.setY(tela::height / 2);
        bolinha.setVX(-bolinha.getvx()); // Inverter a direção
        bolinha.setVY(-bolinha.getvy());
        countBlack += 1;
        
        // Reiniciar os contadores se um dos jogadores alcançar 10 pontos
        if (countBlack == 10 || countWhite == 10) {
            countBlack = 0;
            countWhite = 0;
        }
    }
}

int Juiz::getCountWhite() const {
    return countWhite;
}

int Juiz::getCountBlack() const {
    return countBlack;
}

//lado esq
void Juiz::draw_joy(TFT_eSprite &barra_joy, TFT_eSprite &ball){
    
    barra_joy.fillRect(15, barra.move_joy(coordY_old, coordY_new), bar::square_Width, bar::square_Height, TFT_WHITE);
    barra_joy.pushToSprite(&ball, 0, 0);
    barra_joy.fillRect(15, barra.move_joy(coordY_old, coordY_new), bar::square_Width, bar::square_Height, TFT_BLACK);

}

//lado direito
void Juiz::draw_button(TFT_eSprite &barra_button, TFT_eSprite &ball){

    barra_button.fillRect(80, barra.move_button(coordY), bar::square_Width, bar::square_Height, TFT_WHITE);
    barra_button.pushToSprite(&ball,220, 75);
    barra_button.fillRect(80, barra.move_button(coordY), bar::square_Width, bar::square_Height, TFT_BLACK);
}


















// boolean Juiz::hit_direita(){
//     boolean result_dir = false;

//     //COLISÃO BARRA DIREITA - BUTTOn
//     if ( (bolinha.getX() + bolinha.getCircleRadius()) >= 300 && (bolinha.getY() >= ((barra.move_button(coordY))) && y <= (barra.move_button(coordY) + bar::square_Height))) {
//         result_dir = true;
//         //Serial.println("Bateu direita");
//     }   
    
//     return result_dir;
// }

// boolean Juiz::hit_esquerda() {
//     boolean result_esq = false;
//     //COLISÃO BARRA ESQUERDA - JOY
//     if ((bolinha.getX() - bolinha.getCircleRadius()) == 0 && (bolinha.getY() >= (barra.move_joy(coordY_old, coordY_new)) && bolinha.getY() <= (barra.move_joy(coordY_old, coordY_new) + (bar::square_Height + bar::square_Width)))) {
//         result_esq = true;
//         //Serial.println("Bateu Esquerda");
//     }
//     return result_esq;
// }

