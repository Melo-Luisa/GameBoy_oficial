#pragma once

#include  "config.h"
//#include "joystick.h"


class JuizVelha{
    private:
  //  Joystick joy;
    

    public:

    JuizVelha();

    void showIntro(TFT_eSPI &d);
    void drawLines(TFT_eSPI &d);


};

JuizVelha::JuizVelha() {
    // Constructor definition (you can leave it empty if no initialization is needed)
}


void JuizVelha::showIntro(TFT_eSPI &d){

}

void JuizVelha::drawLines(TFT_eSPI &d){
    // Set the color for the grid lines (white)
    uint16_t lineColor = d.color565(255, 255, 255);

    // Line thickness (draw multiple lines close to each other)
    int thickness = 4;  // Adjust thickness as needed

    // Grid dimensions
    int xStart = 100;  // Left margin
    int yStart = 20;   // Top margin
    int cellSize = 93; // Size of each cell in the grid (280 / 3)

    // Draw thicker vertical lines
    for (int i = 0; i < thickness; i++) {
    d.drawLine(xStart + cellSize - i, yStart, xStart + cellSize - i, yStart + 280, lineColor);  // First vertical line
    d.drawLine(xStart + 2 * cellSize - i, yStart, xStart + 2 * cellSize - i, yStart + 280, lineColor);  // Second vertical line
    }

    // Draw thicker horizontal lines
    for (int i = 0; i < thickness; i++) {
    d.drawLine(xStart, yStart + cellSize - i, xStart + 280, yStart + cellSize - i, lineColor);  // First horizontal line
    d.drawLine(xStart, yStart + 2 * cellSize - i, xStart + 280, yStart + 2 * cellSize - i, lineColor);  // Second horizontal line
    }

}




