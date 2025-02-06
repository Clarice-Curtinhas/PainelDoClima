#include <ESP8266WiFi.h>
#include <PubSubClient.h>

typedef struct {
  float temp, umidade, qualidade;
} tDados;

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
      client.publish("projeto", "hello world");
      // ... and resubscribe
      client.subscribe("projeto/teste");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

tDados leDados(tDados d, char* message){
  int i=0;
  char temp[5], umidade, qualidade;
 
 while(message[i]!=','){
  if(message[i]==','){
    break;
  }
  temp[i] = message[i];
  i++;
 }
  Serial.print("string");
 Serial.println(temp);

 //d.temp = temp.toFloat();
 snprintf(temp, i, "%lf", d.temp);
 d.umidade = 0;
 d.qualidade = 0;

 return d;
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Mensagem recebida no tópico: ");
  Serial.println(topic);

  // Converte os dados recebidos para String
  char message[100] = "";

  tDados d;
  for (int i = 0; i < length; i++) {
    message[i] += (char)payload[i];
  }

  d = leDados(d, message);

  Serial.print("Mensagem: ");
  Serial.println(message);
  //Serial.println(d.temp);
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
