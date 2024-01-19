#include <TFT_eSPI.h>
#include "image.h"

TFT_eSPI d = TFT_eSPI();

void setup(){
    d.init();
    d.setRotation(1);
    d.setSwapBytes(true);
    d.fillScreen(TFT_BLACK);
    d.pushImage(20,20,196,240,image);
    d.pushImage(40,20,196,240,image);
    d.pushImage(50,20,196,240,image);
    d.pushImage(20,20,196,240,image);
}

void loop(){

}