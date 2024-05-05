#include <Arduino.h>

class JOYSTICK{
    private:
        int EIXO_X;
        int EIXO_Y;
    public:

        JOYSTICK(int EIXO_X, int EIXO_Y);

        void debug();
        int read_raw_X();
        int read_raw_Y();

        int coord_X();
        int coord_Y();

        bool cima = false;
        bool baixo = false;
        bool esquerda = false;
        bool direita = false;

        boolean is_cima();
        boolean is_baixo();
        boolean is_esquerda();
        boolean is_direita();

};