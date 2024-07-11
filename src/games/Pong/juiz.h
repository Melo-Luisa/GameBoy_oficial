
#pragma once

#include "config.h"
#include "ball.h"
#include "barra.h"

/*classe Juiz tem como objetivo fazer a logica do jogo Pong
- Private - variaveis básicas
- Public - funções utilizadas  */
class Juiz{

    private:

        bool gamePongOn ;
        int countBlack = 0; int countWhite = 0;
        int  coordY, coordY_button;
        int x, y,vx,vy,circleRadius;
        Ball bolinha; 
        Barra barra;

        
    public:
        Juiz(int x, int y, int vx, int vy, int circleRadius, int coordY, int coordY_button): bolinha(y, x, vx, vy, circleRadius), barra(coordY, coordY_button){
            this->countBlack = countBlack;
            this->countWhite = countWhite;
        }

        void end(TFT_eSprite &abertura, bool &gameOn);
        void init(TFT_eSprite &abertura); 
        void draw_Ball(TFT_eSprite &ball); // desenha bola
        void placar(TFT_eSprite &placar, int countBlack, int countWhite); // desenha placar
        boolean hit_esquerda(int coordY); // retorna valor se atingiu esq
        boolean hit_direita(int coordY_button); // retorna valor se atingiu na dire
        boolean hit_superior();
        boolean hit_inferior();
        void atingir(); // verifica se atingiu
        void count(TFT_eSprite &abertura); //conta os pontos
        
        void draw_joy( TFT_eSprite &barra_joy);
        void draw_button( TFT_eSprite &barra_button, int coordY_button);

        int getCountWhite() const;
        int getCountBlack() const;
        void setCountBlack(int value);
        void setCountWhite(int value);

};

/*Função para o final do jogo - termino
@param TFT  abertura
@param int  countBlack, countWhite
@param bool  gameOn
*/
void Juiz::end(TFT_eSprite &abertura, bool &gameOn){
    abertura.fillScreen(TFT_BLACK);
    abertura.drawString("Fim de Jogo" ,367/2, 120,4);
    gamePongOn = false;
    Serial.println("End");

    
}

/*função de abertura
@param TFT_eSprite-&abertura
*/
void Juiz::init(TFT_eSprite &abertura){
    abertura.fillScreen(TFT_BLACK);

    abertura.setTextColor(TFT_WHITE);
    abertura.setTextSize(3);
    abertura.setTextDatum(TC_DATUM);
    
    abertura.drawString("PONG", 367/2, 120,4); 

    
    abertura.pushSprite(60,10);
}
  
/*Verifica se houve colisão do lado *esquerdo* da tela - barra do joystick
@param coordY
@return result_esq
*/
boolean Juiz::hit_esquerda(int coordY) {

    boolean result_esq = false;
    if (bolinha.getX() <= 20 && 
    ((bolinha.getY() >= barra.move_joy() )  && bolinha.getY() <= (barra.move_joy() + (bar::square_Height)) )) {
       result_esq =  true;

    }
    return result_esq;
}


/*Verifica se houve colisão do lado *direito* da tela - barra do Button
@param coordY_button
@return result_dir

*/
boolean Juiz::hit_direita(int coordY_button) {
   boolean result_dir = false;
    if (bolinha.getX() >= 440 &&
     (bolinha.getY() >= ((barra.move_button())) && bolinha.getY() <= (barra.move_button() + bar::square_Height))) {
        result_dir = true;
    }   
    
    return result_dir;
}


/*Caso as funções hit_esquerda(), hit_direita() tenham obtido sucesso, a função atingir muda a direção da bola.*/
void Juiz::atingir() {
    if (hit_esquerda(coordY)) {
        bolinha.setVX(-bolinha.getvx());
        bolinha.setVY(bolinha.getvy());
    }
    if(hit_direita(coordY_button)){
        bolinha.setVX(-bolinha.getvx());
        bolinha.setVY(bolinha.getvy());
    }
   
}


/*Função dois em um: conta os pontos e quando a bola sai da tela ele reseta do lado oposto
- Primeiro lado sendo da esquerda
- Segundo sendo o lado direito 
@note Alterar o nome da função*/
void Juiz::count(TFT_eSprite &abertura) {
    //esquerda
    if (bolinha.getX() < -55) { 
        bolinha.setX(tela::width - 45); 
        countWhite += 1;
    //direita
    } else if (bolinha.getX() >= tela::width + bolinha.getCircleRadius() ) { 
        bolinha.setX(bolinha.getCircleRadius()); // Coloca a bola perto da
        countBlack += 1;    
    }
}


/*Guarda o valor do placar e retorna na função do placar*/
int Juiz::getCountWhite() const {
    return countWhite;
}


/*Guarda o valor do placar e retorna na função do placar*/
int Juiz::getCountBlack() const {
    return countBlack;
}

void Juiz::setCountBlack(int value) {
    countBlack = value;
}

void Juiz::setCountWhite(int value) {
    countWhite = value;
}



/*Função tem como objetivo desenhar na tela a barra do lado esquerdo, dentro da sua sprite mesmo - Joystick
@param TFT barra_joy*/
void Juiz::draw_joy( TFT_eSprite &barra_joy){
    barra.move_joy();
    barra_joy.fillSprite(TFT_BLACK);
    barra_joy.fillRect(20, 55, bar::square_Width, bar::square_Height, TFT_WHITE);
    barra_joy.pushSprite(0, barra.move_joy());
    Serial.println(barra.move_joy());
    
}

/*Função tem como objetivo desenhar na tela a barra do lado direito, dentro da sua sprite mesmo - Botão
@param TFT barra_button
@note Tirar "coordY_button"*/
void Juiz::draw_button(TFT_eSprite &barra_button, int coordY_button ){
    barra.move_joy();
    barra_button.fillSprite(TFT_BLACK);
    barra_button.fillRect(20, 20, bar::square_Width, bar::square_Height, TFT_WHITE);
    barra_button.pushSprite(420, barra.move_button());
    //Serial.println(barra.move_button());
}

/*Função tem como objetivo desenhar na tela a bola
@param TFT ball*/
void Juiz::draw_Ball(TFT_eSprite &ball){
     
    bolinha.move();
    ball.fillSprite(TFT_BLACK);
    ball.fillCircle(40, 40, bolinha.getCircleRadius(), TFT_RED);
    ball.pushSprite(bolinha.getX(), bolinha.getY());
    
}

/*Função tem como objetivo desenhar placar na tela
@param TFT placar
@param int countBlack, countWhite*/
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
