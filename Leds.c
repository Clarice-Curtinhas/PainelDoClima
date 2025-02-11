#include <Adafruit_NeoPixel.h>
#include <time.h>

// Fitas com os dados da UFES
#define PIN1 4   // Pino de dados da fita 1
#define PIN2 5   // Pino de dados da fita 2
#define PIN3 6   // Pino de dados da fita 3

// Fitas com os dados do local 1
#define PIN4 7   // Pino de dados da fita 4
#define PIN5 8   // Pino de dados da fita 5
#define PIN6 9   // Pino de dados da fita 6

// Fitas com os dados do local 2
#define PIN7 10  // Pino de dados da fita 7
#define PIN8 11  // Pino de dados da fita 8
#define PIN9 12  // Pino de dados da fita 9

//Fita gradiente de cores (referência)
#define PIN10 13 // Pino de dados da fita 10

#define NUMPIXELS 30 // Número de LEDs no strip

#define TEMPMIN_VIX 15
#define TEMPMAX_VIX 40
#define UMDMIN 0
#define UMDMAX 100
#define QLDMIN_VIX definir
#define QLDMAX_VIX definir

#define MENOR -1
#define MAIOR 1
#define IGUAL 0

#define TEMPERATURA 't'
#define UMIDADE 'u'
#define QUALIDADE 'q'

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

float tempAtual; //Receber do mqtt
float umidadeAtual; //Receber do mqtt
float qualidadeAtual; //Receber do mqtt

char opcao = TEMPERATURA;

void setup(){
    Serial.begin(9600);

    // Inicializa o NeoPixel
    strip1.begin();
    strip2.begin();
    strip3.begin();
    strip4.begin();
    strip5.begin();
    strip6.begin();
    strip7.begin();
    strip8.begin();
    strip9.begin();
    strip10.begin();

    // Garante que todos os LEDs começam apagados
    strip1.show();
    strip2.show();#define NUMANIMACAO 5
    strip3.show();
    strip4.show();
    strip5.show();
    strip6.show();
    strip7.show();
    strip8.show();
    strip9.show();
    strip10.show();

    // Inicializa botão e indica qual função ele irá chamar
    pinMode(2, INPUT_PULLUP);
    attachInterrupt(0, stuffHapenned, RISING);
}

void loop(){
    int i;
    // Valores fictícios para teste
    tempAtual = 24.5;
    umidadeAtual = 75;
    qualidadeAtual = 68.7;

    for (int i = 0; i < NUMPIXELS; i++){
        defineCor(i, tempAtual, umidadeAtual, qualidadeAtual);
        strip1.setPixelColor(i, strip1.Color(cor[0], cor[1], cor[2]));

        defineCor(i, tempAtual, umidadeAtual, qualidadeAtual);
        strip2.setPixelColor(i, strip2.Color(cor[0], cor[1], cor[2]));

        defineCor(i, tempAtual, umidadeAtual, qualidadeAtual);
        strip3.setPixelColor(i, strip3.Color(cor[0], cor[1], cor[2]));

        defineCor(i, tempAtual, umidadeAtual, qualidadeAtual);
        strip4.setPixelColor(i, strip4.Color(cor[0], cor[1], cor[2]));

        defineCor(i, tempAtual, umidadeAtual, qualidadeAtual);
        strip5.setPixelColor(i, strip5.Color(cor[0], cor[1], cor[2]));

        defineCor(i, tempAtual, umidadeAtual, qualidadeAtual);
        strip6.setPixelColor(i, strip6.Color(cor[0], cor[1], cor[2]));

        defineCor(i, tempAtual, umidadeAtual, qualidadeAtual);
        strip7.setPixelColor(i, strip7.Color(cor[0], cor[1], cor[2]));

        defineCor(i, tempAtual, umidadeAtual, qualidadeAtual);
        strip8.setPixelColor(i, strip8.Color(cor[0], cor[1], cor[2]));

        defineCor(i, tempAtual, umidadeAtual, qualidadeAtual);
        strip9.setPixelColor(i, strip9.Color(cor[0], cor[1], cor[2]));

        defineCor(i, tempAtual, umidadeAtual, qualidadeAtual);
        strip10.setPixelColor(i, strip10.Color(cor[0], cor[1], cor[2]));

        fita = 1;
    }

    strip1.show();
    strip2.show();
    strip3.show();
    strip4.show();
    strip5.show();
    strip6.show();
    strip7.show();
    strip8.show();
    strip9.show();
    strip10.show();

    delay(50); // Aguarda 1 segundo
}

/**
 * @brief função para definir a cor de cada led na matriz de fitas criado, sendo i qual o índice do LED em determinada fita e tempAtual, umidadeAtual, qualidadeAtual para definir se ela deve ligar ou não
 * 
 * @param i 
 * @param tempAtual
 * @param umidadeAtual 
 * @param qualidadeAtual 
 */
void defineCor(int i, float tempAtual, float umidadeAtual, float qualidadeAtual){

    if (fita == 10){
        if (opcao == TEMPERATURA){
            cor[0] = map(i, 0, 19, 0, 255);
            cor[1] = 0;
            cor[2] = map(i, 0, 19, 255, 0);
        }

        else if (opcao == UMIDADE){
            cor[0] = 0;
            cor[1] = map(i, 0, 19, 0, 255);
            cor[2] = map(i, 0, 19, 255, 0);
        }

        else if (opcao == QUALIDADE){
            cor[0] = map(i, 0, 19, 0, 255);
            cor[1] = map(i, 0, 19, 255, 0);
            cor[2] = 0;
        }
    }

    else {
        if (opcao == TEMPERATURA){
            cor[0] = map(tempAtual, TEMPMIN_VIX, TEMPMAX_VIX, 0, 255);
            cor[1] = 0;
            cor[2] = map(tempAtual, TEMPMIN_VIX, TEMPMAX_VIX, 255, 0);
        }

        else if (opcao == UMIDADE){
            cor[0] = 0;
            cor[1] = map(umidadeAtual, UMDMIN, UMDMAX, 0, 255);
            cor[2] = map(umidadeAtual, UMDMIN, UMDMAX, 255, 0);
        }

        else if (opcao == QUALIDADE){
            cor[0] = map(qualidadeAtual, QLDMIN_VIX, QLDMAX_VIX, 0, 255);
            cor[1] = map(qualidadeAtual, QLDMIN_VIX, QLDMAX_VIX, 255, 0);
            cor[2] = 0;
        }
    }

    fita++;
}

/**
 * @brief função chamada quando o botão é apertado para mudar as informações exibidas no painel
 * 
 */
void stuffHapenned(){
  if(opcao == TEMPERATURA) opcao = UMIDADE;
  else if(opcao == UMIDADE) opcao = QUALIDADE;
  else if(opcao == QUALIDADE) opcao = TEMPERATURA;
}
