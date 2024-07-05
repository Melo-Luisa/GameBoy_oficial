#ifndef MENU_H
#define MENU_H

#pragma once
#include <Arduino.h>
#include <TFT_eSPI.h>
#include <SPI.h>
#include "games/Pong/juiz.h"
#include "games/CapiRunner/logic.h"
#include "games/QuizBoy/juizQuiz.h"
#include "games/QuizBoy/questions.h"
#include "config.h"
#include "joystick.h"



class Menu{
    private:
        bool geral ;//inicia no menu inicial
        bool games ; //menu games
        bool settings ; //menu settings
        bool credits ; //menu credits
        bool inGameMenu;

        bool gamePongOn;
        bool gameCapiOn;
        bool gameQuizOn;
        bool menuOn; // só para acessar o menu novamente
        
        //começa em 1 pra já ter algo pré selecionado
        int geral_index ;
        int games_index;
        int settings_index;
        bool var, capi;
        int x, y,vx,vy,circleRadius, coordY, coordY_button;
        int capix, capivx, numObstaculos;
        int total;
        Joystick joyzinho;
        Juiz juiz;
        JuizCapi juizcapi;
        JuizQuiz juizquiz;
        Pergunta perguntas[2];


    
        unsigned long lastDebounceTime = 0;
        const unsigned long debounceDelay = 150;

    public:
        Menu(bool geral, bool games, bool settings, bool credits, int geral_index, int games_index, int setting_index)
        : geral(geral), games(games), settings(settings), credits(credits), geral_index(geral_index), settings_index(setting_index), joyzinho(joystick::eixo_x, joystick::eixo_y, joystick::botao_joy), juiz( x,  y,  vx,  vy,  circleRadius, coordY, coordY_button), juizcapi(capix, capivx, numObstaculos), juizquiz(perguntas, total){}
        //FUNCIONA
        void init(TFT_eSPI &d);/*função já existente pra desenhar a inicialização*/

        void drawMenuGames(TFT_eSprite &game, int &games_index);//desenha/mostra as imagens com ícone de cada jogo, no subMenu Jogo

        void select(int games_index, bool &gamePongOn, bool var, bool &gameCapiOn, bool capi, TFT_eSprite &game, bool &gameQuizOn);
        void trackPosition(bool &games, int &games_index);

        void backgroundPong(TFT_eSPI &d, TFT_eSprite &abertura);
        void backgroundEndPong(TFT_eSPI &d, bool &gamePongOn);
        void backgroundCapi(TFT_eSPI &d);

        //PÓS 11/06
        void drawSettings();
        void drawCredits();//Mostra informações dos criadores, além da foto dos dois   
        void drawMenuInicial(TFT_eSPI &d, TFT_eSprite &text, int geral_index);//desenha o menu inicial, com as opções de games, créditos e settings
        // void PongOn(bool &gamePongOn, TFT_eSPI &d);
        // void CapiOn(bool &gameCapiOn);

    
};

void Menu::backgroundPong(TFT_eSPI &d, TFT_eSprite &abertura){
    d.fillScreen(TFT_BLACK);
    d.setTextColor(TFT_WHITE);
    d.setTextSize(1);
    // Define a cor e o tamanho do texto
    d.setTextDatum(TC_DATUM);
    d.setCursor(200, 120, 4);
    String name = "PONG";
    for (int i = 0; i < name.length(); i++) {
        d.print(name[i]);
        delay(100);
    }

    d.drawCentreString("Utilize o joystick para CIMA e BAIXO para controlar a barra da esquerda.", 245,150,2);

    d.drawCentreString(" E os Botões CIMA e BAIXO para controlar a barra da direita.", 245, 170,2);
    d.drawCentreString("Evite que a bolinha passe para o outro lado.", 245, 190,2);
    d.drawCentreString("- Quem chegar em 10 Pontos primeiro ganha!", 245,210,2);
    delay(6500);
    //d.fillScreen(TFT_BLACK);
    
}
void Menu::backgroundEndPong(TFT_eSPI &d, bool &gamePongOn){
    d.fillScreen(TFT_BLACK);
    d.drawCentreString("Fim de Jogo" ,245, 190,4);
    d.drawCentreString("Logo logo você irá para o menu!" ,245, 210,2);
    gamePongOn = false;
    menuOn = true;
    delay(1000);
    d.fillScreen(TFT_WHITE);

}

