//banco de perguntas
#pragma once

#include "config.h"

struct Pergunta {
    const char* enunciado;
    const char* alternativas[3]; //3 alternativas por pergunta
    int respostaCorreta; //0, 1 ou 2 -> indice das alternativas
};

// Vetor de perguntas
Pergunta perguntas[] = {
    {
        "Qual é o nome do protagonista da série de jogos 'The Legend of Zelda'?",
        {"Zelda", "Link", "Ganondorf"},
        1
    },
    {
        "Em que ano foi lançado o jogo 'Super Mario Bros.' para o NES?",
        {"1983", "1985", "1987"},
        1
    },
    {
        "Qual jogo popularmente conhecido como 'GTA V' foi lançado em qual ano?",
        {"2010", "2013", "2015"},
        1
    },
    {
        "Qual é o nome do vilão principal na série 'Sonic the Hedgehog'?",
        {"Bowser", "Dr. Eggman", "King K. Rool"},
        1
    },
    {
        "Qual destes jogos foi desenvolvido pela CD Projekt Red?",
        {"The Witcher 3: Wild Hunt", "The Elder Scrolls V: Skyrim", "Fallout 4"},
        0
    },
    {
        "Em que console foi lançado o jogo 'Halo: Combat Evolved' originalmente?",
        {"PlayStation 2", "Xbox", "GameCube"},
        1
    },
    {
        "Qual jogo popular da Nintendo apresenta personagens lutando em arenas, incluindo Mario, Link e Pikachu?",
        {"Mario Kart", "Super Smash Bros.", "Animal Crossing"},
        1
    },
    {
        "Qual destes jogos foi lançado primeiro?",
        {"Minecraft", "Fortnite", "Among Us"},
        0
    },
    {
        "Qual é o nome do planeta natal dos Protoss no jogo 'StarCraft'?",
        {"Korhal", "Shakuras", "Aiur"},
        2
    },
    {
        "Qual desses jogos é um exemplo clássico de um RPG japonês (JRPG)?",
        {"Final Fantasy VII", "Call of Duty: Modern Warfare", "Resident Evil 2"},
        0
    }
};
