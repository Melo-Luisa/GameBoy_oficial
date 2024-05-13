// itens totais da main 

#include "main.cpp"
#include "pongConfig.h"
#include "bola/ball.h"
#include "barra/barra.h"

class Juiz: public BALL, public BARRA{
    private:
        int x, y, vx, vy, circleRadius; 
        int countBlack = 0; int countWhite = 0;
    public:
        Juiz(int x, int y, int vx, int vy, int circleRadius): BALL(x), BALL(circleRadius), BALL(y), BARRA(coordY_joy), BARRA(coordY){}

        void draw(TFT_eSprite &ball); // desenha bola
        void placar( TFT_eSprite &placar, int countBlack, int countWhite); // desenha placar
        boolean hit_esquerda(); // retorna valor se atingiu esq
        boolean hit_direita(); // retorna valor se atingiu na dire
        void atingir(); // verifica se atingiu
        void count(); //conta os pontos
};

void Juiz::draw(TFT_eSprite &ball){
    
    ball.setColorDepth(8);
    ball.createSprite(320, 240);

    ball.fillCircle(BALL::x, BALL::y, BALL::circleRadius, TFT_BLACK);
    ball.fillCircle(BALL::x, BALL::y, BALL::circleRadius, TFT_RED);
    ball.pushSprite(0, 0);
}

void Juiz::placar(TFT_eSprite &placar, int countBlack, int countWhite, TFT_eSprite &ball){
    placar.setColorDepth(8);
    placar.createSprite(120, 50);
    placar.setTextDatum(MC_DATUM); 

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

boolean Juiz::hit_direita(BALL::circleRadius, ){
    boolean result_dir = false;

    //COLISÃO BARRA DIREITA - BUTTOn
    if ( (BALL::x + BALL::circleRadius) >= 300 && (y >= ((BARRA::coordY)) && y <= (BARRA::coordY + barra::square_Height))) {
        result_dir = true;
        //Serial.println("Bateu direita");
    }   
    
    return result_dir;
}

boolean Juiz::hit_esquerda(){
    boolean result_esq = false;
    //COLISÃO BARRA ESQUERDA - JOY
    if ((BALL::x - BALL::circleRadius) == 0 && (y >= ((BARRA::coordY_joy))  && BALL::y <= (BARRA::coordY_joy + (barra::square_Height + barra::square_Width))) ) {
        result_esq = true;
        //Serial.println("Bateu Esquerda");
    }
    return result_esq;
}

void Juiz::atingir(){
    if(Juiz::hit_direita()){
        vx = -vx;
        vy = -vy;
    }
    if(Juiz::hit_esquerda()){
        vx = -vx;
        vy = -vy;
    }
}

int Juiz::count(){
    if (x <= 0) { // esquerda
        x = 240 - circleRadius;
        countWhite +=1;
        //coloquei o ou mas não tenho certeza
        if(countWhite == 10 || countBlack == 10){
            countBlack = 0;
            countWhite = 0;
        }
    } else if (x >= 240 +20 ) {
        x = circleRadius;
        countBlack += 1;
        
        if(countBlack == 10 || countBlack == 10){

            countBlack = 0;
            countWhite = 0;
        }
    }
}