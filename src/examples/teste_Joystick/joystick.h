#include <Arduino.h>

const int xAxisPin = 33; // Pin connected to X axis of joystick
const int yAxisPin = 32; // Pin connected to Y axis of joystick


const int threshold = 1000; // Adjust this threshold as needed

enum Direction { NONE, UP, DOWN, LEFT, RIGHT };

Direction prevDirectionX = NONE;
Direction prevDirectionY = NONE;

class JOYSTICK {
public:
  JOYSTICK() {}

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

private:

        int EIXO_X;
        int EIXO_Y;

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



/*
class JOYSTICK{
    private:
        int EIXO_X;
        int EIXO_Y;

  
    public:

        JOYSTICK(int EIXO_X, int EIXO_Y);

        void debug();
        int read_raw_X();
        int read_raw_Y();
 
        int coord_X();
        int coord_Y();



};
*/