void Menu::backgroundCapi(TFT_eSPI &d){
    d.fillScreen(TFT_BLACK);
    d.setTextColor(TFT_WHITE);
    d.setTextSize(1);
    d.setTextDatum(TC_DATUM);
    d.setCursor(150,120,4);
    String name = "CAPI RUNNER";
    for(int i = 0; i< name.length();i++){
        d.print(name[i]);
        delay(300);
    }
    d.drawCentreString("Utilize o botão VERDE para pular para CIMA.", 245,150,2);
    d.drawCentreString(" E evite colidir com o tronco.", 245, 170,2);
    d.drawCentreString(" Marque a maior pontuação!", 245, 190,2);
    d.drawCentreString("PARA SAIR: APERTE AMARELO", 240, 210,2);
    delay(6000);
   // d.fillScreen(TFT_BLACK);
}

void Menu::init(TFT_eSPI &d) {
  d.setCursor(150, 120, 2);
  d.setTextColor(TFT_WHITE);
  d.setTextSize(3);
  

  String word = "GAMEBOY";

  for (int i = 0; i < word.length(); i++) {
    d.print(word[i]);
    delay(100);
  }

  delay(100);
  d.fillScreen(TFT_WHITE);

}

void Menu::trackPosition(bool &games, int &games_index) {
    int valuejoyzinhoX = joyzinho.read_raw_Y();
    Direction directionX = joyzinho.getDirectionY(valuejoyzinhoX);

    unsigned long currentTime = millis();

    if (currentTime - lastDebounceTime > debounceDelay) {
        lastDebounceTime = currentTime;

        
        if(games){
            if (directionX == DOWN) {
                games_index++;
                if (games_index > 2) {
                    games_index = 0;
                }
            }

            if (directionX == UP) {
                games_index--;
                if (games_index < 0) {
                    games_index = 2;
                }
            }
        }

    }
}

void Menu::drawMenuGames(TFT_eSprite &game, int &games_index) {
    
    game.fillSprite(TFT_WHITE);
    game.setTextSize(2);

    // Adiciona o título
    game.setCursor(40, 10); // Define a posição do cursor para o título
    game.setTextColor(TFT_BLACK);
    game.println("GAMES");

    // Desenha os itens do menu abaixo do título
    game.setCursor(40, 40); // Define a posição inicial do cursor para o primeiro item

    if (games_index == 0) {
        game.setTextColor(TFT_WHITE, TFT_BLACK);
        game.println(" PONG ");
        game.setTextColor(TFT_BLACK);
        // Serial.println("pong");
    } else {
        game.println(" PONG ");
    }

    game.setCursor(150, 40); // Define a posição do cursor para o segundo item

    if (games_index == 1) {
        game.setTextColor(TFT_WHITE, TFT_BLACK);
        game.println(" CAPI RUNNER ");
        game.setTextColor(TFT_BLACK);
        // Serial.println("dino");
    } else {
        game.println(" CAPI RUNNER ");
    }

    game.setCursor(350, 40); // Define a posição do cursor para o terceiro item

    if (games_index == 2) {
        game.setTextColor(TFT_WHITE, TFT_BLACK);
        game.println(" QUIZBOY ");
        game.setTextColor(TFT_BLACK);
        /// Serial.println("tetris");
    } else {
        game.println(" QUIZBOY ");
    }

    game.pushSprite(0, 110);
        
    
}
void Menu::select(int games_index, bool &gamePongOn, bool var, bool &gameCapiOn, bool capi, TFT_eSprite &game, bool &gameQuizOn ){
    if(joyzinho.read_button_central() == LOW || digitalRead(button::azul) == LOW){
        if(games){
            switch(games_index){
                case 0:
                    gamePongOn = true;
                    gameCapiOn = false;
                    gameQuizOn = false;
                    var = true;
                    // game.fillScreen(TFT_BLACK);
                    break;

                case 1:
            
                    gameCapiOn = true;
                    gamePongOn = false;
                    gameQuizOn = false;
                    capi = true;


                    
                
                    break;
                case 2:
                    gameCapiOn = false;
                    gamePongOn = false;
                    gameQuizOn = true;
                    break;
            }
        }
    }

}
// void Menu::PongOn(bool &gamePongOn, TFT_eSPI &d){
  

