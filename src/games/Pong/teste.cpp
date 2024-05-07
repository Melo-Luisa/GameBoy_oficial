#include <Arduino.h>
#include <TFT.h>

TFT tft;

// Definindo as dimensões da tela
const int SCREEN_WIDTH = 320;
const int SCREEN_HEIGHT = 240;

// Definindo as dimensões da bola
const int BALL_SIZE = 10;

// Definindo as dimensões da barra
const int BAR_WIDTH = 10;
const int BAR_HEIGHT = 40;

class Pong {
private:
    class Ball {
    private:
        int x, y;
        int dx, dy;

    public:
        Ball(int initialX, int initialY, int initialDX, int initialDY) : x(initialX), y(initialY), dx(initialDX), dy(initialDY) {}

        void move() {
            x += dx;
            y += dy;

            // Lógica para rebater a bola quando atingir as bordas da tela
            if (x <= 0 || x >= SCREEN_WIDTH - BALL_SIZE) {
                dx = -dx;
            }
            if (y <= 0 || y >= SCREEN_HEIGHT - BALL_SIZE) {
                dy = -dy;
            }
        }

        void draw() {
            tft.fillCircle(x, y, BALL_SIZE, TFT_WHITE);
        }
    };

    class Bar {
    private:
        int x, y;

    public:
        Bar(int initialX, int initialY) : x(initialX), y(initialY) {}

        void move(int dy) {
            y += dy;

            // Limitando a movimentação da barra dentro da tela
            if (y < 0) {
                y = 0;
            } else if (y > SCREEN_HEIGHT - BAR_HEIGHT) {
                y = SCREEN_HEIGHT - BAR_HEIGHT;
            }
        }

        void draw() {
            tft.fillRect(x, y, BAR_WIDTH, BAR_HEIGHT, TFT_WHITE);
        }
    };

    Ball ball;
    Bar leftBar;
    Bar rightBar;

public:
    Pong() : ball(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 2, 2), leftBar(10, SCREEN_HEIGHT / 2 - BAR_HEIGHT / 2), rightBar(SCREEN_WIDTH - 20, SCREEN_HEIGHT / 2 - BAR_HEIGHT / 2) {}

    void setup() {
        tft.begin();
        tft.setRotation(1); // Ajuste a rotação do display conforme necessário
        tft.fillScreen(TFT_BLACK);
    }

    void loop() {
        tft.fillScreen(TFT_BLACK);

        // Movendo e desenhando a bola e as barras
        ball.move();
        ball.draw();
        leftBar.draw();
        rightBar.draw();

        delay(30);
    }
};

// Função principal
void setup() {
    Pong pong;
    pong.setup();

    // Loop principal do jogo
    while (true) {
        pong.loop();
    }
}

void loop() {
    // Não há nada para fazer aqui, todo o código está no setup()
}
