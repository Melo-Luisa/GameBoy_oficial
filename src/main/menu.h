#pragma once
#include <Arduino.h>

class Menu{
    private:
        bool geral = false; //inicia no menu inicial
        bool games = false; //menu games
        bool settings = false //menu settings
        bool credits = false; //menu credits
        
        //começa em 1 pra já ter algo pré selecionado
        int geral_index = 1;
        int games_index = 1;
        int settings_index = 1;

    public:
        void init(){
            //função já existente pra desenhar a inicialização
        }

        void drawMenuInicial(){
            //desenha o menu inicial, com as opções de games, créditos e settings
        }

        void drawMenuGames(){
            //desenha/mostra as imagens com ícone de cada jogo, no subMenu Jogo
        }

        void drawSettings(){
            //desenha o menu de configurações
            //BMS
            //Dificuldade dos Jogos
            //Teste de Hardware
        }
        void drawCredits(){
            //Mostra informações dos criadores, além da foto dos dois
        }

        void trackPosition(){
            //irá saber em qual parte dos menus e sub menus o jogador está.
            //fazer com um ENUM
            //não sei se será void
            //usar as funções da classe JOY
            //ESSA FUNÇÃO SÓ VAI ATUALIZAR OS VALORES DAS VARIÁVEIS A DEPENDER DA MOVIMENTAÇÃO DO JOY
            //VAI RETORNAR UM ENUM CHAMADO POSITION?

            //FAZER UM IF BASEADO NAS POSICOES DO JOY PRA SABER EM QUAL MENU ESTÁ, E ATUALIZAR AS VARIAVEIS?

            
        //------------- INDEX MENUS -------------------
            //LOGICA MENU PRINCIPAL
            if(geral == true){
                if(joy.direction == RIGHT){
                    geral_index++;
                    if(geral_index > 2){
                        geral_index = 0;
                    }
                }
                if(joy.direction == LEFT){
                    geral_index--;
                    if(geral_index > 2){
                        geral_index = 0;
                    }
                }
            }

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
        
    /*


                

            
            */
        }

        void showPosition(){
            //A depender do valor retornado pela TRACK POSITION, usará a estrutura abaixo pra mostrar
            //na tela a opção / ir para o menu selecionado



        }
};
