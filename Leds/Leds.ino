#include <Adafruit_NeoPixel.h>
#include <time.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Fitas com os dados da UFES
#define PIN1 4   // Pino de dados da fita 1
#define PIN2 5   // Pino de dados da fita 2
#define PIN3 6   // Pino de dados da fita 3
#define PIN4 7   // Pino de dados da fita 4

//Divisória das fitas
#define PIN5 8   // Pino de dados da fita 5

// Fitas com os dados de Vitória
#define PIN6 9   // Pino de dados da fita 6
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
#define QLDMIN_VIX 1
#define QLDMAX_VIX 1

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

// apagar, caso o codigo dê certo
float tempAtual; //Receber do mqtt
float umidadeAtual; //Receber do mqtt
float qualidadeAtual; //Receber do mqtt

char opcao = TEMPERATURA;

//Variáveis MQTT
typedef struct {
  float temp, umidade, qualidade;
} tDados;

tDados dadosUfes, dadosVix;
float *dadoAtual = &dadosUfes.temp;
float *dadoExt = &dadosVix.temp;

const char* ssid = "PIC2-2.4G";
const char* password = "engcomp@ufes";
//Free mqtt server for testing
const char* mqtt_server = "broker.mqtt-dashboard.com";
//Local MQTT server - Tested using mosquitto mqtt for windows and linux
//const char* mqtt_server = "192.168.137.1";


WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

void setup(){
    Serial.begin(9600);

    // Inicializa o MQTT
    setup_wifi();
    client.setServer(mqtt_server, 1883);
    client.setCallback(callback);

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
    pinMode(3, INPUT_PULLUP);
    pinMode(21, INPUT_PULLUP);
    attachInterrupt(0, selecionaTemp, RISING);
    attachInterrupt(1, selecionaUmidade, RISING);
    attachInterrupt(2, selecionaQualidade, RISING);
}

