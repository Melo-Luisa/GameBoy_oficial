#pragma once
#include <stdlib.h>

#include  "config.h"
#include "obstacles.h"
#include "capivara.h"
#include "img_capi.h"

class logic{
    private:
        bool gameTwoOn;
        int numObstaculos, placar = 0;
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
        
        int score(int placar);

        int getplacar() const;



};


/*Desenhar na tela a capivara*/
void logic::drawCapi(TFT_eSprite &capiSprite){
    capi.jump();
    capiSprite.fillSprite(TFT_BLACK);
    capiSprite.fillCircle(30,  capi.getY() + 65, 10, TFT_WHITE);
    //capiSprite.pushImage(0, 0, 96, 96, img_capi);
    /*X = 0
    Y = */
    capiSprite.pushSprite(0, 220);
    //Serial.println(capi.getY());

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

    obstaculosSprite.fillRect(5, 10, obs::obs_width, obs::obs_height, TFT_WHITE);
    //Serial.println(numObstaculos);
    
    //Se o número for 2, desenhar um segundo retângulo
    if (numObstaculos == 2) {
        // Você pode ajustar as coordenadas do segundo retângulo conforme necessário
        int secondRectX = 70; // Posição x do segundo retângulo
        int secondRectY = 25; // Posição y do segundo retângulo (mesma linha)
        obstaculosSprite.fillRect(secondRectX, secondRectY, obs::obs_width_1, obs::obs_height_1, TFT_RED);
        //obstaculosSprite.pushSprite(obst.getX(), 150);

       
    }
    
    obstaculosSprite.pushSprite(obst.getX(), 250);
    //Serial.println(obst.getX());
}

/*Verifica se houve colisão com obstaculos*/
bool logic::colision(){
    bool colisao = false;
    if( capi.getY() <= 0 && obst.getX() <= 5){
        colisao = true;
        Serial.println("Colidiu");
    }
    
    return colisao;

}

/*Contador de pontuação*/
int logic::score(int placar){
    placar += 1;
    if(colision()){
        placar = 0;
    }
}

int logic::getplacar() const {return placar;}

void logic::drawScore(TFT_eSprite &scoreSprite){

    scoreSprite.fillSprite(TFT_ORANGE);
    scoreSprite.setTextColor(TFT_WHITE);
    scoreSprite.drawString(String("ola"), 20,25,6);

    scoreSprite.pushSprite(200,10);


}
