#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoOTA.h>
#include <WS2812FX.h>

// WiFi config
#define SSID ""
#define PSK ""
#define BROKER ""

// MQTT config
#define MQTT_PORT 1883
#define MQTT_DEVICE_NAME "Bar-lampe"
#define MQTT_QUEUE "Bar/fx"


// MQTT runtime
WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[100];
int value = 0;

/*********  GENERAL SETUP ********************************/

#define LED_COUNT 108
#define LED_PIN 1
WS2812FX ws2812fx = WS2812FX(LED_COUNT, LED_PIN, NEO_GRB);



/**************   MAIN *************************************************/



void setup() {
  yield();
  Serial.begin(115200);
  delay(1000);


  // Connect to WiFi network
  Serial.print("\nWiFi connecting...");
  WiFi.begin(SSID, PSK);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");
  Serial.print("Use this URL to connect: http://");
  Serial.println(WiFi.localIP());

  client.setServer(BROKER, MQTT_PORT);
  client.setCallback(mqttCallback);


}

void reconnect() {
  yield();
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(MQTT_DEVICE_NAME)) {
      Serial.println("connected");
      // subscribe to MQTT queue
      client.subscribe(MQTT_QUEUE);
    } else {
      Serial.print("mqtt connect failed, rc=");
      Serial.print(client.state());
      Serial.println(" retry in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}


void loop() {
  yield();
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}

void setColorLed (char* msgarrived){

  ws2812fx.setColor(0x000000);   //Set Color
  ws2812fx.setMode(FX_MODE_STATIC);
  ws2812fx.service();

}

void mqttCallback(const char* topic, byte* payload, unsigned int length) {

  yield();
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("]: ");
  for (int i = 0; i < length; i++)
    Serial.print((char) payload[i]);
  Serial.println();

  char* msg = (char *) payload;
  msg[length] = '\0'; // this seems necessary...

  ws2812fx.setBrightness(100);
  ws2812fx.setSpeed(200);
  ws2812fx.setColor(0x000000);   //Set Color
  ws2812fx.setMode(FX_MODE_STATIC);
  ws2812fx.service();
}







/*
ws2812fx.service();
ws2812fx.setColor(0xFFFFFF);
ws2812fx.service();
delay(1000);
ws2812fx.setColor(0x001234);
ws2812fx.service();
delay(1000);
*/
