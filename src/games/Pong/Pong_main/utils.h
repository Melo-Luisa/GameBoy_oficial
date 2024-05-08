// itens totais da main 

#ifndef main_h
#define main_h

#include <Arduino.h>
#include <TFT_eSPI.h>

class main {
public:
	void principal(TFT_eSprite &d);
private:
	int square_width = 340; int square_height = 240;
};

#endif	
