#include <Arduino.h>
#include <TFT_eSPI.h> 
#include <SPI.h>
#define EIXO_X  33
#define EIXO_Y  32


TFT_eSPI d = TFT_eSPI();  //init display

TFT_eSprite ball = TFT_eSprite(&d);
TFT_eSprite barra1 = TFT_eSprite(&d);
TFT_eSprite barra2 = TFT_eSprite(&d);

//Ball Settings
int circleRadius =10; 
int vx = 10, vy = 10; //velocidade da bolinha
int x = 100, y = 50;

int square_Width = 10;
int square_Height = 60;

//Barra joystick
int coordX_B1 = 15;
int coordY_B1 = 100;

int coordY_B1_atual = 100;
int coordY_B1_antiga = 100;


//Barra botoes
int coordY_B2 = 100; //eh y

int botao_azul = 34; //azul
int botao_amarelo = 35; // amarelo

//SCORE PLAYERS
int countBlack = 0;
int countWhite = 0;

void update_Score(){
    Serial.print(countWhite + " | ");
    Serial.print(countBlack);
    Serial.println();
}


boolean hit() {

    boolean result = false;

    //COLISÃO BARRA DIREITA
    if((x >=320) && y == coordY_B2){
        result = true;
        Serial.println("BATEU NA B2"); 


    }

    //COLISÃO BARRA ESQUERDA
    if((x <0) && y == coordY_B1){
        result = true;
        Serial.println("BATEU NA B1");

    }


    return result;
/*
    if(( x <= (15 + square_Width) && x >= 15) && 
    (( y <= (coordY_B1 + square_Height) && y >= coordY_B1 ) &&  y <= (coordY_B2 + square_Height) && y >= coordY_B2 )){
        result = true;
    }

    return result;
*/

    
}





void ball_a(){
    //--------------BOLINHA---------------
    ball.fillCircle(x, y, circleRadius, TFT_BLACK); //apaga a bola antiga
    /*ANIMAÇÃO DA BOLA*/



    //Colisão da Bolinha com X - Passou da Barra e NÃO BATEU na Barra - PONTUAÇÃO
    if((x<= 0) || (x>= d.width() - circleRadius)){
        //Serial.println("GOL PORRA");
        //vx = -vx

    }
    

   //Colisão da Bolinha com Y - BATE E VOLTA
    if((y<= 0)|| (y >= d.height() - circleRadius)){
        vy = -vy;
        //Serial.print("Toquei nos cantos - Y");
    }

    if(hit()){
        vy = -vy;
        vx = -vx;
        
    }

    x += vx;
    y += vy;


    //BOLINHA TELA
    ball.fillCircle(x,y,circleRadius, TFT_RED);
    ball.pushSprite(0,0);

   
}


 


void joystick_m(){
    
    //----------------BARRA JOYSTICK-------------

    //coordenadas do joystick
    // coordY_B1 = map(analogRead(EIXO_Y), 0, 4095, 0, 220);

    coordY_B1_antiga = map(analogRead(EIXO_Y), 0, 4095, 0, 220);

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
    //Serial.print(coordY_B1_antiga);
    //Serial.println(coordY_B1_atual);
}

void button_m(){
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

/*//-----------------BARRA BOTOES-----------------

    //baixo
    if(digitalRead(botao_azul) == 0){ //se o botao azul for apertado 
        if(coordY_B2+(square_Height) <= 230){ 
            coordY_B2 += 10;
            /*100 + 30 <= 240? Sim
            
            190 maximo
            
            
        }
    
    }
    else if(digitalRead(botao_amarelo) == 0){ //se o botao azul for apertado 
        coordY_B2 -= 10;
        if(coordY_B2+(square_Height) == 50){ 
            coordY_B2 += 10;
        
        }

            
        
    
    }
    Serial.println(coordY_B2);*/


    
/*
    // Verifica colisão com a barra do joystick
    if (x + circleRadius >= 15 && x - circleRadius <= 15 + square_Width &&
        y >= coordY_B1 && y <= coordY_B1 + square_Height) {
        // Calcula a distância entre a bolinha e a borda da barra
        int distance = abs(x - 15);
        
        // Se a distância for menor ou igual ao raio da bolinha, move a bolinha para fora da barra
        if (distance <= circleRadius) {
            x = 15 - circleRadius - 1; // Move a bolinha para fora da barra
            vx = -vx; // Inverte a velocidade horizontal da bolinha
            Serial.println("Colisão com a barra do joystick");
        }
    }

    // Verifica colisão com a barra dos botões
    if (x + circleRadius >= 80 && x - circleRadius <= 80 + square_Width &&
        y >= coordY_B2 && y <= coordY_B2 + square_Height) {
        // Calcula a distância entre a bolinha e a borda da barra
        int distance = abs(x - 80);
        
        // Se a distância for menor ou igual ao raio da bolinha, move a bolinha para fora da barra
        if (distance <= circleRadius) {
            y = 80 - square_Width + circleRadius - 1; // Move a bolinha para fora da barra
            vy = -vy; // Inverte a velocidade horizontal da bolinha
            Serial.println("Colisão com a barra dos botões");
        }
    }
*/