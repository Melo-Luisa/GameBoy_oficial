#pragma once
#include <stdlib.h>

#include  "config.h"
#include "obstacles.h"
#include "capivara.h"
#include "capivara_final.h"
#include "tree_final.h"



class logic{
    private:
        bool gameTwoOn;
        int numObstaculos, placar = 0, highScore;
        int x,vx;
        int leap, jump, level;
        obstacles obst;
        Capivara capi; 

    public:
        logic(int x, int vx, int numObstaculos): numObstaculos(numObstaculos), obst(x, vx), capi(leap, jump, level){}
        void drawCapi(TFT_eSprite &capiSprite);
        void drawObstacles(TFT_eSprite &obstaculosSprite, int numObstaculos);
        void drawBackground();
        void drawScore(TFT_eSprite &scoreSprite);
        int randomObstaculos(int numObstaculos);

        bool colision();
        
        void score();

        int getplacar() const;
        int getHighScore() const;

        void level_speed();
        void background();





};

void logic::background(){
    

}

/*Desenhar na tela a capivara*/
void logic::drawCapi(TFT_eSprite &capiSprite){
    capi.jump();
    capiSprite.fillSprite(TFT_BLACK);
    capiSprite.setSwapBytes(true);
    //capiSprite.fillCircle(30,  capi.getY() + 65, 10, TFT_WHITE);
    capiSprite.pushImage(0,capi.getY()+75,60,60,capivara_final);
    capiSprite.pushSprite(0, 190);


}


int logic::randomObstaculos(int numObstaculos){
    numObstaculos = random(1, 3);
    //Serial.println(numObstaculos);
    return numObstaculos;
}

/*Desenhar na tela os obstaculos
@note quadrados de inicio, alguma forma a mais? Arvores, desenho empilhada?*/
void logic::drawObstacles(TFT_eSprite &obstaculosSprite, int numObstaculos) {
    obst.move();
    obstaculosSprite.fillSprite(TFT_BLACK);

    obstaculosSprite.setSwapBytes(true);
    obstaculosSprite.pushImage(0,25,60,60,tree_final);

    obstaculosSprite.pushSprite(obst.getX(), 250);
}

/*Verifica se houve colisão com obstaculosc:\Users\luhco\Downloads\tree_final.c
@note FUNCIONA*/
bool logic::colision(){
    bool colisao = false;
    if(capi.getY() == 0 && obst.getX() <= obst.getVX()){
        colisao = true;
    }
    
    return colisao;

}

/*Contador de pontuação
@note funciona*/
void logic::score(){
    placar += 1;
    if (colision()) {
        if (placar > highScore) {
            highScore = placar;  // Atualiza o melhor placar
        }
        placar = 0;
    }
}

int logic::getplacar() const {return placar;}
int logic::getHighScore() const {return highScore;}

void logic::drawScore(TFT_eSprite &scoreSprite) {
    scoreSprite.fillSprite(TFT_WHITE);
    scoreSprite.setTextColor(TFT_BLACK);

    scoreSprite.drawString("Score: " + String(getplacar()), 110, 20, 4);

    scoreSprite.drawString("High Score: " + String(getHighScore()), 120, 55, 4);

    scoreSprite.pushSprite(100, 10);
}

/*Vai aumentando a velocidade conforme vai passando com mais pontuação */
void logic::level_speed() {
    switch (getplacar() / 100) {
        case 0:
            obst.setVX(10);
            break;
        case 1:
            obst.setVX(15);
            break;
        case 2:
            obst.setVX(20);
            break;
        case 3:
            obst.setVX(25);
            break;
        default:
            obst.setVX(30);  // Para pontuações acima de 300
            break;
    }
}

