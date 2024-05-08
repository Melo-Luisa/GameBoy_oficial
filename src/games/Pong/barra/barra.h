#include "main.cpp"

class BARRA: public BALL{
    private:
        int coordY_old, coordY_new; //JOYSTICK
        int coordY; //BUTTON
    public:
        BARRA(int coordY_old, int coordY_new, int coordY);

        //funções
        void move_joy(int coordY_old, int coordY_new);
        void draw_joy(TFT_eSprite &barra_joy);

        void move_button(int coordY);
        void draw_button(TFT_eSprite &barra_button);
        
};


void BARRA::move_joy(int coordY_old, int coordY_new){
    int coordY = map(analogRead(joystick::eixo_y), 0, 4095, 0, 220);

    coordY_old = 100;//map(analogRead(EIXO_Y), 0, 4095, 0, 220);

    //barra do joystick
    
    //Serial.println(analogRead(EIXO_Y));

    coordY_new = map(analogRead(joystick::eixo_x), 0, 4095, 0, 220);
    //cima
    if(coordY_new > coordY_old){
        coordY += 10;
    }//baixo
    if(coordY_new < coordY_old){
        coordY -= 10;

    }
}

void BARRA::draw_joy(TFT_eSprite &barra_joy){
    barra_joy.setColorDepth(8);
    barra_joy.createSprite(100, 240);

    barra_joy.fillRect(15, coordY, barra::square_Width, barra::square_Height, TFT_WHITE);
    barra_joy.pushToSprite(&ball, 0, 0);
    barra_joy.fillRect(15, coordY, barra::square_Width, barra::square_Height, TFT_BLACK);
}

void BARRA::move_button(int coordY){
    if(digitalRead(button::azul) == 0){ //se o botao azul for apertado 
        if(coordY+ (barra::square_Height) <= 230){ 
            coordY += 10;
        }
    
    }
    else if(digitalRead(button::amarelo) == 0){ //se o botao azul for apertado 
        coordY -= 10;
        if(coordY+(barra::square_Height) == 50){ 
            coordY += 10;
        }
    
    }
}

void BARRA::draw_button(TFT_eSprite &barra_button){
    barra_button.fillRect(80, coordY, barra::square_Width, barra::square_Height, TFT_WHITE);
    // não esta puxando a classe ball
    barra_button.pushToSprite(&ball, 220, 0);
    barra_button.fillRect(80, coordY, barra::square_Width, barra::square_Height, TFT_BLACK);
}