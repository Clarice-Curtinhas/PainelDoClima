#include <Adafruit_NeoPixel.h>
#include <time.h>
#include "constantes.h"

Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(NUMPIXELS, PIN1, NEO_GRB + NEO_KHZ800);   // Cria um objeto da biblioteca NeoPixel
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(NUMPIXELS, PIN2, NEO_GRB + NEO_KHZ800);   // Cria um objeto da biblioteca NeoPixel
Adafruit_NeoPixel strip3 = Adafruit_NeoPixel(NUMPIXELS, PIN3, NEO_GRB + NEO_KHZ800);   // Cria um objeto da biblioteca NeoPixel
Adafruit_NeoPixel strip4 = Adafruit_NeoPixel(NUMPIXELS, PIN4, NEO_GRB + NEO_KHZ800);   // Cria um objeto da biblioteca NeoPixel
Adafruit_NeoPixel strip5 = Adafruit_NeoPixel(NUMPIXELS, PIN5, NEO_GRB + NEO_KHZ800);   // Cria um objeto da biblioteca NeoPixel
Adafruit_NeoPixel strip6 = Adafruit_NeoPixel(NUMPIXELS, PIN6, NEO_GRB + NEO_KHZ800);   // Cria um objeto da biblioteca NeoPixel
Adafruit_NeoPixel strip7 = Adafruit_NeoPixel(NUMPIXELS, PIN7, NEO_GRB + NEO_KHZ800);   // Cria um objeto da biblioteca NeoPixel
Adafruit_NeoPixel strip8 = Adafruit_NeoPixel(NUMPIXELS, PIN8, NEO_GRB + NEO_KHZ800);   // Cria um objeto da biblioteca NeoPixel
Adafruit_NeoPixel strip9 = Adafruit_NeoPixel(NUMPIXELS, PIN9, NEO_GRB + NEO_KHZ800);   // Cria um objeto da biblioteca NeoPixel
Adafruit_NeoPixel strip10 = Adafruit_NeoPixel(NUMPIXELS, PIN10, NEO_GRB + NEO_KHZ800); // Cria um objeto da biblioteca NeoPixel

int cor[3];
int backgroundColor[3];
int analisePorcent = MENOR;

int fita = 1;

// apagar, caso o codigo dê certo
float tempAtual; //Receber do mqtt
float umidadeAtual; //Receber do mqtt
float qualidadeAtual; //Receber do mqtt

char opcao = TEMPERATURA;

//Variáveis MQTT
typedef struct {
  float temp, umidade, qualidade;
} tDados;

tDados dadosUfes, dadosSPaulo, dadosBrasilia;

float dadoAtual = 25.0;
float dadoExt = 15.0;
float dadoExt2 = 40.0;