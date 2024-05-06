#include "pong.h"

Pong pon;


void setup() {
    Serial.begin(115200);

    pong.init();

    //joystick
    //pinMode(EIXO_X, INPUT);
    pinMode(EIXO_Y, INPUT);
    //buttons
    pinMode(pong.botao_azul, INPUT_PULLUP);
    pinMode(pong.botao_amarelo, INPUT_PULLUP);
 }
void loop() {
    pong.ball_a(pong.x,  pong.y,  pong.vy,  pong.vx,  pong.countBlack,  pong.countWhite,  pong.circleRadius,  pong.barra2); 
    pong.joystick_m(pong.coordY_B1,  pong.coordY_B1_antiga,  pong.barra1,  pong.square_Width,  pong.square_Height);
    pong.button_m(pong.botao_azul,  pong.botao_amarelo,  pong.coordY_B2,  pong.barra2);
    pong.update_Score(pong.placar,pong.countBlack, pong.countWhite);
    
    //TAVA DANDO ERRO NAS VARIÁVEIS PQ ELAS ESTÃO DECLARADAS DENTRO DA CLASSE. TIVE QUE COLOCAR .PONG 
    //MUDAR AS VARIÁVEIS PARA O .H MAS PRA FORA DA CLASSE. -> MAS CONTINUAR PRA VER OQ DA.

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
