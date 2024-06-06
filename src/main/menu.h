#pragma once
#include <Arduino.h>
#include <TFT_eSPI.h>
#include <SPI.h>

#include "config.h"
#include "joystick.h"

class Menu{
    private:
        bool geral ;//inicia no menu inicial
        bool games ; //menu games
        bool settings ; //menu settings
        bool credits ; //menu credits
        
        //começa em 1 pra já ter algo pré selecionado
        int geral_index ;
        int games_index;
        int settings_index;
        Joystick joy;

        unsigned long lastDebounceTime = 0;
        const unsigned long debounceDelay = 150;

    public:
        Menu(bool geral, bool games, bool settings, bool credits, int geral_index, int games_index, int setting_index)
        : geral(geral), games(games), settings(settings), credits(credits), geral_index(geral_index), settings_index(setting_index), joy(32,33,25){}

        //FUNCIONA
        void init(TFT_eSPI &d);/*função já existente pra desenhar a inicialização*/

        //FUNCIONA
        void drawMenuInicial(TFT_eSPI &d, TFT_eSprite &text, int geral_index);/*desenha o menu inicial, com as opções de games, créditos e settings*/
            

        void drawMenuGames(TFT_eSprite &game, int geral_index);//desenha/mostra as imagens com ícone de cada jogo, no subMenu Jogo
            

        void drawSettings();
            /*desenha o menu de configurações
            BMS
            Dificuldade dos Jogos
            Teste de Hardware*/
            
        
        void drawCredits();//Mostra informações dos criadores, além da foto dos dois
            
        //FUNCIONA
        void trackPosition(bool &geral, int &geral_index);
        void select(int geral_index, TFT_eSprite &text);

        void showPosition();
            //A depender do valor retornado pela TRACK POSITION, usará a estrutura abaixo pra mostrar
            //na tela a opção / ir para o menu selecionado
        

    
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



void Menu::trackPosition(bool &geral, int &geral_index) {
    int valueJoyX = joy.read_raw_X();
    Direction directionX = joy.getDirectionX(valueJoyX);
    
    unsigned long currentTime = millis();

    if (currentTime - lastDebounceTime > debounceDelay) {
        lastDebounceTime = currentTime;
        
        if (geral) {
            if (directionX == RIGHT) {
                geral_index++;
                if (geral_index > 2) {
                    geral_index = 0;
                }
                
                
            }

            if (directionX == LEFT) {
                geral_index--;
                if (geral_index < 0) {
                    geral_index = 2;
                }
            }

            
        }

        // Similar logic for games and settings menus
    }
    //Serial.println(geral_index);
}



void Menu::select(int geral_index, TFT_eSprite &text){
    if(joy.read_button_central() == LOW){
        if(geral){
            switch(geral_index){
                case 0:
                    Serial.println("Games");
                    drawMenuGames(text, geral_index);
                    delay(1000);
                    break;
                    // games = true;
                    // settings = false;
                    // geral = false;
                    // credits = false;
                case 1:
                    // settings = true;
                    // games = false;
                    // geral = false;
                    // credits = false;
                    Serial.println("Settings");
                    break;
                case 2:
                    // credits = true;
                    // games = false;
                    // geral = false;
                    // settings = false;
                    Serial.println("Credits");
                    break;
            }
        }

        // if(games){
        //     switch(games_index){
        //     case 1:
        //         pong = true;
        //         pewpew = false;
        //         games = false;
        //     case 2:
        //         pewpew = true;
        //         pong = false;
        //         games = false;
        //     }
        // }

        // if(settings){
        //     switch(settings_index){
        //         case 1:
        //             bms = true;
        //             testes = false;
        //             settings = false;
        //         case 2:
        //             testes = true;
        //             bms = false;
        //             settings = false;
        //         }
        //     }
        // }
    }

}

void Menu::drawMenuGames(TFT_eSprite &game, int geral_index) {
    game.fillSprite(TFT_WHITE);
    game.setTextSize(2);

    // Adiciona o título
    game.setCursor(40, 10); // Define a posição do cursor para o título
    game.setTextColor(TFT_BLACK);
    game.println("GAMES");

    // Desenha os itens do menu abaixo do título
    game.setCursor(40, 40); // Define a posição inicial do cursor para o primeiro item

    if (geral_index == 0) {
        game.setTextColor(TFT_WHITE, TFT_BLACK);
        game.println(" PONG ");
        game.setTextColor(TFT_BLACK);
    } else {
        game.println(" PONG ");
    }

    game.setCursor(180, 40); // Define a posição do cursor para o segundo item

    if (geral_index == 1) {
        game.setTextColor(TFT_WHITE, TFT_BLACK);
        game.println(" DINO ");
        game.setTextColor(TFT_BLACK);
    } else {
        game.println(" DINO ");
    }

    game.setCursor(300, 40); // Define a posição do cursor para o terceiro item

    if (geral_index == 2) {
       game.setTextColor(TFT_WHITE, TFT_BLACK);
        game.println(" TETRIS ");
        game.setTextColor(TFT_BLACK);
    } else {
        game.println(" TETRIS ");
    } 

    game.pushSprite(0, 110);
}








/*           
    //----------------- IDENTIFICAÇÃO MENUS  -----------------------------

    
    //irá saber em qual parte dos menus e sub menus o jogador está.
    //fazer com um ENUM
    //não sei se será void
    //usar as funções da classe JOY
    //ESSA FUNÇÃO SÓ VAI ATUALIZAR OS VALORES DAS VARIÁVEIS A DEPENDER DA MOVIMENTAÇÃO DO JOY
    //VAI RETORNAR UM ENUM CHAMADO POSITION?

    //FAZER UM IF BASEADO NAS POSICOES DO JOY PRA SABER EM QUAL MENU ESTÁ, E ATUALIZAR AS VARIAVEIS?

            
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
    

    
        



