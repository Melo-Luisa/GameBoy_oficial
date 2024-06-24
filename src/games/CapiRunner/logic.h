#pragma once
#include <stdlib.h>

#include  "config.h"
#include "obstacles.h"
#include "capivara.h"
#include "capivara_final.h"
#include "tree_final.h"

#define MAX_OBSTACULOS 2

struct Obstacle {
    int x;
    int y;
};

class logic{
    private:
        bool gameTwoOn;
        int numObstaculos, placar = 0, highScore;
        int x,vx;
        int leap, jump, level;
        obstacles obst;
        Capivara capi; 

        Obstacle obstaculos[MAX_OBSTACULOS] = {
            {5, 10},   // Posição do primeiro obstáculo
            {5, 15}   // Posição do segundo obstáculo
        };

        Obstacle obstaculos_size[MAX_OBSTACULOS] = {
            {10, 15},   // tamanho do primeiro obstáculo
            {10,15}   // tamanho do segundo obstáculo
        };

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





};


/*Desenhar na tela a capivara*/
void logic::drawCapi(TFT_eSprite &capiSprite){
    capi.jump();
    capiSprite.fillSprite(TFT_BLACK);
    capiSprite.setSwapBytes(true);
    //capiSprite.fillCircle(30,  capi.getY() + 65, 10, TFT_WHITE);
    capiSprite.pushImage(0,capi.getY()+75,60,60,capivara_final);
    capiSprite.pushSprite(0, 190);


}

// void setupRandom() {
//     randomSeed(analogRead(0));
// }

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
    Serial.println(numObstaculos);
    // for (int i = 0; i <= numObstaculos; i++) {
    //     int color = (i == 0) ? TFT_WHITE : TFT_WHITE;
    //     obstaculosSprite.fillRect(obstaculos[i].x, obstaculos[i].y, obstaculos_size[i].x, obstaculos_size[i].y, color);
    // }
    obstaculosSprite.setSwapBytes(true);
    //obstaculosSprite.fillCircle(30,  capi.getY() + 65, 10, TFT_WHITE);
    obstaculosSprite.pushImage(0,25,60,60,tree_final);

    //obstaculosSprite.pushSprite(obst.getX(), 250);
    obstaculosSprite.pushSprite(obst.getX(), 250);
    //Serial.println(obst.getX());
}

/*Verifica se houve colisão com obstaculosc:\Users\luhco\Downloads\tree_final.c
@note FUNCIONA*/
bool logic::colision(){
    bool colisao = false;
    if(capi.getY() == 0 && obst.getX() <= obst.getVX()){
        colisao = true;
        //Serial.println("Colidiu");
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
    //Serial.println(placar);
}

int logic::getplacar() const {return placar;}
int logic::getHighScore() const {return highScore;}

void logic::drawScore(TFT_eSprite &scoreSprite) {
    scoreSprite.fillSprite(TFT_BLACK);
    scoreSprite.setTextColor(TFT_WHITE);

    // Desenha o placar atual
    scoreSprite.drawString("Score: " + String(getplacar()), 110, 20, 4);

    // Desenha o melhor placar
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

