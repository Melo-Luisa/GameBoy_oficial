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
    d.setTextSize(2);
    d.setCursor(130,y1Linha);
    d.println("Qual o nome do");
    d.setCursor(50,y2Linha);
    d.println("protagonista da serie de");
    d.setCursor(30,y3Linha);
    d.println("jogos The Legend of Zelda?");
    delay(10);
}

void question2(TFT_eSPI &d) {
    Serial.println("Em que ano foi lançado o jogo 'Super Mario Bros.' para o NES?");
    d.setTextSize(2);
    d.setCursor(40,y1Linha);
    d.println("Em quem ano foi lancado o");
    d.setCursor(45,y2Linha);
    d.println("jogo 'Super Mario Bros.'");
    d.setCursor(155,y3Linha);
    d.println("para o NES?");
    delay(10);
}

void question3(TFT_eSPI &d) {
    Serial.println("Qual jogo popularmente conhecido como 'GTA V' foi lancado em qual ano?");
    d.setTextSize(2);
    d.setCursor(60,y1Linha);
    d.println("O jogo popularmente");
    d.setCursor(50,y2Linha);
    d.println("conhecido como 'GTA V'");  
    d.setCursor(40,y3Linha);
    d.println("foi lancado em qual ano?");
    delay(10);
}

void question4(TFT_eSPI &d) {
    Serial.println("No Jogo Minecraft, qual o nome do Chefe Final que os Jogadores Podem Derrotar?");
    d.setTextSize(2);
    d.setCursor(30,10);
    d.println("No Jogo Minecraft, qual o");    
    d.setCursor(40,y2Linha);
    d.println("Nome do Chefe Final que os");   
    d.setCursor(40,y3Linha);
    d.println("Jogadores Podem Derrotar?");
    delay(10);

}

void question5(TFT_eSPI &d) {
    Serial.println("Qual foi o primeiro Jogo Lancado para o GameBoy?");
    d.setTextSize(2);
    d.setCursor(35,y1Linha);
    d.println("Qual foi o primeiro Jogo");  
    d.setCursor(60,y2Linha);
    d.println("Lancado para o GameBoy?");
    delay(10);

}

void question6(TFT_eSPI &d) {
    Serial.println("Qual é o nome do protagonista de 'The Witcher 3: Wild Hunt'?");
    d.setTextSize(2);
    d.setCursor(150,y1Linha);
    d.println("Qual o nome do");    
    d.setCursor(150,y2Linha);
    d.println("protagonista de ");
    d.setCursor(30,y3Linha);
    d.println("The Witcher 3: Wild Hunt?");
    delay(10);
}

void question7(TFT_eSPI &d) {
    Serial.println("Em 'Among Us', qual é o objetivo principal dos impostores?");
    d.setTextSize(2);
    d.setCursor(75,y1Linha);
    d.println("Em 'Among Us', qual o");
    d.setCursor(90,y2Linha);
    d.println("objetivo principal");
    d.setCursor(100,y3Linha);
    d.println("dos impostores?");
    delay(10);
}

void question8(TFT_eSPI &d) {
    Serial.println("Em League of Legends qual é a função principal do personagem 'Thresh?'");
    d.setTextSize(2);
    d.setCursor(30,y1Linha);
    d.println("Em League of Legends qual");
    d.setCursor(60,y2Linha);
    d.println("a funcao principal do");
    d.setCursor(70,y3Linha);
    d.println("personagem 'Thresh'?");
    delay(10);
}

void question9(TFT_eSPI &d) {
    Serial.println("Qual é o nome do personagem que usa um chapéu e solta raios em 'Mortal Kombat'?");
    d.setTextSize(2);
    d.setCursor(20,y1Linha);
    d.println("Qual o nome do personagem");
    d.setCursor(20,y2Linha);
    d.println("que usa um chapeu e solta");
    d.setCursor(20,y3Linha);
    d.println("raios em 'Mortal Kombat'?");
    delay(10);
}



void question10(TFT_eSPI &d) {
    Serial.println("Em 'Street Fighter', qual é o nome do lutador que possui uma famosa habilidade chamada 'Hadouken'?");
    d.setTextSize(2);
    d.setCursor(40,y1Linha);
    d.println("Em 'Street Fighter', qual");
    d.setCursor(20,y2Linha);
    d.println("o nome do lutador que tem");
    d.setCursor(70,y3Linha);
    d.println("uma famosa habilidade");
    d.setCursor(80,y4Linha);
    d.println("chamada 'Hadouken'?");
    delay(10);
}

void question11(TFT_eSPI &d) {
    Serial.println("Qual é o nome do famoso encanador da Nintendo?"); //COLOCAR ALGO NA RESPOSTA
    //"AQUELE QUE.."
    d.setTextSize(2);
    d.setCursor(60,y1Linha);
    d.println("Qual o nome do famoso");
    d.setCursor(60,y2Linha);
    d.println("encanador da Nintendo?");
    delay(10);
}

void question12(TFT_eSPI &d) {
    Serial.println("Qual personagem de LoL tem a habilidade 'Ataque Tóxico'?");
    d.setCursor(50,y1Linha);
    d.println("Qual personagem de LoL");
    d.setCursor(100,y2Linha);
    d.println("tem a habilidade");
    d.setCursor(120,y3Linha);
    d.println("'Ataque Toxico'?");
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