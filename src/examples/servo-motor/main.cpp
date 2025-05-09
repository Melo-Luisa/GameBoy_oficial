#include <ESP32Servo.h>//INCLUSÃO DA BIBLIOTECA NECESSÁRIA
 
const int pinoServo = 6; //PINO DIGITAL UTILIZADO PELO SERVO  
 
Servo s; //OBJETO DO TIPO SERVO
int pos; //POSIÇÃO DO SERVO
 
void setup() {
  s.setPeriodHertz(50); // Frequência típica para servos
  s.attach(pinoServo, 500, 2400); // PWM mínimo e máximo em microssegundos
  delay(5000);
  s.write(0);
}

void loop() {
  for (pos = 0; pos < 180; pos++) {
    s.write(pos);
    delay(15);
  }
  delay(1000);
  for (pos = 180; pos >= 0; pos--) {
    s.write(pos);
    delay(15);
  }
}
