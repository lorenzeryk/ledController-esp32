#include <ArduinoJson.h>
#include <FastLED.h>
#include <MQTTClient.h>
#include <WiFiClientSecure.h>

#include "secrets.h"
#include "WiFi.h"

MQTTClient client = MQTTClient(2048);
WiFiClientSecure net = WiFiClientSecure();

// Information about lighting strip
#define PIN 9
#define NUM_LIGHTS 25
CRGB leds[NUM_LIGHTS];

int colors[3];
String mode;

void connectAWS()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.println("Connecting to Wi-Fi");

  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  // Configure WiFiClientSecure to use the AWS IoT device credentials
  net.setCACert(AWS_CERT_CA);
  net.setCertificate(AWS_CERT_CRT);
  net.setPrivateKey(AWS_CERT_PRIVATE);

  // Connect to the MQTT broker on the AWS endpoint we defined earlier
  client.begin(AWS_IOT_ENDPOINT, 8883, net);

  // Create a message handler
  client.onMessage(messageHandler);

  Serial.print("Connecting to AWS IOT");

  while (!client.connect(THINGNAME)) {
    Serial.print(".");
    delay(100);
  }

  if(!client.connected()){
    Serial.println("AWS IoT Timeout!");
    return;
  }

  // Subscribe to a topic
  client.subscribe(SHADOW_GET_ACCEPTED);
  client.subscribe(SHADOW_GET_REJECTED);
  client.subscribe(SHADOW_UPDATE_ACCEPTED);
  client.subscribe(SHADOW_UPDATE_REJECTED);

  Serial.println("AWS IoT Connected!");
}

void publishMessage() {}

void getShadow() {
  client.publish(SHADOW_GET);
}

void messageHandler(String &topic, String &payload) {
  Serial.println("Message from " + topic);
  Serial.println("incoming: " + topic + " - " + payload);

  StaticJsonDocument<300> JSONDocument;

  DeserializationError error = deserializeJson(JSONDocument, payload);

  if (error) {
    Serial.println(error.f_str());
    return;
  }

  String newMode = JSONDocument["mode"];
  
  if (newMode == "Static") {
    mode = newMode;
    colors[0] = JSONDocument["color"]["red"];
    colors[1] = JSONDocument["color"]["green"];
    colors[2] = JSONDocument["color"]["blue"];
  }

  updateLights();
}

void updateLights() {
  if (mode == "Static") {
    setStaticLightColor(colors[0], colors[1], colors[2]);
  }
}

void setStaticLightColor(int r, int g, int b) {
  for (int i = 0; i < NUM_LIGHTS; i++) {
    leds[i] = CRGB(r, g, b);
    FastLED.show();
  }
}

void setup() {
  Serial.begin(9600);
  connectAWS();
  getShadow();
  FastLED.addLeds<WS2812, PIN, GRB>(leds, NUM_LIGHTS);
  FastLED.setBrightness(20);
}

void loop() {
  client.loop();
  updateLights();
}