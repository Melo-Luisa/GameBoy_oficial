//o juiz faz toda a lógica de pegar as perguntas e verificar tudo e etc
#pragma once

#include "config.h"
#include "questions.h"
#include "joystick.h"

#define MAX_PERGUNTAS 10
#define MAX_ALTERNATIVAS 3
#define MAX_CHAR 100


class JuizQuiz{
    //variaveis
    private:
    Joystick joy;
    Pergunta perguntas[10];
    int pontuacao;
    int perguntaAtual;
    int totalPerguntas;

    int alternativa_index;

    bool question_ON; //se estiver uma pergunta aparecendo na tela. É usada no alternativa_index

    unsigned long lastDebounceTime = 0;
    const unsigned long debounceDelay = 200;

    int distancia_alternativas = 70;


    public:
    //funções
    JuizQuiz(Pergunta p[], int total);

    int showIntros(TFT_eSPI &d);

    void drawQuestions(TFT_eSPI &d);

    void updateAlternative(TFT_eSPI &d, int prev_index, int current_index);

    void trackPosition(TFT_eSPI &d, int &alternativa_index);

    void select(TFT_eSPI &d, int &alternativa_index);

    int score();

    bool isFinished();

};


JuizQuiz::JuizQuiz(Pergunta p[], int total):pontuacao(0), perguntaAtual(0), totalPerguntas(total), alternativa_index(0), joy(joystick::eixo_x, joystick::eixo_y, joystick::botao_joy) {
    for(int i=0; i < total; i++){
        perguntas[i] = p[i];
    }
}


int JuizQuiz::showIntros(TFT_eSPI &d){
    //mostrar algumas falas do gameboy. Como se fosee o GB falando com o jogador
    //Essas falas serão antes e depois 
    d.setTextSize(4);
    d.fillScreen(TFT_BLACK);
    d.setTextColor(TFT_WHITE);

    d.setCursor(100, 20);
    d.println("Bem-Vindo ao");

    d.setCursor(150, 100);
    d.setTextColor(d.color565(255, 150, 0));
    d.println("QuizBoy");

    d.setTextColor(TFT_WHITE);
    d.setCursor(60, 200);
    d.setTextSize(2);
    d.println("Acha Mesmo que Sabe Mais que O");
    d.setCursor(190, 230);
    d.println("GameBoy?");

    d.setCursor(30, 290);
    d.setTextSize(2);
    d.println("Pressione o Joystick para Descobrir");

    // Espera pelo botão do joystick
    while (joy.read_button_central() == HIGH) {
        delay(100);
    }
    return 0;
}


void JuizQuiz::drawQuestions(TFT_eSPI &d) {
    d.fillScreen(TFT_BLACK);
    d.setTextColor(TFT_WHITE);
    d.drawString(perguntas[perguntaAtual].enunciado, 10, 10, 2);
    for (int i = 0; i < MAX_ALTERNATIVAS; ++i) {
        d.drawString(String(i + 1) + ". " + perguntas[perguntaAtual].alternativas[i], 10, (distancia_alternativas * i)+50, 2);
    }
}

void JuizQuiz::updateAlternative(TFT_eSPI &d, int prev_index, int current_index) {
    // Atualiza a cor da alternativa anterior
    d.setTextColor(TFT_WHITE);
    d.drawString(String(prev_index + 1) + ". " + perguntas[perguntaAtual].alternativas[prev_index], 10, (distancia_alternativas * prev_index)+50, 2);

    // Atualiza a cor da alternativa atual
    d.setTextColor(TFT_YELLOW);
    d.drawString(String(current_index + 1) + ". " + perguntas[perguntaAtual].alternativas[current_index], 10, (distancia_alternativas * current_index)+50, 2);
}


//Mesma funcão do Menu - Usa o Joy
void JuizQuiz::trackPosition(TFT_eSPI &d, int &alternativa_index) {
    int valueJoyX = joy.read_raw_X();
    Direction directionX = joy.getDirectionX(valueJoyX);
    unsigned long currentTime = millis();

    if (currentTime - lastDebounceTime > debounceDelay) {
        lastDebounceTime = currentTime;

        int prev_index = alternativa_index;

        if (directionX == RIGHT) {
            alternativa_index++;
            if (alternativa_index >= MAX_ALTERNATIVAS) {
                alternativa_index = 0;
            }
        }

        if (directionX == LEFT) {
            alternativa_index--;
            if (alternativa_index < 0) {
                alternativa_index = MAX_ALTERNATIVAS - 1;
            }
        }

        if (prev_index != alternativa_index) {
            updateAlternative(d, prev_index, alternativa_index);
        }
    }
}


//Função que recebe valores do trackPosition e confirma se a resposta está correta
//Verifica se acertou ou não e manda pro score??
void JuizQuiz::select(TFT_eSPI &d, int &alternativa_index) {
    static bool buttonWasPressed = false;
    bool buttonPressed = (joy.read_button_central() == LOW);

    if (buttonPressed && !buttonWasPressed) {
        buttonWasPressed = true;

        int respostaCorreta = perguntas[perguntaAtual].respostaCorreta;
        int respostaSelecionada = alternativa_index;

        Serial.print("Resposta Correta: ");
        Serial.println(respostaCorreta);
        Serial.print("Resposta Selecionada: ");
        Serial.println(respostaSelecionada);

        if (respostaSelecionada == respostaCorreta) {
            pontuacao++;
            d.setTextColor(TFT_GREEN);
            d.drawString("Correto!", 10, 110, 2);
        } else {
            d.setTextColor(TFT_RED);
            d.drawString("Errado!", 10, 110, 2);
            d.setTextColor(TFT_WHITE);
            d.drawString("Resposta correta: ", 10, 130, 2);
            d.drawString(perguntas[perguntaAtual].alternativas[respostaCorreta], 10, 150, 2);
        }

        perguntaAtual++;
        alternativa_index = 0;
        delay(2000); // Espera 2 segundos antes de passar para a próxima pergunta
        if (perguntaAtual < totalPerguntas) {
            drawQuestions(d);
        }
    }

    if (!buttonPressed) {
        buttonWasPressed = false;
    }
}




int JuizQuiz::score(){
    return pontuacao;
}

bool JuizQuiz::isFinished(){
     return perguntaAtual >= totalPerguntas;
}