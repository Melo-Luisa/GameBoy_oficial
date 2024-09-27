#pragma once
#include <stdlib.h>

#include "obstacles.h"
#include "capivara.h"
//imagens
#include "capivara_final.h"
#include "tree_final.h" 
#include "back_final.h" 



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
        void drawObstacles(TFT_eSprite &obstaculosSprite);
        void drawScore(TFT_eSprite &scoreSprite);
        int randomObstaculos(int numObstaculos);

        bool colision();
        
        void score();

        int getplacar() const;
    
        void setplacar(int valor){placar = valor;}
        int getHighScore() const;

        void level_speed();

        void backgroundEndCapi(TFT_eSPI &d, bool &gameCapiOn);



};


void JuizCapi::backgroundEndCapi(TFT_eSPI &d, bool &gameCapiOn){
    
    d.fillScreen(TFT_BLACK);
    d.drawCentreString("Voce bateu!" ,245, 120,4);
    d.drawCentreString("Score:" + String(getplacar()) ,245, 170,4);
    d.setTextSize(2);
    d.setTextColor(TFT_ORANGE);

    d.setTextColor(TFT_WHITE);
    gameCapiOn = false; 
    delay(3500);
    d.fillScreen(TFT_WHITE);
     
}


/*Desenhar na tela a capivara*/
void JuizCapi::drawCapi(TFT_eSprite &capiSprite){
    capi.jump();
    capiSprite.fillSprite(TFT_BLACK);
    capiSprite.setSwapBytes(true);
    //capiSprite.fillCircle(30,  capi.getY()+75, 10, TFT_WHITE);
    capiSprite.pushImage(5,capi.getY()+75,60,60,capivara_final);
    capiSprite.pushSprite(0, 70);



}



/*Desenhar na tela os obstaculos
@note quadrados de inicio, alguma forma a mais? Arvores, desenho empilhada?*/
void JuizCapi::drawObstacles(TFT_eSprite &obstaculosSprite) {
    obst.move();
    obstaculosSprite.fillSprite(TFT_BLACK);

    // obstaculosSprite.setSwapBytes(true);
    // obstaculosSprite.pushImage(0,25,60,60,tree_final);


    int rectWidth = 60;  // Largura do retângulo
    int rectHeight = 60; // Altura do retângulo
    int rectX = 0;       // Posição X do retângulo
    int rectY = 25;      // Posição Y do retângulo
    uint16_t rectColor = TFT_WHITE;  // Cor do retângulo

    obstaculosSprite.fillRect(rectX, rectY, rectWidth, rectHeight, rectColor); 

    obstaculosSprite.pushSprite(obst.getX(), 130);
}

/*Verifica se houve colisão com obstaculos
@note FUNCIONA*/
bool JuizCapi::colision() {
    bool colisao = false;
    const int toleranciaX = 15;  // Defina uma margem de erro para a coordenada X
    const int toleranciaY = 5;  // Defina uma margem de erro para a coordenada Y

    // Verifica se as coordenadas X e Y estão próximas o suficiente
    if (abs(capi.getY() - 0) <= toleranciaY && abs(obst.getX() - obst.getVX()) <= toleranciaX) {
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
         
       
    }
   
}

int JuizCapi::getplacar() const {return placar;}
int JuizCapi::getHighScore() const {return highScore;}

void JuizCapi::drawScore(TFT_eSprite &scoreSprite) {

    scoreSprite.fillSprite(TFT_WHITE);
    scoreSprite.setTextColor(TFT_BLACK);

    scoreSprite.drawString("Score: " + String(getplacar()), 110, 20, 4);

    scoreSprite.drawString("High Score: " + String(getHighScore()), 120, 55, 4);

    scoreSprite.pushSprite(100, 10);

}

/*Vai aumentando a velocidade conforme vai passando com mais pontuação */
void JuizCapi::level_speed() {
    switch (getplacar()/100 ) {
        case 0:
            obst.setVX(10);
            break;
        case 1:
            obst.setVX(20);
            break;
        case 2:
            obst.setVX(30);
            break;
        case 3:
            obst.setVX(40);
            break;
        default:
            obst.setVX(50);  // Para pontuações acima de 300
            break;
    }
}

