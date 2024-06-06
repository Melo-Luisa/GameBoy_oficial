#include <TFT_eSPI.h> 
#include <SPI.h>

// Defina o tamanho da tela e as cores
#define TFT_WIDTH  320
#define TFT_HEIGHT 240
#define TEXT_COLOR TFT_WHITE
#define BACKGROUND_COLOR TFT_BLACK

// Crie uma instância do objeto TFT_eSPI
TFT_eSPI tft = TFT_eSPI();

// Crie uma instância do objeto TFT_eSprite para desenhar texto
TFT_eSprite placar = TFT_eSprite(&tft);

void setup() {
  // Inicialize o display TFT
  tft.init();
  tft.setRotation(1); // Defina a orientação do display (opcional)

  // Inicialize o objeto de sprite para texto
  placar.setColorDepth(16);
  placar.createSprite(TFT_WIDTH, TFT_HEIGHT);
  placar.fillSprite(BACKGROUND_COLOR); // Preencha o sprite com a cor de fundo
  placar.setTextDatum(MC_DATUM); // Defina o ponto de referência para o texto como o centro
}

void loop() {
  // Limpe o sprite antes de desenhar um novo texto
  placar.fillSprite(BACKGROUND_COLOR);

  // Desenhe texto no sprite
  placar.setTextColor(TEXT_COLOR);
  placar.drawString("Olá, Mundo!", TFT_WIDTH / 2, TFT_HEIGHT / 2);

  // Exiba o sprite na tela
  placar.pushSprite(0, 0);

  delay(1000); // Aguarde um segundo antes de desenhar novamente (apenas para exemplo)
}
