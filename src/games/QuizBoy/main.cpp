#include <Arduino.h>

// Estrutura da pergunta
struct Pergunta {
    const char* enunciado;
    const char* alternativas[4];
    int respostaCorreta;
};

// Vetor de perguntas
Pergunta perguntas[] = {
    {
        "Qual é a capital da França?",
        {"Berlim", "Madrid", "Paris", "Lisboa"},
        2
    },
    {
        "Qual é o maior planeta do sistema solar?",
        {"Terra", "Marte", "Júpiter", "Saturno"},
        2
    }
};

// Função para exibir uma pergunta
void exibirPergunta(const Pergunta& pergunta) {
    Serial.println(pergunta.enunciado);
    for (int i = 0; i < 4; ++i) {
        Serial.print(i + 1);
        Serial.print(". ");
        Serial.println(pergunta.alternativas[i]);
    }
}

void setup() {
    Serial.begin(115200);
    delay(1000);

    for (auto& pergunta : perguntas) {
        exibirPergunta(pergunta);
        Serial.println("Escolha uma alternativa (1-4):");
        
        while (!Serial.available()) {
            // Aguarda até que o usuário insira uma resposta
        }

        int respostaUsuario = Serial.parseInt() - 1;

        if (respostaUsuario == pergunta.respostaCorreta) {
            Serial.println("Correto!");
        } else {
            Serial.print("Errado! A resposta correta é: ");
            Serial.println(pergunta.alternativas[pergunta.respostaCorreta]);
        }
        Serial.println();
    }
}

void loop() {
    // O código do quiz está no setup()
}
