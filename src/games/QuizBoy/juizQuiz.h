//o juiz faz toda a lógica de pegar as perguntas e verificar tudo e etc
#pragma once

#include "config.h"
#include "questions.h"
#include "joystick.h"

#define MAX_PERGUNTAS 20
#define MAX_ALTERNATIVAS 3



class JuizQuiz{
    //variaveis
    private:
    Joystick joy;
    Pergunta perguntas[MAX_PERGUNTAS];
    int pontuacaoJogador;
    int pontuacaoGB;
    int perguntaAtual;
    int totalPerguntas;

    int alternativa_index;

    bool question_ON; //se estiver uma pergunta aparecendo na tela. É usada no alternativa_index

    unsigned long lastDebounceTime = 0;
    const unsigned long debounceDelay = 200;

    int distancia_alternativas = 40;


    int red = 255; // Starting color
    int green = 0;
    int blue = 0;

int step = 10; // Step value for color change
    public:
    //funções
    JuizQuiz(Pergunta p[], int total);

    int showIntros(TFT_eSPI &d);

    void drawQuestions(TFT_eSPI &d);

    void updateAlternative(TFT_eSPI &d, int prev_index, int current_index);

    void trackPosition(TFT_eSPI &d, int &alternativa_index);

    void select(TFT_eSPI &d, int &alternativa_index);

    int scoreJogador();

    int scoreGB();

    bool isFinished();

    void updateColor(TFT_eSPI &d);

    
    void initQuiz(TFT_eSPI &d);

    void endQuiz(TFT_eSPI &d);



};


JuizQuiz::JuizQuiz(Pergunta p[], int total):pontuacaoJogador(0), pontuacaoGB(0), perguntaAtual(0), totalPerguntas(total), alternativa_index(0), joy(joystick::eixo_x, joystick::eixo_y, joystick::botao_joy) {
    for(int i=0; i < total; i++){
        perguntas[i] = p[i];
    }
}

void JuizQuiz::initQuiz(TFT_eSPI &d){
    if (!isFinished()) {
        trackPosition(d, alternativa_index);
        select(d, alternativa_index);
    }
}

void JuizQuiz::endQuiz(TFT_eSPI &d){
        d.fillScreen(TFT_BLACK);
        d.setTextColor(d.color565(255, 150, 0));    
        d.drawString("The End", 160, 10, 2);
        if(scoreGB() > scoreJogador()){ //gameboy ganhou
            d.setTextSize(3);
            d.setTextColor(TFT_GREEN);
            d.drawString("GameBoy", 30, 80, 2);
            d.drawString((String(scoreGB())), 80, 150);
            d.setTextColor(TFT_WHITE);
            d.drawString("x", 230, 80, 2);
            d.setTextColor(TFT_RED);
            d.drawString("Player", 320, 80, 2);
            d.drawString(String(scoreJogador()), 360, 150);
            d.setTextColor(TFT_WHITE);
            d.setTextSize(2);
            d.drawString("Aparentemente o GameBoy sabe mais...", 30, 250);

            
        }else{ //jogador ganhou
            d.setTextSize(3);
            d.setTextColor(TFT_RED);
            d.drawString("GameBoy", 30, 80, 2);
            d.drawString((String(scoreGB())), 80, 150);
            d.setTextColor(TFT_WHITE);
            d.drawString("x", 230, 80, 2);
            d.setTextColor(TFT_GREEN);
            d.drawString("Player", 320, 80, 2);
            d.drawString(String(scoreJogador()), 360, 150);
            d.setTextColor(TFT_WHITE);   
            d.setTextSize(2);
            d.drawString("Tu Realmente Entende de Jogos Hein...", 20, 250);
        }
    pontuacaoGB = 0;
    pontuacaoJogador = 0;
    alternativa_index = 0;
    perguntaAtual = 0;
    delay(3000);
}

