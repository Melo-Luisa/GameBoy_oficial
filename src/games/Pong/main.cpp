#include "function_pong.cpp"

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
    
    //Placar
    placar.setColorDepth(8);
    placar.createSprite(120, 50);
    placar.setTextDatum(MC_DATUM); 

    //joystick
    //pinMode(EIXO_X, INPUT);
    pinMode(EIXO_Y, INPUT);
    //buttons
    pinMode(botao_azul, INPUT_PULLUP);
    pinMode(botao_amarelo, INPUT_PULLUP);
 }
void loop() {
    ball_a( x,  y,  vy,  vx,  countBlack,  countWhite,  circleRadius,  barra2); 
    joystick_m( coordY_B1,  coordY_B1_antiga,  barra1,  square_Width,  square_Height);
    button_m( botao_azul,  botao_amarelo,  coordY_B2,  barra2);
    update_Score( placar,countBlack, countWhite);
    

}





// /* CODIGO EXEMPLO DAS SPRITES

//     img.fillCircle(x, 50, 10, TFT_BLACK); //desenha um circulo preto pra apagar o antigo
//     //atualiza as coordenadas pra ele se mover
//     x=x+1;
//     if(x>320){
//       x=0;
//     }

//     img.fillCircle(x, 50, 10, TFT_WHITE); //circulo branco, que está aparecendo
//     img.fillRect(18, 70, 100, 100, TFT_BLACK); //retangulo preto pra apagar os numeros antigos
//     img.drawString(String(x), 20, 74, 7); //posicao do circulo

// */
// /*---------- CHATGPT TOQUE --------------
// coordX_B2 = map(analogRead(EIXO_X), 0, 4095, 0, 300); 
// coordY_B2 = map(analogRead(EIXO_Y), 0, 4095, 0, 220);
// Serial.print(analogRead(EIXO_X));
// Serial.println(analogRead(EIXO_Y));
// if (x + circleRadius >= coordX_B1 && x - circleRadius <= coordX_B1 + square_Width &&
//     y + circleRadius >= coordY_B1 && y - circleRadius <= coordY_B1 + square_Height) {
//     // Inverte a velocidade da bola
//     x -= vx;
//     y -= vy;

//     Serial.print("Toquei");
// }*/
