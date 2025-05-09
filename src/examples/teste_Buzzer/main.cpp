// #include <Arduino.h>

// Define the GPIO pin connected to the buzzer
// #define BUZZER_PIN 22

// void playTone(int frequency, int duration) {
//   ledcSetup(0, frequency, 8); // Set the frequency
//   ledcAttachPin(BUZZER_PIN, 0);
//   ledcWrite(0, 128); // 50% duty cycle
//   delay(duration);
//   ledcWrite(0, 0); // Stop the sound
// }


// void playRightAnswerTone() {
//   // Resposta correta: tocar uma sequência melódica
//   playTone(1000, 200); // 1 kHz tom por 200 ms
//   delay(100);          // Pausa curta
//   playTone(1200, 200); // 1.2 kHz tom por 200 ms
//   delay(100);          // Pausa curta
//   playTone(1500, 300); // 1.5 kHz tom por 300 ms
// }


// void playWrongAnswerTone() {
//   // Wrong answer: play a low-pitched longer beep
//   playTone(500, 500); // 500 Hz tone for 500 ms
// }



// void setup() {
//   pinMode(BUZZER_PIN, OUTPUT);
  
//   // Example: Play right and wrong answer tones
//   playRightAnswerTone();
//   delay(1000); // Wait for 1 second
//   playWrongAnswerTone();
// }

// void loop() {
//   // Nothing to do here
// }

#include <Arduino.h>

const int PINO_BUZZER = 22; // Pode ser qualquer pino digital disponível

void setup() {
  pinMode(PINO_BUZZER, OUTPUT);
}

void loop() {
  digitalWrite(PINO_BUZZER, HIGH); // Liga o buzzer
  delay(500);                      // Espera 0.5s
  digitalWrite(PINO_BUZZER, LOW);  // Desliga o buzzer
  delay(500);                      // Espera 0.5s
}
