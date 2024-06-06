#include <Arduino.h>
#include <TFT_eSPI.h>

//Inicialização Display
TFT_eSPI d = TFT_eSPI();
TFT_eSprite ball = TFT_eSprite(&d);

void setup(){
  d.init();
  d.setRotation(1);
  d.fillScreen(TFT_BLACK);

  ball.setColorDepth(8);
  //Cria a Sprite um pouco maior do que o objeto que será desenhado dentro da Sprite
  ball.createSprite(40, 40); 
}

int x = 0;
int y = 0;

void loop(){
  //img.fillCircle(20, 20, 15,TFT_BLACK); //Também funcionou. Não vi diferença do fillSprite abaixo.
  //Apaga o conteúdo da sprite para não gerar o "rastro" e ficar só o movimento do objeto
  ball.fillSprite(TFT_BLACK);
  x=x+1;
  if(x>480){
    x=0;
  }
  ball.fillCircle(20, 20, 15, TFT_RED); //estatico, não mexe mais

  //Movimenta a sprite toda, e não o objeto dentro da sprite
  ball.pushSprite(x, y);
  

}