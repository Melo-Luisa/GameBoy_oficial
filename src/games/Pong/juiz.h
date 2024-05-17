#pragma once
#include <Arduino.h>
#include <TFT_eSPI.h> 
#include <SPI.h>

#include "config.h"
#include "ball.h"
#include "barra.h"

class Juiz{

    private:
        int x, vx, y, vy, circleRadius; 
        int countBlack = 0; int countWhite = 0;
        int coordY_old, coordY_new, coordY;
        Ball bolinha; 
        Barra barra ;
        
    public:
        Juiz(int x, int y, int vx ,int vy, int countBlack, int countWhite, int circleRadius): bolinha(y, x, vx, vy, circleRadius), barra(coordY_old, coordY_new, coordY){}

        void draw_Ball(TFT_eSprite &ball, int x, int y, int circleRadius); // desenha bola
        void placar(TFT_eSprite &placar, int countBlack, int countWhite,  TFT_eSprite &ball); // desenha placar
        boolean hit_esquerda(); // retorna valor se atingiu esq
        boolean hit_direita(); // retorna valor se atingiu na dire
        void atingir(); // verifica se atingiu
        int count(int countWhite, int countBlack); //conta os pontos
        void draw_joy(TFT_eSprite &barra_joy, TFT_eSprite &ball);
        void draw_button(TFT_eSprite &barra_button, TFT_eSprite &ball);
};

void Juiz::draw_Ball(TFT_eSprite &ball, int x, int y, int circleRadius){
    
    ball.fillCircle(x, y, circleRadius, TFT_BLACK);
    ball.fillCircle(x, y, circleRadius, TFT_RED);
    ball.pushSprite(0, 0);
}

//é necessário colocar o paramentro da TFT_eSprite?

void Juiz::placar(TFT_eSprite &placar, int countBlack, int countWhite, TFT_eSprite &ball){


    Serial.print(countWhite);
    Serial.print("X");
    Serial.print(countBlack);
    Serial.println();

    placar.fillSprite(TFT_BLUE);
    // Desenhe texto no sprite
    placar.setTextColor(TFT_WHITE);
    placar.drawString(String(countBlack), 20, 25, 7);
    placar.drawString("x", 70, 25, 4);
    placar.drawString(String(countWhite), 120, 25, 7);

    // Exiba o sprite na tela
    placar.pushToSprite(&ball,85, 5, TFT_BLACK);
}

boolean Juiz::hit_direita(){
    boolean result_dir = false;

    //COLISÃO BARRA DIREITA - BUTTOn
    if ( (bolinha.move(y, x, vx, vy, circleRadius) + bolinha.move(y, x, vx, vy, circleRadius)) >= 300 && (y >= ((barra.move_button(coordY))) && y <= (barra.move_button(coordY) + bar::square_Height))) {
        result_dir = true;
        //Serial.println("Bateu direita");
    }   
    
    return result_dir;
}

boolean Juiz::hit_esquerda() {
    boolean result_esq = false;
    //COLISÃO BARRA ESQUERDA - JOY
    if ((bolinha.move(y, x, vx, vy, circleRadius) - bolinha.move(y, x, vx, vy, circleRadius)) == 0 && (bolinha.move(y, x, vx, vy, circleRadius) >= (barra.move_joy(coordY_old, coordY_new)) && bolinha.move(y, x, vx, vy, circleRadius) <= (barra.move_joy(coordY_old, coordY_new) + (bar::square_Height + bar::square_Width)))) {
        result_esq = true;
        //Serial.println("Bateu Esquerda");
    }
    return result_esq;
}

void Juiz::atingir() {
    if (hit_direita()) {
        vx = -vx;
        vy = -bolinha.move(y, x, vx, vy, circleRadius);
    }
    if (hit_esquerda()) {
        vx = -vx;
        vy = -bolinha.move(y, x, vx, vy, circleRadius);
    }
}

int Juiz::count(int countWhite, int countBlack){
    if (x <= 0) { // esquerda
        x = 240 - bolinha.move(y, x, vx, vy, circleRadius);
        countWhite +=1;
        //coloquei o ou mas não tenho certeza
        if(countWhite == 10 || countBlack == 10){
            countBlack = 0;
            countWhite = 0;
        }
    } else if (x >= 240 +20 ) {
        x = bolinha.move(y, x, vx, vy, circleRadius);
        countBlack += 1;
        
        if(countBlack == 10 || countBlack == 10){

            countBlack = 0;
            countWhite = 0;
        }
    }

    return countWhite;
}

void Juiz::draw_joy(TFT_eSprite &barra_joy, TFT_eSprite &ball){
    


    barra_joy.fillRect(15, barra.move_joy(coordY_old, coordY_new), bar::square_Width, bar::square_Height, TFT_WHITE);
    barra_joy.pushToSprite(&ball, 0, 0);
    barra_joy.fillRect(15, barra.move_joy(coordY_old, coordY_new), bar::square_Width, bar::square_Height, TFT_BLACK);

}

void Juiz::draw_button(TFT_eSprite &barra_button, TFT_eSprite &ball){
    barra_button.fillRect(80, barra.move_button(coordY), bar::square_Width, bar::square_Height, TFT_WHITE);
    // não esta puxando a classe ball
    barra_button.pushToSprite(&ball, 220, 0);
    barra_button.fillRect(80, barra.move_button(coordY), bar::square_Width, bar::square_Height, TFT_BLACK);
}

