
class BALL{
    private:
        int x, y, vx, vy, circleRadius;
        
    public:
        BALL(int x, int y, int vx, int vy, int circleRadius);

        //funções
        void move();
        // void placar(TFT_eSprite &placar);
        // void draw(TFT_eSprite &ball);
        // boolean hit_direita();
        // boolean hit_esquerda();
};


void BALL::move(){
    if (y <= 0 || y >= 240 - circleRadius) {
        vy = -vy;
    }
    x += vx;
    y += vy;  

    // if (x <= 0) { // esquerda
    //     x = 240 - circleRadius;
    //     countWhite +=1;
    //     //coloquei o ou mas não tenho certeza
    //     if(countWhite == 10 || countBlack == 10){
    //         countBlack = 0;
    //         countWhite = 0;
    //     }
    // } else if (x >= 240 +20 ) {
    //     x = circleRadius;
    //     countBlack += 1;
        
    //     if(countBlack == 10 || countBlack == 10){

    //         countBlack = 0;
    //         countWhite = 0;
    //     }
    // }
    // //devo colocar todos os argumentos?
    // if(hit_direita()){
    //     vx = -vx;
    //     vy = -vy;
    // }
    // if(hit_esquerda()){
    //     vx = -vx;
    //     vy = -vy;
    // }
}

// void BALL::placar(TFT_eSprite &placar){
//     placar.setColorDepth(8);
//     placar.createSprite(120, 50);
//     placar.setTextDatum(MC_DATUM); 

//     Serial.print(countWhite);
//     Serial.print("X");
//     Serial.print(countBlack);
//     Serial.println();

//     placar.fillSprite(TFT_BLUE);
//     // Desenhe texto no sprite
//     placar.setTextColor(TFT_WHITE);
//     placar.drawString(String(countBlack), 20, 25, 7);
//     placar.drawString("x", 70, 25, 4);
//     placar.drawString(String(countWhite), 120, 25, 7);

//     // Exiba o sprite na tela
//     placar.pushToSprite(&ball,85, 5, TFT_BLACK);
// }
// void BALL::draw(TFT_eSprite &ball){

//     ball.setColorDepth(8);
//     ball.createSprite(320, 240);

//     ball.fillCircle(x, y, circleRadius, TFT_BLACK);
//     ball.fillCircle(x, y, circleRadius, TFT_RED);
//     ball.pushSprite(0, 0);
// }

// boolean BALL::hit_direita(){
//     boolean result_dir = false;

//     //COLISÃO BARRA DIREITA - BUTTOn
//     if ( (x + circleRadius) >= 300 && (y >= ((coordY_2)) && y <= (coordY_2 + barra::square_Height))) {
//         result_dir = true;
//         //Serial.println("Bateu direita");
//     }   
    
//     return result_dir;
// }

// boolean BALL::hit_esquerda(){
//     boolean result_esq = false;
//     //COLISÃO BARRA ESQUERDA - JOY
//     if ((x - circleRadius) == 0 && (y >= ((coordY_1))  && y <= (coordY_1 + (barra::square_Height + barra::square_Width))) ) {
//         result_esq = true;
//         //Serial.println("Bateu Esquerda");
//     }
//     return result_esq;
// }