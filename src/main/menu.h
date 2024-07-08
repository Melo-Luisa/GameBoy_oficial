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
        : geral(geral), games(games), settings(settings), credits(credits), geral_index(geral_index), settings_index(setting_index), games_index(games_index), joyzinho(joystick::eixo_x, joystick::eixo_y, joystick::botao_joy), juiz( x,  y,  vx,  vy,  circleRadius, coordY, coordY_button), juizcapi(capix, capivx, numObstaculos), juizquiz(perguntas, total){}
        //FUNCIONA
        void init(TFT_eSPI &d);/*função já existente pra desenhar a inicialização*/

        void drawMenuGames(TFT_eSprite *(&game), int &games_index);//desenha/mostra as imagens com ícone de cada jogo, no subMenu Jogo
        void drawMenuGames_aux(TFT_eSprite *(&two), int &games_index);

        void select(int games_index, bool &gamePongOn, bool var, bool &gameCapiOn, bool capi, TFT_eSprite &game, bool &gameQuizOn);
        void trackPosition(bool &games, int &games_index);

        void backgroundPong(TFT_eSPI &d, TFT_eSprite &abertura);
        void backgroundEndPong(TFT_eSPI &d, bool &gamePongOn);
        void backgroundCapi(TFT_eSPI &d);
        void backgroundEndCapi(TFT_eSPI &d);


        //PÓS 11/06
        void drawSettings();
        void drawCredits();//Mostra informações dos criadores, além da foto dos dois   
        void drawMenuInicial(TFT_eSPI &d, TFT_eSprite &text, int geral_index);//desenha o menu inicial, com as opções de games, créditos e settings

    
};

void Menu::backgroundPong(TFT_eSPI &d, TFT_eSprite &abertura){
    d.fillScreen(TFT_BLACK);
    d.setTextColor(TFT_WHITE);
    d.setTextSize(2);
    // Define a cor e o tamanho do texto
    d.setTextDatum(TC_DATUM);
    d.setTextColor(d.color565(255, 150, 0));
    d.setCursor(200, 20);
    String name = "PONG";
    for (int i = 0; i < name.length(); i++) {
        d.print(name[i]);
        delay(100);
    }

    d.setCursor(15,72);
    d.setTextColor(TFT_WHITE);
    d.setTextSize(2);
    d.println("Utilize o joystick para controlar a \nbarra da esquerda.");

    d.setCursor(8,155);
    d.setTextSize(2);
    d.println(" E os Botões para controlar a barra \nda direita.");
    d.setTextColor(TFT_YELLOW);
    d.drawCentreString("PARA SAIR: BOTAO AMARELO.", 250, 282,2);
    // d.drawCentreString("- Quem chegar em 10 Pontos primeiro ganha!", 245,210,2);

    d.setCursor(35, 230);
    d.setTextColor(d.color565(255, 150, 0));
    d.setTextSize(2);
    d.println("Pressione o Joystick para jogar");

    while (joyzinho.read_button_central() == HIGH) {
        delay(100);
    }

    //delay(6500);
    d.fillScreen(TFT_BLACK);
    
}
void Menu::backgroundEndPong(TFT_eSPI &d, bool &gamePongOn){
    d.fillScreen(TFT_BLACK);
    d.drawCentreString("Fim de Jogo" ,245, 100,4);
    d.drawCentreString("Logo logo você irá para o menu!" ,245, 130,2);
    d.setTextSize(2);
    d.setTextColor(TFT_ORANGE);
    d.drawString("GameBoy", 30, 80, 2);
    d.drawString((String(juiz.getCountBlack())), 80, 150);
    d.setTextColor(TFT_WHITE);
    d.drawString("x", 230, 80, 2);
    d.setTextColor(TFT_RED);
    d.drawString("Player", 320, 80, 2);
    d.drawString(String(juiz.getCountWhite()), 360, 150);
    d.setTextColor(TFT_WHITE);
    d.setTextSize(2);
   
    gamePongOn = false;
    menuOn = true;
    delay(2000);
    d.fillScreen(TFT_WHITE);

}