void JuizQuiz::updateColor(TFT_eSPI &d) {
  if (red == 255 && green < 255 && blue == 0) {
    green += step; // Increase green
  } else if (green == 255 && red > 0 && blue == 0) {
    red -= step; // Decrease red
  } else if (green == 255 && blue < 255 && red == 0) {
    blue += step; // Increase blue
  } else if (blue == 255 && green > 0 && red == 0) {
    green -= step; // Decrease green
  } else if (blue == 255 && red < 255 && green == 0) {
    red += step; // Increase red
  } else if (red == 255 && blue > 0 && green == 0) {
    blue -= step; // Decrease blue
  }
  
  // Ensure color values stay within bounds
  red = constrain(red, 0, 255);
  green = constrain(green, 0, 255);
  blue = constrain(blue, 0, 255);
  
  uint16_t color = d.color565(red, green, blue);
  d.fillScreen(color); // Update the screen with the new color
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
    d.setTextSize(2);


    if (perguntas[perguntaAtual].func != nullptr) {
        perguntas[perguntaAtual].func(d); // Chama a função associada à pergunta
    } else {
        Serial.println("Função da pergunta não definida.");
    }
    d.setTextSize(3);
    for (int i = 0; i < MAX_ALTERNATIVAS; ++i) {
        d.drawString(String(i + 1) + ". " + perguntas[perguntaAtual].alternativas[i], 10, (distancia_alternativas * i) + 200);
    }
}

void JuizQuiz::updateAlternative(TFT_eSPI &d, int prev_index, int current_index) {
    d.setTextSize(3);
    // Atualiza a cor da alternativa anterior
    d.setTextColor(TFT_WHITE);
    d.drawString(String(prev_index + 1) + ". " + perguntas[perguntaAtual].alternativas[prev_index], 10, (distancia_alternativas * prev_index)+200);

    // Atualiza a cor da alternativa atual
    d.setTextColor(TFT_YELLOW);
    d.drawString(String(current_index + 1) + ". " + perguntas[perguntaAtual].alternativas[current_index], 10, (distancia_alternativas * current_index)+200);
}


//Mesma funcão do Menu - Usa o Joy
void JuizQuiz::trackPosition(TFT_eSPI &d, int &alternativa_index) {
    int valueJoyX = analogRead(joystick::eixo_y); //joy.read_raw_X();
    Direction directionX = joy.getDirectionY(valueJoyX);
    unsigned long currentTime = millis();

    if (currentTime - lastDebounceTime > debounceDelay) {
        lastDebounceTime = currentTime;

        int prev_index = alternativa_index;

        if (directionX == UP) {
            alternativa_index++;
            if (alternativa_index >= MAX_ALTERNATIVAS) {
                alternativa_index = 0;
            }
        }

        if (directionX == DOWN) {
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
    bool buttonPressed = ((digitalRead(button::azul) == LOW) || joy.read_button_central() == LOW);

    if (buttonPressed && !buttonWasPressed) {
        buttonWasPressed = true;

        int respostaCorreta = perguntas[perguntaAtual].respostaCorreta;
        int respostaSelecionada = alternativa_index;

        Serial.print("Resposta Correta: ");
        Serial.println(respostaCorreta);
        Serial.print("Resposta Selecionada: ");
        Serial.println(respostaSelecionada);

        if (respostaSelecionada == respostaCorreta) {
            d.fillScreen(TFT_BLACK);
            pontuacaoJogador++;
            d.setTextColor(TFT_GREEN);
            d.drawString("Correto!", 180, 120, 2);
            d.setTextColor(TFT_WHITE);
            d.drawString("Ponto pra Você!", 150, 200, 2);
        } else {
            pontuacaoGB++;
            d.fillScreen(TFT_BLACK);
            d.setTextColor(TFT_RED);
            d.drawString("Errado!", 180, 100, 2);
            d.setTextColor(TFT_WHITE);
            d.drawString("Ponto pro GameBoy", 80, 150, 2);
            d.drawString("Resposta correta: ", 80, 200, 2);
            d.drawString(perguntas[perguntaAtual].alternativas[respostaCorreta], 80, 250, 2);
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




int JuizQuiz::scoreJogador(){
    return pontuacaoJogador;
}


int JuizQuiz::scoreGB(){
    return pontuacaoGB;
}

bool JuizQuiz::isFinished(){
     return perguntaAtual >= 5;
}