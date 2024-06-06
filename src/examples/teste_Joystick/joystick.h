#pragma once
#include <Arduino.h>



const int threshold = 1000; // Adjust this threshold as needed

enum Direction { NONE, UP, DOWN, LEFT, RIGHT , CENTRAL};

Direction prevDirectionX = NONE;
Direction prevDirectionY = NONE;
bool prevCentralState = HIGH;


class Joystick {
  private:
  int xAxisPin; // Pin connected to X axis of joystick
  int yAxisPin; // Pin connected to Y axis of joystick
  int centralPin;


  public:
    Joystick(int xAxisPin, int yAxisPin, int centralPin) {
      this->xAxisPin = xAxisPin;
      this->yAxisPin = yAxisPin;
      this->centralPin = centralPin;

      pinMode(xAxisPin, INPUT);
      pinMode(yAxisPin, INPUT);
      pinMode(centralPin, INPUT_PULLUP);
    }

    void debug(){
      Serial.print("X: " + String(analogRead(xAxisPin)));
      Serial.println(" - Y: " + String(analogRead(yAxisPin)));
      Serial.println(" - Central: " + String(digitalRead(centralPin)));
    }
    
    int read_raw_X(){
      int readRawX = analogRead(xAxisPin);
      return readRawX;
    }

    int read_raw_Y(){
      int readRawY = analogRead(yAxisPin);
      return readRawY;
    }

     int read_button_central(){
      int readCentral = digitalRead(centralPin);
      return readCentral;
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
        case CENTRAL:
          Serial.println("Central");
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

      bool currentCentralState = read_button_central();
      if (currentCentralState == LOW && prevCentralState == HIGH) {
        printDirection(CENTRAL);
      }
      prevCentralState = currentCentralState;
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



