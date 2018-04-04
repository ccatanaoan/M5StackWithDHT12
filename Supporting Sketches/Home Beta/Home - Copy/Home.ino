#include <WiFi.h>
#include <MQTT.h>
#include <M5Stack.h>

const char ssid[] = "RiseAboveThisHome";
const char pass[] = "SteelReserve";

WiFiClient net;
MQTTClient client;

unsigned long lastMillis = 0;

void connect() {
  Serial.print("Connecting to WiFi...");
  M5.Lcd.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    M5.Lcd.print(".");
    delay(1000);
  }

  Serial.println("\Connected to WiFi");
  M5.Lcd.println("Connected to WiFi");

  String clientId = "Cloyd-";
  clientId += String(random(0xffff), HEX);

  Serial.print("\nConnecting to MQTT...");
  M5.Lcd.print("Connecting to MQTT...");
  while (!client.connect(clientId.c_str(), "vynckfaq", "KHSV1Q1qSUUY")) {
    Serial.print(".");
    M5.Lcd.print(".");
    delay(1000);
  }

  Serial.println("\Connected to MQTT");
  M5.Lcd.println("Connected to MQTT");

  client.subscribe("TempHumid");
  client.subscribe("MQ7");
  // client.unsubscribe("/hello");
}

void messageReceived(String &topic, String &payload) {
  M5.Lcd.fillScreen(TFT_BLACK);
  M5.Lcd.setTextColor(TFT_WHITE, TFT_BLACK);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(0,0);
  Serial.println("Incoming: " + topic + " - " + payload);
  M5.Lcd.println("Incoming: " + topic + " - " + payload);

}

void setup() {
  Serial.begin(115200);
  // Setup the TFT display
  M5.begin();
  M5.Lcd.setTextSize(2);
  
  WiFi.begin(ssid, pass);

  // Note: Local domain names (e.g. "Computer.local" on OSX) are not supported by Arduino.
  // You need to set the IP address directly.
  client.begin("m14.cloudmqtt.com", 11816, net);
  client.onMessage(messageReceived);

  connect();
}

void loop() {
  client.loop();
  delay(10);  // <- fixes some issues with WiFi stability
  M5.update();

  if (!client.connected()) {
    connect();
  }

  // publish a message roughly every second.
  if (millis() - lastMillis > 1000) {
    lastMillis = millis();
    //client.publish("/hello", "world");
  }
}