//     while (gamePongOn) {
//         //initializePong();
//         while (gamePongOn) {
            
//         }
//     }
// }

// void Menu::CapiOn(bool &gameCapiOn){
//     juizcapi.drawCapi(capiSprite);
//     juizcapi.drawObstacles(obstaculosSprite);
//     juizcapi.colision();
//     juizcapi.score();
//     juizcapi.drawScore(scoreSprite);
//     juizcapi.level_speed();

//     if (digitalRead(button::amarelo) == LOW) {
//         gameCapiOn = false;
//         menuOn = true;
//         d.fillScreen(TFT_WHITE);
//         juizcapi.setplacar(0);
//     }
// }





void Menu::drawMenuInicial(TFT_eSPI &d, TFT_eSprite &text, int geral_index) {
    text.fillSprite(TFT_WHITE);

    if (geral_index == 0) {
        text.setTextColor(TFT_WHITE, TFT_BLACK);
        text.println(" GAMES ");
        text.setTextColor(TFT_BLACK);
    } else {
        text.println(" GAMES ");
    }
    text.setCursor(40, 40, 2);

    if (geral_index == 1) {
        text.setTextColor(TFT_WHITE, TFT_BLACK);
        text.println(" SETTINGS ");
        text.setTextColor(TFT_BLACK);
    } else {
        text.println(" SETTINGS ");
    }
    text.setCursor(180, 40, 2);

    if (geral_index == 2) {
       text.setTextColor(TFT_WHITE, TFT_BLACK);
        text.println(" CREDITS ");
        text.setTextColor(TFT_BLACK);
    } else {
        text.println(" CREDITS ");
    } 
    text.setCursor(300, 40, 2);
    //text.print("Creditos");
    text.setTextSize(2);

    text.pushSprite(0, 110);
    
}







#endif
















/*           
    //----------------- IDENTIFICAÇÃO MENUS  -----------------------------

    
    //irá saber em qual parte dos menus e sub menus o jogador está.
    //fazer com um ENUM
    //não sei se será void
    //usar as funções da classe joyzinho
    //ESSA FUNÇÃO SÓ VAI ATUALIZAR OS VALORES DAS VARIÁVEIS A DEPENDER DA MOVIMENTAÇÃO DO joyzinho
    //VAI RETORNAR UM ENUM CHAMADO POSITION?

    //FAZER UM IF BASEADO NAS POSICOES DO joyzinho PRA SABER EM QUAL MENU ESTÁ, E ATUALIZAR AS VARIAVEIS?

            
*/
   
        

 
            
/*
    CASE SWITCH RELATIVAMENTE GRANDE -> 1 dentro do outro
    ter 2 níveis de variáveis. 
    bool GERAl == true //MENU PRINCIPAL - IF GERAL && PIPIPO
        -MENU (MENU será o nome de uma variável) - 1º case SWITCH
            -GAMES = 1
            -SETTINGS = 2
            -CREDITS = 3 (credits não terá subMenu)
        
        -SUB_GAMES (será variável)
            -PONG = 0
        -SUB_SETTINGS (Será variável)
            -BMS = 0
            -DIFICULDADE = 1
            -TESTES = 2

*/
    

    
        



