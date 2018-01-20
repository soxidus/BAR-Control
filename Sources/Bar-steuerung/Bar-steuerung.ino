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
#define MQTT_QUEUE "Bar/#"


// MQTT runtime
WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

/************* MQTT TOPICS (change these topics as you wish)  **************************/
const char* on_cmd = "ON";
const char* off_cmd = "OFF";
const char* effect = "solid";

/*********  GENERAL SETUP ********************************/

#define LED_COUNT 108
#define LED_PIN 1
WS2812FX ws2812fx = WS2812FX(LED_COUNT, LED_PIN, NEO_GRB);



/**************   MAIN *************************************************/



void setup() {
  yield();
  Serial.begin(115200);

  ws2812fx.init();
  ws2812fx.setBrightness(100);
  ws2812fx.setSpeed(200);
  ws2812fx.setColor(0x000000);   //Set Color
  ws2812fx.setMode(FX_MODE_STATIC);
  ws2812fx.start();

    delay(1000);
}

void loop() {
  ws2812fx.service();
  ws2812fx.setColor(0xFFFFFF);
  ws2812fx.service();
  delay(1000);
  ws2812fx.setColor(0x001234);
  ws2812fx.service();
  delay(1000);
}
