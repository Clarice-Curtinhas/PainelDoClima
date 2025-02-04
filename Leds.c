#include <Adafruit_NeoPixel.h>
#include <time.h>

#define PIN1 4   // Pino de dados da fita 1
#define PIN2 5   // Pino de dados da fita 2
#define PIN3 6   // Pino de dados da fita 3
#define PIN4 7   // Pino de dados da fita 4
#define PIN5 8   // Pino de dados da fita 5
#define PIN6 9   // Pino de dados da fita 6
#define PIN7 10  // Pino de dados da fita 7
#define PIN8 11  // Pino de dados da fita 8
#define PIN9 12  // Pino de dados da fita 9
#define PIN10 13 // Pino de dados da fita 10

#define NUMPIXELS 30 // Número de LEDs no strip

#define TEMPIDEAL 24.5
#define UMIDADEIDEAL 0.40
#define QUALIDADEIDEAL 1000

#define MENOR -1
#define MAIOR 1
#define IGUAL 0

#define TEMPERATURA 't'
#define UMIDADE 'u'
#define QUALIDADE 'q'

#define NUMANIMACAO 5

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

float tempAtual;
float umidadeAtual;
float qualidadeAtual;

char opcao = TEMPERATURA;

// Variáveis para a animação de onda
int waveOffset = 0;      // Deslocamento da onda
int waveAmplitude = 128; // Amplitude da onda
int waveSpeed = 20;      // Velocidade da onda
float frequencia = 0.1;  // Frequência da onda

int randomStrip, pixels = NUMANIMACAO + 5;

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
    strip2.show();
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
    int porcentagem;

    waveOffset++;

    tempAtual = 24.5;

    porcentagem = opcaoSelecionada();

    if (pixels == (NUMPIXELS + NUMANIMACAO) && analisePorcent == IGUAL){
        // Seed the random number generator with the current time
        srand(time(NULL));
        // Generate a random number between 1 and 10
        randomStrip = rand() % 10 + 1;
        pixels = 0;
    }

    for (int i = 0; i < NUMPIXELS; i++){
        defineCor(i, porcentagem);
        strip1.setPixelColor(i, strip1.Color(cor[0], cor[1], cor[2]));

        defineCor(i, porcentagem);
        strip2.setPixelColor(i, strip2.Color(cor[0], cor[1], cor[2]));

        defineCor(i, porcentagem);
        strip3.setPixelColor(i, strip3.Color(cor[0], cor[1], cor[2]));

        defineCor(i, porcentagem);
        strip4.setPixelColor(i, strip4.Color(cor[0], cor[1], cor[2]));

        defineCor(i, porcentagem);
        strip5.setPixelColor(i, strip5.Color(cor[0], cor[1], cor[2]));

        defineCor(i, porcentagem);
        strip6.setPixelColor(i, strip6.Color(cor[0], cor[1], cor[2]));

        defineCor(i, porcentagem);
        strip7.setPixelColor(i, strip7.Color(cor[0], cor[1], cor[2]));

        defineCor(i, porcentagem);
        strip8.setPixelColor(i, strip8.Color(cor[0], cor[1], cor[2]));

        defineCor(i, porcentagem);
        strip9.setPixelColor(i, strip9.Color(cor[0], cor[1], cor[2]));

        defineCor(i, porcentagem);
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

    if (analisePorcent == IGUAL){
        pixels++;
    }

    delay(50); // Aguarda 1 segundo
}

/**
 * @brief função que define qual a porcentagem de LEDs deve ser ligado de acordo com a opção que é exibida
 * PRECISA DE AJUSTES
 * 
 * @return int 
 */
int opcaoSelecionada(){
    int porcentagem;

    backgroundColor[0] = 255;
    backgroundColor[1] = 255;
    backgroundColor[2] = 255;

    if (opcao == TEMPERATURA){
        backgroundColor[1] = 0;

        porcentagem = ((tempAtual * 100) / TEMPIDEAL);
    }

    else if (opcao == UMIDADE){
        backgroundColor[0] = 0;

        porcentagem = ((umidadeAtual * 100)/ UMIDADEIDEAL);
    }

    else if (opcao == QUALIDADE){
        backgroundColor[2] = 0;

        porcentagem = ((qualidadeAtual * 100) / QUALIDADEIDEAL);
    }

    if (porcentagem < 100)
        analisePorcent = MENOR;

    else if (porcentagem > 100)
        analisePorcent = MAIOR;

    else{
        cor[0] = backgroundColor[0];
        cor[1] = backgroundColor[1];
        cor[2] = backgroundColor[2];

        analisePorcent = IGUAL;
    }

    return porcentagem;
}

/**
 * @brief função para definir a cor de cada led na matriz de fitas criado, sendo i qual o índice do LED em determinada fita e porcentagem para definir se ela deve ligar ou não
 * 
 * @param i 
 * @param porcentagem 
 */
void defineCor(int i, int porcentagem){

    if (analisePorcent == MENOR && (porcentagem / 10) <= fita){
        if (opcao == TEMPERATURA){
            cor[0] = sin((i + waveOffset + (fita / 20)) * frequencia) * 127;
            cor[1] = sin((i + waveOffset + 50 + (fita / 20)) * frequencia) * 127 + waveAmplitude;
            cor[2] = 255;
        }

        else if (opcao == UMIDADE){
            cor[0] = sin((i + waveOffset + (fita / 20)) * frequencia) * 127 + waveAmplitude;
            cor[1] = 255;
            cor[2] = sin((i + waveOffset + 100 + (fita / 20)) * frequencia) * 127 + waveAmplitude;
        }

        else if (opcao == QUALIDADE){
            cor[0] = 255;
            cor[1] = sin((i + waveOffset + 50 + (fita / 20)) * frequencia) * 127 + waveAmplitude;
            cor[2] = sin((i + waveOffset + 100 + (fita / 20)) * frequencia) * 127 + waveAmplitude;
        }
    }

    else if (analisePorcent == MAIOR && (porcentagem / 10) >= fita){
        if (opcao == TEMPERATURA){
            cor[0] = 255;
            cor[1] = sin((i + waveOffset + 50 + (fita / 20)) * frequencia) * 127 + waveAmplitude;
            cor[2] = sin((i + waveOffset + 100 + (fita / 20)) * frequencia) * 127 + waveAmplitude;
        }

        else if (opcao == UMIDADE){
            cor[0] = sin((i + waveOffset + (fita / 20)) * frequencia) * 127 + waveAmplitude;
            cor[1] = sin((i + waveOffset + 50 + (fita / 20)) * frequencia) * 127 + waveAmplitude;
            cor[2] = 255;
        }

        else if (opcao == QUALIDADE){
            cor[0] = sin((i + waveOffset + (fita / 20)) * frequencia) * 127 + waveAmplitude;
            cor[1] = 255;
            cor[2] = sin((i + waveOffset + 100 + (fita / 20)) * frequencia) * 127 + waveAmplitude;
        }
    }

    else{
        if (randomStrip == fita && (i >= pixels && i <= (pixels + 5))){
            cor[0] = 255;
            cor[1] = 255;
            cor[2] = 255;

            Serial.println(i);
        }

        else{
            cor[0] = backgroundColor[0];
            cor[1] = backgroundColor[1];
            cor[2] = backgroundColor[2];
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