void Menu::backgroundCapi(TFT_eSPI &d){
    d.fillScreen(TFT_BLACK);
    d.setTextColor(TFT_WHITE);
    d.setTextSize(2);
    d.setTextDatum(TC_DATUM);
    d.setTextColor(d.color565(25, 150, 0)); //laranja
    d.setCursor(170,20);
    String name = "CAPI RUNNER";
    for(int i = 0; i< name.length();i++){
        d.print(name[i]);
        delay(100);
    }

    d.setCursor(15,72);
    d.setTextColor(TFT_WHITE);
    d.setTextSize(2);
    d.println("Utilize o botão VERDE para pular para CIMA.");

    d.setCursor(8,155);
    d.setTextSize(2);
    d.println("Evite colidir com o tronco");

    d.setTextColor(TFT_YELLOW);
    d.drawCentreString("PARA SAIR: BOTAO AMARELO.", 250, 282,2);

    d.setCursor(35, 230);
    d.setTextColor(d.color565(255, 150, 0));
    d.setTextSize(2);
    d.println("Pressione o Joystick para jogar");

    while (joyzinho.read_button_central() == HIGH) {
        delay(100);
    }

    d.fillScreen(TFT_BLACK);
}

void Menu::backgroundEndCapi(TFT_eSPI &d){
    d.fillScreen(TFT_BLACK);
    d.drawCentreString("Você bateu!" ,245, 50,4);
    d.setTextSize(2);
    d.setTextColor(TFT_ORANGE);
    d.drawString("Pontuacao:", 245, 150, 2);
    d.drawString(String(juizcapi.getHighScore()), 245, 180);

    d.setTextColor(TFT_WHITE);
   
    gameCapiOn = false;
    menuOn = true;
    delay(3500);
    d.fillScreen(TFT_WHITE);
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

void Menu::drawMenuGames(TFT_eSprite *(&two_aux), int &games_index) {
    (*two_aux).setTextFont(2);
    (*two_aux).fillSprite(TFT_WHITE);
    (*two_aux).setTextSize(2);
    (*two_aux).setCursor(180, 0); 
    (*two_aux).setTextColor(TFT_BLACK);
    (*two_aux).println("GAMES");

    (*two_aux).setTextSize(2);

    (*two_aux).setCursor(40, 40); // Define a posição inicial do cursor para o primeiro item


    if (games_index == 0) {
        (*two_aux).setTextColor(TFT_WHITE, TFT_BLACK);
        (*two_aux).println(" PONG ");
        (*two_aux).setTextColor(TFT_BLACK);
        // Serial.println("pong");
    } else {
        (*two_aux).println(" PONG ");
    }

    (*two_aux).setCursor(150, 40); // Define a posição do cursor para o segundo item

    if (games_index == 1) {

        (*two_aux).setTextColor(TFT_WHITE, TFT_BLACK);
        (*two_aux).println(" CAPI RUNNER ");
        (*two_aux).setTextColor(TFT_BLACK);
        // Serial.println("dino");
    } else {
        (*two_aux).println(" CAPI RUNNER ");
    }

    (*two_aux).setCursor(350, 40); // Define a posição do cursor para o terceiro item

    if (games_index == 2) {
        (*two_aux).setTextColor(TFT_WHITE, TFT_BLACK);
        (*two_aux).println(" QUIZBOY ");
        (*two_aux).setTextColor(TFT_BLACK);
        /// Serial.println("tetris");
    } else {
        (*two_aux).println(" QUIZBOY ");
    }
    //Serial.println(games_index);
    (*two_aux).pushSprite(0, 110);
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
                    game.deleteSprite();
                    break;

                case 1:
            
                    gameCapiOn = true;
                    gamePongOn = false;
                    gameQuizOn = false;
                    capi = true;


                    game.deleteSprite();

                
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


#endif


/*void Menu::drawMenuInicial(TFT_eSPI &d, TFT_eSprite &text, int geral_index) {
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
    
}*/











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
    

    
        
