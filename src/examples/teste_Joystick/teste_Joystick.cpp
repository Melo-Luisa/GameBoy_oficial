#include <Arduino.h>
#include "joystick.h"

const int xAxisPin = 33; // Pin connected to X axis of joystick
const int yAxisPin = 32; // Pin connected to Y axis of joystick

const int threshold = 1000; // Adjust this threshold as needed

enum Direction { NONE, UP, DOWN, LEFT, RIGHT };

Direction prevDirectionX = NONE;
Direction prevDirectionY = NONE;

// Function declarations
Direction getDirectionX(int value, int threshold);
Direction getDirectionY(int value, int threshold);
void printDirection(Direction dir);

void setup() {
  Serial.begin(115200);
}

void loop() {
  // Read analog values from joystick axes
  int xAxisValue = analogRead(xAxisPin);
  int yAxisValue = analogRead(yAxisPin);

  // Check X axis
  Direction currentDirectionX = getDirectionX(xAxisValue, threshold);

  if (currentDirectionX != prevDirectionX) {
    printDirection(currentDirectionX);
    prevDirectionX = currentDirectionX;
  }

  // Check Y axis
  Direction currentDirectionY = getDirectionY(yAxisValue, threshold);

  if (currentDirectionY != prevDirectionY) {
    printDirection(currentDirectionY);
    prevDirectionY = currentDirectionY;
  }

 
}

Direction getDirectionX(int value, int threshold) {
  if (value < 2048 - threshold) {
    return LEFT;
  } else if (value > 2048 + threshold) {
    return RIGHT;
  } else {
    return NONE;
  }
}

Direction getDirectionY(int value, int threshold) {
  if (value < 2048 - threshold) {
    return UP;
  } else if (value > 2048 + threshold) {
    return DOWN;
  } else {
    return NONE;
  }
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
