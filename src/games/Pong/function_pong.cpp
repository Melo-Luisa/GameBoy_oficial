#include "pong.h"


void update_Score(TFT_eSprite placar, int countBlack, int countWhite){
    
    Serial.print(countWhite);
    Serial.print("X");
    Serial.print(countBlack);
    Serial.println();

    placar.fillSprite(TFT_BLUE);
    // Desenhe texto no sprite
    placar.setTextColor(TFT_WHITE);
    placar.drawString(String(countBlack), 45, 20);
    placar.drawString("X", 55, 20);
    placar.drawString(String(countWhite), 65, 20);
    placar.fontHeight(25);

    // Exiba o sprite na tela
    placar.pushSprite(0, 0);

}


boolean hit_direita(int x, int circleRadius, int coordY_B2, int square_Height) {

    boolean result_dir = false;

    //COLISÃO BARRA DIREITA
    if ( (x + circleRadius) >= 300 && (y >= ((coordY_B2)) && y <= (coordY_B2+square_Height))) {
        result_dir = true;
        //Serial.println("Bateu direita");
    }   
    
    return result_dir;
    
}

boolean hit_esquerda(int x, int circleRadius, int coordY_B2, int square_Height, int square_Width){
    boolean result_esq = false;
    //COLISÃO BARRA ESQUERDA
    if ((x - circleRadius) == 0 && (y >= ((coordY_B1 ))  && y <= (coordY_B1 + (square_Height + square_Width))) ) {
        result_esq = true;
        //Serial.println("Bateu Esquerda");
    }
    return result_esq;
}

void ball_a(int x, int y, int vy, int vx, int countBlack, int countWhite, int circleRadius, TFT_eSprite ball){
    //--------------BOLINHA---------------
    ball.fillCircle(x, y, circleRadius, TFT_BLACK);
    
    if (y <= 0 || y >= d.height() - circleRadius) {
        vy = -vy;
    }
    x += vx;
    y += vy;   
    if (x <= 0) { // esquerda
        x = d.width() - circleRadius;
        countWhite +=1;
        //coloquei o ou mas não tenho certeza
        if(countWhite == 10 || countBlack == 10){
            countBlack = 0;
            countWhite = 0;
        }
    } else if (x >= d.width() +20 ) {
        x = circleRadius;
        countBlack += 1;
        
        if(countBlack == 10|| countBlack == 10){

            countBlack = 0;
            countWhite = 0;
        }
    }
    //devo colocar todos os argumentos?
    if(hit_direita(x, circleRadius, coordY_B2, square_Height)){
        vx = -vx;
        vy = -vy;
    }
    if(hit_esquerda( x, circleRadius, coordY_B2, square_Height,square_Width)){
        vx = -vx;
        vy = -vy;
    }

    ball.fillCircle(x, y, circleRadius, TFT_RED);
    ball.pushSprite(0, 0);


   
}

void joystick_m(int coordY_B1, int coordY_B1_antiga, TFT_eSprite barra1, int square_Width, int square_Height){
    
    //----------------BARRA JOYSTICK-------------


    //coordenadas do joystick
    coordY_B1 = 100;//map(analogRead(EIXO_Y), 0, 4095, 0, 220);

    coordY_B1_antiga = 100;//map(analogRead(EIXO_Y), 0, 4095, 0, 220);

    //barra do joystick
    barra1.fillRect(15, coordY_B1, square_Width, square_Height, TFT_WHITE);
    barra1.pushToSprite(&ball, 0, 0);
    barra1.fillRect(15, coordY_B1, square_Width, square_Height, TFT_BLACK);
    //Serial.println(analogRead(EIXO_Y));

    coordY_B1_atual = map(analogRead(EIXO_Y), 0, 4095, 0, 220);
    //cima
    if(coordY_B1_atual > coordY_B1_antiga){
        coordY_B1 += 10;
    }//baixo
    if(coordY_B1_atual < coordY_B1_antiga){
        coordY_B1 -= 10;

    }
    

}

void button_m(int botao_azul, int botao_amarelo, int coordY_B2,TFT_eSprite barra2 ){
    //----------------BARRA BOTOES-------------
    //baixo
    if(digitalRead(botao_azul) == 0){ //se o botao azul for apertado 
        if(coordY_B2+(square_Height) <= 230){ 
            coordY_B2 += 10;
        }
    
    }
    else if(digitalRead(botao_amarelo) == 0){ //se o botao azul for apertado 
        coordY_B2 -= 10;
        if(coordY_B2+(square_Height) == 50){ 
            coordY_B2 += 10;
        }
    
    }
    

    //barra do botoes
    barra2.fillRect(80, coordY_B2, square_Width, square_Height, TFT_WHITE);
    barra2.pushToSprite(&ball, 220, 0);
    barra2.fillRect(80, coordY_B2, square_Width, square_Height, TFT_BLACK);
}