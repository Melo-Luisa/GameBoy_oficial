
#include <Arduino.h>
#include <TFT_eSPI.h>
#include <SPI.h>

const int SQUARE_WIDTH = 320;
const int SQUARE_HEIGHT = 240;

// Barra pinos
const int EIXO_X = 33;
const int EIXO_Y = 32;

// Botões pinos
const int botao_azul = 34; // Azul
const int botao_amarelo = 35; // Amarelo

// Bola infos
const int BALL_SIZE = 10;

// Joy infos
const int BAR_WIDTH = 10;
const int BAR_HEIGHT = 40;

class Pong {
private:

    TFT_eSPI d;  //init display
    TFT_eSprite ball = TFT_eSprite(&d);
    TFT_eSprite barra1 = TFT_eSprite(&d);
    TFT_eSprite barra2 = TFT_eSprite(&d);
    TFT_eSprite placar = TFT_eSprite(&d);


    class Ball_m {
    private:
        int x;
        int y;
        int vx;
        int vy;

    public:
        Ball_m(int initial_x, int initial_y, int initial_vx, int initial_vy) : x(initial_x), y(initial_y), vx(initial_vx), vy(initial_vy) {}

        void move() {
            if (y <= 0 || y >= SQUARE_HEIGHT - BALL_SIZE) {
                vy = -vy;
            }
            x += vx;
            y += vy;
        }

        void draw() {
            ball.fillCircle(x, y, BALL_SIZE, TFT_BLACK);
            ball.fillCircle(x, y, BALL_SIZE, TFT_RED);
        }
    };

    class Bar_button {
    private:
        int botao_azul;
        int botao_amarelo;
        int coordY_B2;

    public:
        Bar_button(int initial_coordY_B2) : coordY_B2(initial_coordY_B2) {}

        void move() {
            if (digitalRead(botao_azul) == 0) { // Se o botão azul for apertado
                if (coordY_B2 + (SQUARE_WIDTH) <= 230) {
                    coordY_B2 += 10;
                }
            } else if (digitalRead(botao_amarelo) == 0) { // Se o botão amarelo for apertado
                coordY_B2 -= 10;
                if (coordY_B2 + (SQUARE_HEIGHT) == 50) {
                    coordY_B2 += 10;
                }
            }
        }

        void draw() {
            barra2.fillRect(80, coordY_B2, SQUARE_WIDTH, SQUARE_HEIGHT, TFT_WHITE);
        }
    };

    class Bar {
    private:
        int coordY_B1;
        int coordY_B1_antiga;
        int coordY_B1_atual;

    public:
        Bar(int initial_coordY_B1, int initial_coordY_B1_antiga, int initial_coordY_B1_atual) : coordY_B1(initial_coordY_B1), coordY_B1_antiga(initial_coordY_B1_antiga), coordY_B1_atual(initial_coordY_B1_atual) {}

        void move() {
            coordY_B1_atual = map(analogRead(EIXO_Y), 0, 4095, 0, 220);
            // Cima
            if (coordY_B1_atual > coordY_B1_antiga) {
                coordY_B1 += 10;
            } // Baixo
            if (coordY_B1_atual < coordY_B1_antiga) {
                coordY_B1 -= 10;
            }
        }

        void draw() {
            barra1.fillRect(15, coordY_B1, SQUARE_WIDTH, SQUARE_HEIGHT, TFT_WHITE);
        }
    };

    Ball_m ball;
    Bar_button bar_button;
    Bar bar;

public:
    Pong() : ball(SQUARE_WIDTH / 2, SQUARE_HEIGHT / 2, 2, 2), bar_button(SQUARE_HEIGHT / 2 - BAR_HEIGHT / 2), bar(SQUARE_HEIGHT / 2 - BAR_HEIGHT / 2, 0, 0) {}

    void setup() {
        d.init();
        d.setRotation(1); // Ajuste a rotação do display conforme necessário
        d.fillScreen(TFT_BLACK);

        ball.setColorDepth(8);
        ball.createSprite(320, 240);

        barra1.setColorDepth(8);
        barra1.createSprite(50, 240);

        barra2.setColorDepth(8);
        barra2.createSprite(100, 240);

        placar.setColorDepth(8);
        placar.createSprite(120, 50);
        placar.setTextDatum(MC_DATUM);
    }

    void loop() {
        d.fillScreen(TFT_BLACK);

        ball.move();
        bar_button.move();
        bar.move();

        ball.draw();
        bar_button.draw();
        bar.draw();

        ball.pushSprite(0, 0);
        barra1.pushSprite(0, 0);
        barra2.pushSprite(0, 0);
        placar.pushSprite(0, 0);

        delay(30);
    }
};

// Função principal
void setup() {
    Pong pong;
    pong.setup();

    while (true) {
        pong.loop();
    }
}

void loop() {
    // Nada a fazer aqui, todo o código está no setup()
}













// class Pong{
//     public:
//         TFT_eSPI d;
//         TFT_eSprite ball;
//         TFT_eSprite barra1;
//         TFT_eSprite barra2;
//         TFT_eSprite placar;

//         /*Falta parametros*/

//         int vx = 10, vy = 10; //velocidade da bolinha
//         int x = 100, y = 50;

//         int square_Width = 10;
//         int square_Height = 60;

//         //Barra joystick
//         int coordX_B1 = 15;
//         int coordY_B1 = 100;

//         int coordY_B1_atual = 100;
//         int coordY_B1_antiga = 100;


//         //Barra botoes
//         int coordY_B2 = 100; //eh y
    
//         void init();

//         void update_Score(TFT_eSprite placar, int countBlack, int countWhite);

//         boolean hit_direita(int x, int circleRadius, int coordY_B2, int square_Height);

//         boolean hit_esquerda(int x, int circleRadius, int coordY_B2, int square_Height, int square_Width);

//         void ball_a(int x, int y, int vy, int vx, int countBlack, int countWhite, int circleRadius, TFT_eSprite barra2);

//         void joystick_m(int coordY_B1, int coordY_B1_antiga, TFT_eSprite barra1, int square_Width, int square_Height);

//         void button_m(int botao_azul, int botao_amarelo, int coordY_B2, TFT_eSprite barra2);


// };