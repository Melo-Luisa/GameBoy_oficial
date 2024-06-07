#pragma once
#include <Arduino.h>
#include <TFT_eSPI.h>
#include <SPI.h>
#include "games/Pong/main.cpp"
#include "config.h"
#include "joystick.h"



class Menu{
    private:
        bool geral ;//inicia no menu inicial
        bool games ; //menu games
        bool settings ; //menu settings
        bool credits ; //menu credits
        bool inGameMenu;

        bool gamePongOn = true;
        
        //começa em 1 pra já ter algo pré selecionado
        int geral_index ;
        int games_index;
        int settings_index;
        Joystick joyzinho;
        Juiz juiz;

        unsigned long lastDebounceTime = 0;
        const unsigned long debounceDelay = 150;

    public:
        Menu(bool geral, bool games, bool settings, bool credits, int geral_index, int games_index, int setting_index)
        : geral(geral), games(games), settings(settings), credits(credits), geral_index(geral_index), settings_index(setting_index), joyzinho(joystick::eixo_x, joystick::eixo_y, joystick::botao_joy), juiz(x, y, vx, vy, circleRadius, coordY){}

        //FUNCIONA
        void init(TFT_eSPI &d);/*função já existente pra desenhar a inicialização*/

        void drawMenuGames(TFT_eSprite &game, int &games_index);//desenha/mostra as imagens com ícone de cada jogo, no subMenu Jogo

        void select(int games_index, TFT_eSprite &abertura);
        void trackPosition(bool &games, int &games_index);

    

        //PÓS 11/06
        void drawSettings();
        void drawCredits();//Mostra informações dos criadores, além da foto dos dois   
        void drawMenuInicial(TFT_eSPI &d, TFT_eSprite &text, int geral_index);//desenha o menu inicial, com as opções de games, créditos e settings

    
};

void Menu::init(TFT_eSPI &d) {
  d.setCursor(100, 120, 2);
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
    int valuejoyzinhoX = joyzinho.read_raw_X();
    Direction directionX = joyzinho.getDirectionX(valuejoyzinhoX);

    unsigned long currentTime = millis();

    if (currentTime - lastDebounceTime > debounceDelay) {
        lastDebounceTime = currentTime;

        
        if(games){
            if (directionX == RIGHT) {
                games_index++;
                if (games_index > 2) {
                    games_index = 0;
                }
            }

            if (directionX == LEFT) {
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

    game.setCursor(180, 40); // Define a posição do cursor para o segundo item

    if (games_index == 1) {
        game.setTextColor(TFT_WHITE, TFT_BLACK);
        game.println(" DINO ");
        game.setTextColor(TFT_BLACK);
        // Serial.println("dino");
    } else {
        game.println(" DINO ");
    }

    game.setCursor(300, 40); // Define a posição do cursor para o terceiro item

    if (games_index == 2) {
        game.setTextColor(TFT_WHITE, TFT_BLACK);
        game.println(" TETRIS ");
        game.setTextColor(TFT_BLACK);
        /// Serial.println("tetris");
    } else {
        game.println(" TETRIS ");
    }

    game.pushSprite(0, 110);
        
    
}

void Menu::select(int games_index, TFT_eSprite &abertura){
    if(joyzinho.read_button_central() == LOW){

        if(games){
            switch(games_index){
                case 0:
                    Serial.println("Pong");
                    //open file games/Pong/main 
                    juiz.init(abertura, gamePongOn);
                    break;
            
                case 1:
                    Serial.println("Dino");
                    break;
                case 2:
            
                    Serial.println("Tetris");
                    break;
            }
        }
    }

}











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
    

    
        



