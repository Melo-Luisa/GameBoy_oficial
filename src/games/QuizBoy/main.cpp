#include <Arduino.h>
#include <TFT_eSPI.h>
#include <SPI.h>

#include "juizQuiz.h"
#include "config.h"



TFT_eSPI tft = TFT_eSPI();  // Inicialização da tela

int alternativa_index = 0;


JuizQuiz quiz(perguntas, 5);

void setup() {
    Serial.begin(115200);
    tft.init();
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);
    
    quiz.showIntros(tft);
    quiz.drawQuestions(tft);

}



void loop(){


    quiz.initQuiz(tft);

    
    
}


//CÓDIGO QUE FUNCIONA PARA GERAR VETOR ÚNICO ALEATÓRIO
/*
#include <Arduino.h>

// Função para gerar um vetor de valores únicos aleatórios
int* generateUniqueRandomArray(int size, int minValue, int maxValue) {
  static int values[5]; // Vetor estático para manter a alocação de memória
  bool isUnique;

  for (int i = 0; i < size; i++) {
    do {
      isUnique = true;
      values[i] = random(minValue, maxValue + 1);  // Gera um número aleatório no intervalo especificado
      for (int j = 0; j < i; j++) {
        if (values[i] == values[j]) {
          isUnique = false;
          break;
        }
      }
    } while (!isUnique);
  }
  return values;
}

void setup() {
  Serial.begin(115200);

  // Inicializar a semente do gerador de números aleatórios
  randomSeed(micros());

  // Tamanho do vetor e intervalo dos valores aleatórios
  const int size = 5;
  const int minValue = 0;
  const int maxValue = 12;

  // Gerar o vetor de valores únicos aleatórios
  int* randomValues = generateUniqueRandomArray(size, minValue, maxValue);

  // Exibir os valores no Serial Monitor
  Serial.println("Vetor gerado:");
  for (int i = 0; i < size; i++) {
    Serial.println(randomValues[i]);
  }
}

void loop() {
  // O loop está vazio porque só precisamos gerar o vetor uma vez
}
*/