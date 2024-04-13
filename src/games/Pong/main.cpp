#include "funcoesPong.h"

void setup() {
    Serial.begin(115200);
    d.init();
    d.fillScreen(TFT_BLACK);
    d.setRotation(1); //origem fita verde

    //Ball sprite
    ball.setColorDepth(8);
    ball.createSprite(320, 240);

    //Barra 1 Sprite
    barra1.setColorDepth(8);
    barra1.createSprite(50, 240);

    //Barra 2 Sprite
    barra2.setColorDepth(8);
    barra2.createSprite(100, 240);

    //joystick
    //pinMode(EIXO_X, INPUT);
    pinMode(EIXO_Y, INPUT);
    //buttons
    pinMode(botao_azul, INPUT_PULLUP);
    pinMode(botao_amarelo, INPUT_PULLUP);

   
}
void loop() {

    //--------------BOLINHA---------------
    ball_a();
    
    //----------------BARRA JOYSTICK-------------
    joystick_m();

    //-----------------BARRA BOTOES-----------------

    button_m();

    hit();
    /*
    Serial.print("X: ");
    Serial.print(x);
    Serial.print("Y: ");
    Serial.println(y);
    */
    delay(10);

}











/* CODIGO EXEMPLO DAS SPRITES

    img.fillCircle(x, 50, 10, TFT_BLACK); //desenha um circulo preto pra apagar o antigo
    //atualiza as coordenadas pra ele se mover
    x=x+1;
    if(x>320){
      x=0;
    }

    img.fillCircle(x, 50, 10, TFT_WHITE); //circulo branco, que está aparecendo
    img.fillRect(18, 70, 100, 100, TFT_BLACK); //retangulo preto pra apagar os numeros antigos
    img.drawString(String(x), 20, 74, 7); //posicao do circulo

*/
/*---------- CHATGPT TOQUE --------------
coordX_B2 = map(analogRead(EIXO_X), 0, 4095, 0, 300); 
coordY_B2 = map(analogRead(EIXO_Y), 0, 4095, 0, 220);
Serial.print(analogRead(EIXO_X));
Serial.println(analogRead(EIXO_Y));
if (x + circleRadius >= coordX_B1 && x - circleRadius <= coordX_B1 + square_Width &&
    y + circleRadius >= coordY_B1 && y - circleRadius <= coordY_B1 + square_Height) {
    // Inverte a velocidade da bola
    x -= vx;
    y -= vy;

    Serial.print("Toquei");
}*/
