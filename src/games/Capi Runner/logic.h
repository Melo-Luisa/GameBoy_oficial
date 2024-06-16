#pragma once

#include  "config.h"
#include "obstacles.h"
#include "capivara.h"
#include "img_capi.h"

class logic{
    private:
        bool gameTwoOn;
        int x,vx;
        int leap;
        obstacles obst;
        Capivara capi; 

    public:
        logic():obst(x, vx), capi(leap){}
        void drawCapi(TFT_eSprite &capiSprite);
        void drawObstacles(TFT_eSprite &obstaculos);
        void drawBackground();

        bool colision();

        int score();


};


/*Desenhar na tela o boneco do usuário
@note Capivara, capissauro ou ?*/
void logic::drawCapi(TFT_eSprite &capiSprite){
    int Ycap = capi.jump();
    capiSprite.fillSprite(TFT_BLACK);
    capiSprite.pushImage(0, 0, 96, 96, img_capi);
    capiSprite.pushSprite(0, Ycap, TFT_BLACK);

}

/*Desenhar na tela os obstaculos
@note quadrados de inicio, alguma forma a mais? Arvores, desenho empilhada?*/
void logic::drawObstacles(TFT_eSprite &obstaculos) {
    // Mover os obstáculos
     obst.move();
    
    // Limpar a área de desenho
    obstaculos.fillSprite(TFT_BLACK);
    
    // Desenhar o obstáculo na nova posição
    obstaculos.fillRect(25, 25, obs::obs_width, obs::obs_width, TFT_WHITE);
    
    // Atualizar a tela com o sprite desenhado
    obstaculos.pushSprite(obst.getX(), 100);
}

// /*Verifica se houve colisão com obstaculos*/
// bool logic::colision(){


// }

// /*Contador de pontuação*/
// int logic::score(){

// }
