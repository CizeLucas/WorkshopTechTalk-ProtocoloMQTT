#include <WiFi.h>
#include <PubSubClient.h>

#include <Arduino.h>
#include "esp32-hal-timer.h"

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

  // WiFi
  const char *ssid = "<WIFI SSID>"; // Nome da Rede WiFi 
  const char *password = "<WIFI Password>";  // Senha da Rede Wifi

  // MQTT Configuration:
  // MQTT Broker:
    const char *mqtt_broker = "<IP do Broker>";
    const char *mqtt_username = "<Mosquitto User Username>";
    const char *mqtt_password = "<Mosquitto User Password>";
    const int mqtt_port = 1883;
  //MQTT Topics:
    const char *temperatureTopic = "esp32/temp"; // Temperatura do DHT11
    const char *humidityTopic = "esp32/humd"; // Humidade do DHT11
    const char *relay1Topic = "esp32/relay/1"; // Modulo de relé Canal 1 (liga e desliga)
    const char *relay2Topic = "esp32/relay/2"; // Modulo de relé Canal 2 (liga e desliga)
    const char *willMsgTopic = "esp32/status"; // Mensagem WILL (enviada quando o cliente se desconecta)

  // Definindo o timer
  hw_timer_t *timer = NULL;

  // Pinos de I/O Relé e Sensor DHT11
  const int relay1Pin = 18;
  const int relay2Pin = 19;
  #define dht11Pin 4

  // Variável global para lógica do código
  volatile bool isTimeToPostData = false;
  volatile int humidity = 0;
  volatile int temperature = 0;

WiFiClient espClient;
PubSubClient client(espClient);

#define DHTTYPE DHT11 

DHT dht(dht11Pin, DHTTYPE);

// Função de comtrole do relé que checa o conteúdo (payload) da mensagem e atua de acordo
void RelayControl(char *topic, byte *payload, int controlPin) {
  if(payload[0] == '0')
      digitalWrite(controlPin, HIGH);
    else if(payload[0] == '1')
      digitalWrite(controlPin, LOW);
    else
      Serial.println("ERRO: A mensagem recebida no tópico \""+ String(topic) +"\" é desconhecida.");
}

// Função callback é chamada sempre que uma nova mensagem chega em 
//   qualquer um dos tópicos em que estamos inscritos
void callback(char *topic, byte *payload, unsigned int length) {
  
    if(strcmp(topic, relay1Topic) == 0)
      RelayControl(topic, payload, relay1Pin);
    else if(strcmp(topic, relay2Topic) == 0)
      RelayControl(topic, payload, relay2Pin);

    Serial.print("Message arrived in topic: ");
    Serial.println(topic);
    Serial.print("Message:");
    for (int i = 0; i < length; i++) {
        Serial.print((char) payload[i]);
    }
    Serial.println();
    Serial.println("-----------------------");
}

// Função de callback do timer
void IRAM_ATTR SendSensorInfo() {
  isTimeToPostData = true;
}

void setup() {
  // Iniciar comunicação serial com 115200 de baud rate;
  Serial.begin(115200);

  pinMode(relay1Pin, OUTPUT);
  digitalWrite(relay1Pin, HIGH);

  pinMode(relay2Pin, OUTPUT);
  digitalWrite(relay2Pin, HIGH);

  dht.begin();

  // Conectando na rede WIFI
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.println("Connecting to WiFi..");
  }

  // Estabelecendo conexão com o Broker MQTT
  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(callback);
  while (!client.connected()) {
      String client_id = "esp32-" + String(WiFi.macAddress());
      Serial.printf("The client %s connects to the MQTT broker\n", client_id.c_str());
      if (client.connect(client_id.c_str(), mqtt_username, mqtt_password, willMsgTopic, 1, true, "offline", false)) {
          Serial.println("MQTT Broker Connected");
      } else {
          Serial.print("failed with state ");
          Serial.print(client.state());
          delay(2000);
      }
  }

  //Configura o tempo de Keep Alive para 12s
  client.setKeepAlive(12);

  // Inscrição nos tópicos dos Relés
  client.subscribe(relay1Topic, 1);
  client.subscribe(relay2Topic, 1);

  // Configurando a frequência do timer para 1Mhz
  timer = timerBegin(1000000);

  // Anexa a função SendSensorInfo no timer.
  timerAttachInterrupt(timer, &SendSensorInfo);

  // Configurando o alarme para chamar a função SendSensorInfo a cada 10 segundos (10000000 micro segundos).
  timerAlarm(timer, 10000000, true, 0);

  // Envia a mensagem para indicar que o MCU está online
  client.publish(willMsgTopic, "online", true); 
}

void loop() {
  client.loop();

  if(isTimeToPostData) {

  temperature = dht.readTemperature();
  humidity = dht.readHumidity();

    if (isnan(humidity) || isnan(temperature)) {
      Serial.println("ERRO ao ler o sensor DHT11");
    } else {
      client.publish(temperatureTopic, String(temperature).c_str(), true);
      client.publish(humidityTopic, String(humidity).c_str(), true);
    }

    isTimeToPostData = false;
  }
}
