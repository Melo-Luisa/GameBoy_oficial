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
        int geral_index;
        int games_index;
        int settings_index;
        Joystick joy;

        unsigned long lastDebounceTime = 0;
        const unsigned long debounceDelay = 100;

    public:
        Menu(bool geral, bool games, bool settings, bool credits, int geral_index, int games_index, int setting_index)
        : geral(geral), games(games), settings(settings), credits(credits), geral_index(geral_index), settings_index(setting_index), joy(32,33){}

        void init(TFT_eSPI &d);/*função já existente pra desenhar a inicialização*/

        void drawMenuInicial(TFT_eSPI &d, TFT_eSprite &text);/*desenha o menu inicial, com as opções de games, créditos e settings*/
            

        void drawMenuGames();//desenha/mostra as imagens com ícone de cada jogo, no subMenu Jogo
            

        void drawSettings();
            /*desenha o menu de configurações
            BMS
            Dificuldade dos Jogos
            Teste de Hardware*/
            
        
        void drawCredits();//Mostra informações dos criadores, além da foto dos dois
            

        void trackPosition(bool &geral, int &geral_index);

        void showPosition();
            //A depender do valor retornado pela TRACK POSITION, usará a estrutura abaixo pra mostrar
            //na tela a opção / ir para o menu selecionado
        

    
};

void Menu::init(TFT_eSPI &d) {
  d.setCursor(100, 120, 2);
  d.setTextColor(TFT_WHITE);
  d.setTextSize(5);
  

  String word = "GAMEBOY";

  for (int i = 0; i < word.length(); i++) {
    d.print(word[i]);
    delay(100);
  }

  delay(1000);
  d.fillScreen(TFT_ORANGE);

}

void Menu::drawMenuInicial(TFT_eSPI &d, TFT_eSprite &text){
    text.fillSprite(TFT_WHITE);
    text.setTextColor(TFT_BLACK);
    text.setCursor(50, 40, 2);
    text.print("Jogos");
    text.setCursor(180, 40, 2);
    text.print("Config");
    text.setCursor(300, 40, 2);
    text.print("Creditos");
    text.setTextSize(2);


    text.pushSprite(0,110);
}



void Menu::trackPosition(bool &geral, int &geral_index){
    int valueJoyX = analogRead(joystick::eixo_x);
    Direction directionX = joy.getDirectionX(valueJoyX);
    //Serial.println(directionX); //3 = LEFT e 4 = RIGHT
    
    unsigned long currentTime = millis();

    if(currentTime - lastDebounceTime > debounceDelay){
        lastDebounceTime = currentTime;
    //------------- INDEX MENUS -------------------
        //LOGICA MENU PRINCIPAL
        if(geral == true){
        Serial.print("Current geral_index: ");
        Serial.println(geral_index);
            if(directionX == RIGHT){
                geral_index++;
                if(geral_index > 2){
                    geral_index = 0;
                }
            Serial.print("Updated geral_index (RIGHT): ");
            Serial.println(geral_index);
            }
        

            if(directionX == LEFT){
                geral_index--;
                if(geral_index < 0){
                    geral_index = 2;
                }
            Serial.print("Updated geral_index (LEFT): ");
            Serial.println(geral_index);
            }
        
        }

        }
        
}
    

/*
 //LOGICA MENU GAMES
    if(games == true){
        if(joy.direction == RIGHT){
            games_index++;
            if(games_index > 2){
                games_index = 0;
            }
        }
        if(joy.direction == LEFT){
            games_index--;
            if(games_index > 2){
                games_index = 0;
            }
        }
    }

    //LOGICA MENU SETTINGS
    if(settings == true){
        if(joy.direction == RIGHT){
            settings_index++;
            if(settings_index > 2){
                settings_index = 0;
            }
        }
        if(joy.direction == LEFT){
            settings_index--;
            if(settings_index > 2){
                settings_index = 0;
            }
        }
    }
            
            //----------------- IDENTIFICAÇÃO MENUS  -----------------------------

    if(botaoJOY == pressionado){
        if(geral){
            switch(geral_index){
                case 1:
                    games = true;
                    settings = false;
                    geral = false;
                    credits = false;
                case 2:
                    settings = true;
                    games = false;
                    geral = false;
                    credits = false;
                case 3:
                    credits = true;
                    games = false;
                    geral = false;
                    settings = false;
            }
        }

    if(games){
        switch(games_index){
        case 1:
            pong = true;
            pewpew = false;
            games = false;
        case 2:
            pewpew = true;
            pong = false;
            games = false;
        }
    }

    if(settings){
        switch(settings_index){
            case 1:
                bms = true;
                testes = false;
                settings = false;
            case 2:
                testes = true;
                bms = false;
                settings = false;
            }
        }
    }
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
    

    
        