void loop(){
    int i;
    // Valores fictícios para teste
    // apagar, caso o codigo dê certo
    tempAtual = 24.5;
    umidadeAtual = 75;
    qualidadeAtual = 68.7;

    //MQTT
    if (!client.connected()) {
        reconnect();
    }
    client.loop();

    for (int i = 0; i < NUMPIXELS; i++){
        defineCor(i, dadoAtual, dadoExt);
        strip1.setPixelColor(i, strip1.Color(cor[0], cor[1], cor[2]));

        defineCor(i, dadoAtual, dadoExt);
        strip2.setPixelColor(i, strip2.Color(cor[0], cor[1], cor[2]));

        defineCor(i, dadoAtual, dadoExt);
        strip3.setPixelColor(i, strip3.Color(cor[0], cor[1], cor[2]));

        defineCor(i, dadoAtual, dadoExt);
        strip4.setPixelColor(i, strip4.Color(cor[0], cor[1], cor[2]));

        defineCor(i, dadoAtual, dadoExt);
        strip5.setPixelColor(i, strip5.Color(cor[0], cor[1], cor[2]));

        defineCor(i, dadoAtual, dadoExt);
        strip6.setPixelColor(i, strip6.Color(cor[0], cor[1], cor[2]));

        defineCor(i, dadoAtual, dadoExt);
        strip7.setPixelColor(i, strip7.Color(cor[0], cor[1], cor[2]));

        defineCor(i, dadoAtual, dadoExt);
        strip8.setPixelColor(i, strip8.Color(cor[0], cor[1], cor[2]));

        defineCor(i, dadoAtual, dadoExt);
        strip9.setPixelColor(i, strip9.Color(cor[0], cor[1], cor[2]));

        defineCor(i, dadoAtual, dadoExt);
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
 * @brief função para definir a cor de cada led na matriz de fitas criado
 * 
 * @param i o índice do LED em determinada fita
 * @param dadoAtual aponta para o dado da ufes selecionado pelo botão
 * @param dadoExt aponta para o dado de Vitória selecionado pelo botão
 */
void defineCor(int i, float *dadoAtual, float *dadoExt){

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

    else if(fita <= 4) {
        if (opcao == TEMPERATURA){
            cor[0] = map(&dadoAtual, TEMPMIN_VIX, TEMPMAX_VIX, 0, 255);
            cor[1] = 0;
            cor[2] = map(&dadoAtual, TEMPMIN_VIX, TEMPMAX_VIX, 255, 0);
        }

        else if (opcao == UMIDADE){
            cor[0] = 0;
            cor[1] = map(&dadoAtual, UMDMIN, UMDMAX, 0, 255);
            cor[2] = map(&dadoAtual, UMDMIN, UMDMAX, 255, 0);
        }

        else if (opcao == QUALIDADE){
            cor[0] = map(&dadoAtual, QLDMIN_VIX, QLDMAX_VIX, 0, 255);
            cor[1] = map(&dadoAtual, QLDMIN_VIX, QLDMAX_VIX, 255, 0);
            cor[2] = 0;
        }
    } else if(fita >= 6 && fita < 10){
            if (opcao == TEMPERATURA){
            cor[0] = map(&dadoExt, TEMPMIN_VIX, TEMPMAX_VIX, 0, 255);
            cor[1] = 0;
            cor[2] = map(&dadoExt, TEMPMIN_VIX, TEMPMAX_VIX, 255, 0);
        }

        else if (opcao == UMIDADE){
            cor[0] = 0;
            cor[1] = map(&dadoExt, UMDMIN, UMDMAX, 0, 255);
            cor[2] = map(&dadoExt, UMDMIN, UMDMAX, 255, 0);
        }

        else if (opcao == QUALIDADE){
            cor[0] = map(&dadoExt, QLDMIN_VIX, QLDMAX_VIX, 0, 255);
            cor[1] = map(&dadoExt, QLDMIN_VIX, QLDMAX_VIX, 255, 0);
            cor[2] = 0;
        }
    } else if(fita == 5){
            cor[0] = 255;
            cor[1] = 255;
            cor[2] = 255;
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


//Funcoes do MQTT
void setup_wifi() {

  //delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("PainelDoClima", "hello world");
      // ... and resubscribe
      client.subscribe("PainelDoClima/InfoUfes");
      client.subscribe("PainelDoClima/InfoVix");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 1 second");
      // Wait 5 seconds before retrying
      delay(1000);
    }
  }
}

tDados leDados(tDados d, char* message){
  int i=0;
  char temp[5], umidade[5], qualidade[5];
 
 while(message[i]!=','){
  if(message[i]==','){
    temp[i] = '\0';
    break;
  }
  temp[i] = message[i];
  
  i++;
 }
 
  i++;
  int j=0;
 while(message[i]!=','){
  if(message[i]==','){
    umidade[j] = '\0';
    break;
  }
  umidade[j] = message[i];
  i++;
  j++;
 }

  i++;
  int k=0;
 while(message[i]!='\0'){
  if(message[i]=='\0'){
    qualidade[k] = '\0';
    break;
  }
  qualidade[k] = message[i];
  i++;
  k++;
 }

 d.temp = atof(temp);

 d.umidade = atof(umidade);

 d.qualidade = atof(qualidade);

 return d;
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Mensagem recebida no tópico: ");
  Serial.println(topic);

  // Converte os dados recebidos para String
  char message[100] = "";


  for (int i = 0; i < length; i++) {
    message[i] += (char)payload[i];
  }

  if (strcmp(topic, "PainelDoClima/InfoUfes") == 0) {
    dadosUfes = leDados(dadosUfes, message);
    Serial.print("Dados Ufes - Temp: ");
    Serial.println(dadosUfes.temp);
    Serial.print("Umidade: ");
    Serial.println(dadosUfes.umidade);
    Serial.print("Qualidade: ");
    Serial.println(dadosUfes.qualidade);
  } else if (strcmp(topic, "PainelDoClima/InfoVix") == 0) {
    dadosVix = leDados(dadosVix, message);
    Serial.print("Dados Vix - Temp: ");
    Serial.println(dadosVix.temp);
    Serial.print("Umidade: ");
    Serial.println(dadosVix.umidade);
    Serial.print("Qualidade: ");
    Serial.println(dadosVix.qualidade);
  } else {
    Serial.println("Tópico desconhecido");
  }

  Serial.print("Mensagem: ");
  Serial.println(message);
  
}

//comentar
void selecionaTemp(){
  opcao = TEMPERATURA;
  dadoAtual = &dadosUfes.temp;
  dadoExt = &dadosVix.temp;
}

void selecionaUmidade(){
  opcao = UMIDADE;
  dadoAtual = &dadosUfes.umidade;
  dadoExt = &dadosVix.umidade;
}

void selecionaQualidade(){
  opcao = QUALIDADE;
  dadoAtual = &dadosUfes.qualidade;
  dadoExt = &dadosVix.qualidade;
}