//#include "joystick.h"
#include <Arduino.h>



const int threshold = 1000; // Adjust this threshold as needed

enum Direction { NONE, UP, DOWN, LEFT, RIGHT };

Direction prevDirectionX = NONE;
Direction prevDirectionY = NONE;


class Joystick {
  private:
  int xAxisPin; // Pin connected to X axis of joystick
  int yAxisPin; // Pin connected to Y axis of joystick


  public:
    Joystick(int xAxisPin, int yAxisPin) {
      this->xAxisPin = xAxisPin;
      this->yAxisPin = yAxisPin;

      pinMode(xAxisPin, INPUT);
      pinMode(yAxisPin, INPUT);
    }

    void debug(){
      Serial.print("X: " + String(analogRead(xAxisPin)));
      Serial.println(" - Y: " + String(analogRead(yAxisPin)));
    }
    
    int read_raw_X(){
      int readRawX = analogRead(xAxisPin);
      return readRawX;
    }

    int read_raw_Y(){
      int readRawY = analogRead(yAxisPin);
      return readRawY;
    }

    int coordX(){
      int coordX = map(analogRead(xAxisPin), 0, 4095, 0, 300); //NÃO ESTÁ O VALOR CHEIO DA TELA P/ A BOLINHA NÃO PASSAR. VISTO QUE 0,0 DA BOLINHA É SUP. ESQ.
      //NÃO SEI SE É A MELHOR FORMA DE IMPLEMENTAR ESSE CÓDIGO, SEM O VALOR CHEIO DA TELA. 
      return coordX;
    }

    int coordY(){
      //MESMO "PROBLEMA DO COORD X EM RELAÇÃO AO TAMANHO DA TELA/LIMITES DO MAP"
      int coordY = map(analogRead(yAxisPin), 0, 4095, 0, 220);
      return coordY;
    }

    void printDirection(Direction dir) {
      switch (dir) {
        case UP:
          Serial.println("Up");
          break;
        case DOWN:
          Serial.println("Down");
          break;
        case LEFT:
          Serial.println("Left");
          break;
        case RIGHT:
          Serial.println("Right");
          break;
        default:
          break;
      }
    }

    void checkAndPrintDirections(int xAxisValue, int yAxisValue) {
      Direction currentDirectionX = getDirectionX(xAxisValue);
      static Direction prevDirectionX = NONE;
      if (currentDirectionX != prevDirectionX) {
        printDirection(currentDirectionX);
        prevDirectionX = currentDirectionX;
      }

      Direction currentDirectionY = getDirectionY(yAxisValue);
      static Direction prevDirectionY = NONE;
      if (currentDirectionY != prevDirectionY) {
        printDirection(currentDirectionY);
        prevDirectionY = currentDirectionY;
      }
    }

    Direction getDirectionX(int value) {
    if (value < 2048 - threshold) {
      return LEFT;
    } else if (value > 2048 + threshold) {
      return RIGHT;
    } else {
      return NONE;
    }
  }

  Direction getDirectionY(int value) {
    if (value < 2048 - threshold) {
      return UP;
    } else if (value > 2048 + threshold) {
      return DOWN;
    } else {
      return NONE;
    }
  }

};

Joystick joystick(32, 33);

void setup() {
  Serial.begin(115200);
}

void loop() {
  // Read analog values from joystick axes
  int xAxisValue = analogRead(32);
  int yAxisValue = analogRead(33);

  // Check and print directions
  joystick.checkAndPrintDirections(xAxisValue, yAxisValue);
  //joystick.debug();
}
