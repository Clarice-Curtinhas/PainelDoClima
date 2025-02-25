#include <ESP8266WiFi.h>
#include <PubSubClient.h>

typedef struct {
  float temp, umidade, qualidade;
} tDados;

const char* ssid = "Galaxy A20s3459";
const char* password = "jrhp4729";
//Free mqtt server for testing
const char* mqtt_server = "broker.mqtt-dashboard.com";
//Local MQTT server - Tested using mosquitto mqtt for windows and linux
//const char* mqtt_server = "192.168.137.1";


WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

void setup_wifi() {

  delay(10);
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
      Serial.println(" try again in 1 seconds");
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
 //Serial.println(d.temp);
 d.umidade = atof(umidade);
 //Serial.println(d.umidade);
 d.qualidade = atof(qualidade);
 //Serial.println(d.qualidade);
 return d;
}

void callback(char* topic, byte* payload, unsigned int length) {
  //Serial.print("Mensagem recebida no tópico: ");
  //Serial.println(topic);

  // Converte os dados recebidos para String
  char message[100] = "";

  tDados dadosUfes, dadosVix;
  for (int i = 0; i < length; i++) {
    message[i] += (char)payload[i];
  }

  if (strcmp(topic, "PainelDoClima/InfoUfes") == 0) {
    dadosUfes = leDados(dadosUfes, message);
    Serial.println("Dados Ufes");
    Serial.println(dadosUfes.temp);
    Serial.println(dadosUfes.umidade);
    Serial.println(dadosUfes.qualidade);
  } else if (strcmp(topic, "PainelDoClima/InfoVix") == 0) {
    dadosVix = leDados(dadosVix, message);
    Serial.println("Dados Vix");
    Serial.println(dadosVix.temp);
    Serial.println(dadosVix.umidade);
    Serial.println(dadosVix.qualidade);
  } else {
    Serial.println("Tópico desconhecido");
  }

  //Serial.print("Mensagem: ");
  //Serial.println(message);
  
}

void setup() {
  Serial.begin(9600);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  
  }
