#pragma once
#include <Arduino.h>

class Menu{
    private:

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
            /*
            CASE SWITCH RELATIVAMENTE GRANDE -> 1 dentro do outro
            ter 2 níveis de variáveis. 

            -MENU (menu será o nome de uma variável) - 1º case SWITCH
                -GAMES = 0
                -SETTINGS = 1
                -CREDITS = 2 (credits não terá subMenu)
            
            -SUB_GAMES (será variável)
                -PONG = 0
            -SUB_SETTINGS (Será variável)
                -BMS = 0
                -DIFICULDADE = 1
                -TESTES = 2

            */
        
    /*

            ------
            switch(MENU){
                case 0: //games
                    switch(SUB_GAMES)
                        case 0:
                            pong
                        case 1:
                            pewpew
                case 1: //settings
                    switch(SUB_SETTINGS)
                        case 0:
                            bms
                        case 1:
                            dificuldade
                case 2:
                    credits
            }
                

            
            */
        }

        void showPosition(){
            //A depender do valor retornado pela TRACK POSITION, usará a estrutura abaixo pra mostrar
            //na tela a opção / ir para o menu selecionado



        }
};