#pragma once
#include <stdlib.h>

#include "obstacles.h"
#include "capivara.h"
#include "capivara_final.h"
#include "tree_final.h" 



class JuizCapi{
    private:
        int numObstaculos, placar = 0, highScore;
        int x,vx;
        int leap, jump, level;
        obstacles obst;
        Capivara capi; 

    public:
        JuizCapi(int x, int vx, int numObstaculos): numObstaculos(numObstaculos), obst(x, vx), capi(leap, jump, level){}
        void drawCapi(TFT_eSprite &capiSprite);
        void drawObstacles(TFT_eSprite &obstaculosSprite, int numObstaculos);

        void drawScore(TFT_eSprite &scoreSprite);
        int randomObstaculos(int numObstaculos);

        bool colision();
        
        void score();

        int getplacar() const;
        int getHighScore() const;

        void level_speed();





};


/*Desenhar na tela a capivara*/
void JuizCapi::drawCapi(TFT_eSprite &capiSprite){
    Serial.println("estou entrando na função drawCapi");
    capi.jump();
  
    capiSprite.setSwapBytes(true);
    //capiSprite.fillCircle(30,  capi.getY() + 75, 10, TFT_WHITE);
    capiSprite.pushImage(0,capi.getY(),60,60,capivara_final);
    capiSprite.fillSprite(TFT_BLACK);
    capiSprite.pushSprite(10, 190);


}


int JuizCapi::randomObstaculos(int numObstaculos){
    numObstaculos = random(1, 3);
    //Serial.println(numObstaculos);
    return numObstaculos;
}

/*Desenhar na tela os obstaculos
@note quadrados de inicio, alguma forma a mais? Arvores, desenho empilhada?*/
void JuizCapi::drawObstacles(TFT_eSprite &obstaculosSprite, int numObstaculos) {
     Serial.println("estou entrando na função drawOBSTACULOS");

    obst.move();
    obstaculosSprite.fillSprite(TFT_BLACK);

    obstaculosSprite.setSwapBytes(true);
    obstaculosSprite.pushImage(0,25,60,60,tree_final);

    obstaculosSprite.pushSprite(obst.getX(), 250);
}

/*Verifica se houve colisão com obstaculos
@note FUNCIONA*/
bool JuizCapi::colision(){
    bool colisao = false;
    if(capi.getY() == 0 && obst.getX() <= obst.getVX()){
        colisao = true;
    }
    
    return colisao;

}

/*Contador de pontuação
@note funciona*/
void JuizCapi::score(){
    placar += 1;
    if (colision()) {
        if (placar > highScore) {
            highScore = placar;  
        }
        placar = 0;
    }
}

int JuizCapi::getplacar() const {return placar;}
int JuizCapi::getHighScore() const {return highScore;}

void JuizCapi::drawScore(TFT_eSprite &scoreSprite) {
    Serial.println("estou entrando na função drawScore");

    scoreSprite.fillSprite(TFT_WHITE);
    scoreSprite.setTextColor(TFT_BLACK);

    scoreSprite.drawString("Score: " + String(getplacar()), 110, 20, 4);

    scoreSprite.drawString("High Score: " + String(getHighScore()), 120, 55, 4);

    scoreSprite.pushSprite(100, 10);
}

/*Vai aumentando a velocidade conforme vai passando com mais pontuação */
void JuizCapi::level_speed() {
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

