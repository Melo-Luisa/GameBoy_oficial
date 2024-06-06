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
        int yAxisPin, xAxisPin;
        int  coordY;
        Ball bolinha; 
        Barra barra;

        int prevBallX; // Posição anterior da bola (inicializada fora da tela)
        int prevBallY; 
        int prevJoyY;
        int prevButtonY ;
        
    public:
        Juiz(int x, int y, int vx ,int vy, int countBlack, int countWhite, int circleRadius, int coordY): bolinha(y, x, vx, vy, circleRadius), barra(coordY ), prevBallX(-1), prevBallY(-1), prevJoyY(-1), prevButtonY(-1){
            this->countBlack = countBlack;
            this->countWhite = countWhite;
        }

        void draw_Ball(TFT_eSprite &ball); // desenha bola
        void placar(TFT_eSprite &placar, int countBlack, int countWhite); // desenha placar
        boolean hit_esquerda(int coordY); // retorna valor se atingiu esq
        boolean hit_direita(); // retorna valor se atingiu na dire
        boolean hit_superior();
        boolean hit_inferior();
        void atingir(); // verifica se atingiu
        void count(); //conta os pontos
        
        void draw_joy( TFT_eSprite &barra_joy);
        void draw_button( TFT_eSprite &barra_button);

        int getCountWhite() const;
        int getCountBlack() const;

        //void atualizarBolinha();
};



//Não funciona
boolean Juiz::hit_esquerda(int coordY) {

    //return bolinha.getX() + bolinha.getCircleRadius() == 0;
    boolean result_esq = false;
    //COLISÃO BARRA ESQUERDA
    if (bolinha.getX() <= 30 && (bolinha.getY() >= barra.move_joy() )  && bolinha.getY() <= (barra.move_joy() + (bar::square_Height)) ) {
       result_esq =  true;
       
    }
    return result_esq;
}

//Funciona
boolean Juiz::hit_direita() {
    // return bolinha.getX() >= 300 - bolinha.getCircleRadius();
    boolean result_dir = false;

    //COLISÃO BARRA DIREITA
    if (bolinha.getX() + bolinha.getCircleRadius() >= 430  && (bolinha.getY() >= barra.move_button(coordY) && bolinha.getY() <= (barra.move_button(coordY)+bar::square_Height))) {
        result_dir = true;
    }   
    
    return result_dir;
}



void Juiz::atingir() {
    if (hit_direita() || hit_esquerda(coordY)) {
        bolinha.setVX(-bolinha.getvx()); // Inverter a direção horizontal
        bolinha.setVY(-bolinha.getvy());
    }
   
}




void Juiz::count() {
    if (bolinha.getX() + tela::width < 0) { 
        bolinha.setX(tela::width - bolinha.getCircleRadius()); 

        countWhite += 1;
        
        if (countWhite == 10 || countBlack == 10) {
            countBlack = 0;
            countWhite = 0; 
        }
    } else if (bolinha.getX() >= tela::width + bar::square_Width) { // Se a bola atinge a borda direita
        bolinha.setX(bolinha.getCircleRadius() + bar::square_Height); // 
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
void Juiz::draw_joy( TFT_eSprite &barra_joy){
    barra.move_joy();
    barra_joy.fillSprite(TFT_BLACK);
    barra_joy.fillRect(20, 20, bar::square_Width, bar::square_Height, TFT_WHITE);
    barra_joy.pushSprite(10, barra.move_joy());
    

    // screen.pushSprite(0,0);
    // screen.fillRect(30, barra.move_joy(), bar::square_Width, bar::square_Height, TFT_BLACK);
    // barra_joy.fillRect(15, barra.move_joy(), bar::square_Width, bar::square_Height, TFT_WHITE);
    // barra_joy.pushToSprite(&screen, 0, 0);
    // barra_joy.fillRect(15, barra.move_joy(), bar::square_Width+20, bar::square_Height+20, TFT_BLACK);

}

//lado direito
void Juiz::draw_button(TFT_eSprite &barra_button ){
    barra.move_joy();
    barra_button.fillSprite(TFT_BLACK);
    barra_button.fillRect(20, 20, bar::square_Width, bar::square_Height, TFT_WHITE);
    barra_button.pushSprite(440, barra.move_button(coordY));
    // screen.fillRect(80, barra.move_button(coordY), bar::square_Width, bar::square_Height, TFT_BLACK);
    //barra_button.fillRect(80, barra.move_button(coordY), bar::square_Width, bar::square_Height, TFT_WHITE);
    // barra_button.pushToSprite(&screen,220, 0);
    // barra_button.fillRect(80, barra.move_button(coordY), bar::square_Width, bar::square_Height, TFT_BLACK);
}


void Juiz::draw_Ball(TFT_eSprite &ball){
     
    bolinha.move();
    ball.fillSprite(TFT_BLACK);
    ball.fillCircle(20, 20, bolinha.getCircleRadius(), TFT_RED);
    ball.pushSprite(bolinha.getX(), bolinha.getY());
    
}

void Juiz::placar(TFT_eSprite &placar, int countBlack, int countWhite){

    placar.fillSprite(TFT_ORANGE);
    // Desenhe texto no sprite
    placar.setTextColor(TFT_WHITE);
    placar.drawString(String(getCountBlack()), 20, 25, 7);
    placar.drawString("x", 50, 25, 4);
    placar.drawString(String(getCountWhite()), 80, 25, 7);

    // Exiba o sprite na tela
    placar.pushSprite(200, 10);
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

