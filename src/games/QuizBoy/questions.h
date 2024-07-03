//banco de perguntas
#pragma once

#include "config.h"
#include <TFT_eSPI.h> 
// Define o tipo para o ponteiro de função
typedef void (*QuestionFunction)(TFT_eSPI&);

const int y1Linha = 10;
const int y2Linha = 50;
const int y3Linha = 90;
const int y4Linha = 130;

struct Pergunta {
    const char* alternativas[3]; // 3 alternativas por pergunta
    int respostaCorreta; // 0, 1 ou 2 -> indice das alternativas
    QuestionFunction func; // Ponteiro de função
};

void question1(TFT_eSPI &d) {
    Serial.println("Qual o nome do protagonista da série de jogos The Legend of Zelda?");
    d.setTextSize(3);
    d.drawString("Qual o nome do", 100, y1Linha);
    d.drawString("protagonista da serie de", 30, y2Linha);
    d.drawString("jogos The Legend of Zelda?", 10, y3Linha);
    delay(10);
}

void question2(TFT_eSPI &d) {
    Serial.println("Em que ano foi lançado o jogo 'Super Mario Bros.' para o NES?");
    d.setTextSize(3);
    d.drawString("Em quem ano foi lancado o", 20, y1Linha);
    d.drawString("jogo 'Super Mario Bros.'", 25, y2Linha);
    d.drawString("para o NES?", 130, y3Linha);
    delay(10);
}

void question3(TFT_eSPI &d) {
    Serial.println("Qual jogo popularmente conhecido como 'GTA V' foi lancado em qual ano?");
    d.setTextSize(3);
    d.drawString("O jogo popularmente", 50, y1Linha);
    d.drawString("conhecido como 'GTA V'", 40, y2Linha);
    d.drawString("foi lancado em qual ano?", 30, y3Linha);
    delay(10);
}

void question4(TFT_eSPI &d) {
    Serial.println("No Jogo Minecraft, qual o nome do Chefe Final que os Jogadores Podem Derrotar?");
    d.setTextSize(3);
    d.drawString("No Jogo Minecraft, qual o", 20, 10);
    d.drawString("Nome do Chefe Final que os", 20, y2Linha);
    d.drawString("Jogadores Podem Derrotar?", 20, y3Linha);
    delay(10);

}

void question5(TFT_eSPI &d) {
    Serial.println("Qual foi o primeiro Jogo Lancado para o GameBoy?");
    d.setTextSize(3);
    d.drawString("Qual foi o primeiro Jogo", 25, y1Linha);
    d.drawString("Lancado para o GameBoy?", 30, y2Linha);
    delay(10);

}

void question6(TFT_eSPI &d) {
    Serial.println("Qual é o nome do protagonista de 'The Witcher 3: Wild Hunt'?");
    d.setTextSize(3);
    d.drawString("Qual o nome do", 100, y1Linha);
    d.drawString("protagonista de ", 100, y2Linha);
    d.drawString("The Witcher 3: Wild Hunt?", 20, y3Linha);
    delay(10);
}

void question7(TFT_eSPI &d) {
    Serial.println("Em 'Among Us', qual é o objetivo principal dos impostores?");
    d.setTextSize(3);
    d.drawString("Em 'Among Us', qual o", 55, y1Linha);
    d.drawString("objetivo principal", 80, y2Linha);
    d.drawString("dos impostores?", 90, y3Linha);
    delay(10);
}

void question8(TFT_eSPI &d) {
    Serial.println("Em League of Legends qual é a função principal do personagem 'Thresh?'");
    d.setTextSize(3);
    d.drawString("Em League of Legends qual", 20, y1Linha);
    d.drawString("a funcao principal do", 50, y2Linha);
    d.drawString("personagem 'Thresh'?", 60, y3Linha);
    delay(10);
}

void question9(TFT_eSPI &d) {
    Serial.println("Qual é o nome do personagem que usa um chapéu e solta raios em 'Mortal Kombat'?");
    d.setTextSize(3);
    d.drawString("Qual o nome do personagem", 10, y1Linha);
    d.drawString("que usa um chapeu e solta", 10, y2Linha);
    d.drawString("raios em 'Mortal Kombat'?", 10, y3Linha);
    delay(10);
}



void question10(TFT_eSPI &d) {
    Serial.println("Em 'Street Fighter', qual é o nome do lutador que possui uma famosa habilidade chamada 'Hadouken'?");
    d.setTextSize(3);
    d.drawString("Em 'Street Fighter', qual", 20, y1Linha);
    d.drawString("o nome do lutador que tem", 15, y2Linha);
    d.drawString("uma famosa habilidade", 50, y3Linha);
    d.drawString("chamada 'Hadouken'?", 70, y4Linha);
    delay(10);
}

void question11(TFT_eSPI &d) {
    Serial.println("Qual é o nome do famoso encanador da Nintendo?"); //COLOCAR ALGO NA RESPOSTA
    //"AQUELE QUE.."
    d.setTextSize(3);
    d.drawString("Qual o nome do famoso", 50, y1Linha);
    d.drawString("encanador da Nintendo?", 50, y2Linha);
    delay(10);
}

void question12(TFT_eSPI &d) {
    Serial.println("Qual personagem de LoL tem a habilidade 'Ataque Tóxico'?");
    d.drawString("Qual personagem de LoL", 50, y1Linha);
    d.drawString("tem a habilidade", 90, y2Linha);
    d.drawString("'Ataque Toxico'?", 100, y3Linha);
    delay(10);
}


// Vetor de perguntas
Pergunta perguntas[] = {
    {
        {"Zelda", "Link", "Ganondorf"},
        1,
        question1
    },
    {
        {"1983", "1985", "1987"},
        1,
        question2
    },
    {
        {"2010", "2013", "2015"},
        1,
        question3
    },
    {
        {"Ender Dragon", "Whither", "Herobrine"},
        0,
        question4
    },
    {
        {"Pokemon Red/Blue", "Pong", "Tetris"}, //colocar algo se responder o pong
        2,
        question5
    },
    {
        {"Geralt of Rivia", "Ezio Auditore", "Nathan Drake"},
        0,
        question6
    },
    {
        {"Completar as Tarefas", "Eliminar todos os tripulantes", "Sabotar a Nave"},
        1,
        question7
    },
    {
        {"Atirador", "Suporte", "Mid Laner"},
        1,
        question8
    },
    {
        {"Scorpion", "Sub-Zero", "Raiden"},
        2,
        question9
    },
    {
        {"Ken", "Barbie", "Ryu"},
        2,
        question10
    },
    {
        {"Mario", "Luigi", "Toad"},
        0,
        question11
    },
    {
        {"Singed", "Teemo", "Cassiopeia"},
        1,
        question12
    }

};


//Vetor de Respostas Corretas
String corretas[5] = {
    "Olha só quem acertou! Muito bem", 
    "É mais esperto do que eu imaginava hein?",
    "Sr. Sabe Tudo é? Vamos ver na Próxima.."
};