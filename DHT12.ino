#include <M5Stack.h>
#include "utility/DHT12.h"
#include <Wire.h>     //The DHT12 uses I2C comunication.

DHT12 dht12;          //Preset scale CELSIUS and ID 0x5c.

int counter = 0;
float humidity = 0;
float fahrenheit = 0;

void setup() {
  M5.begin();
  // Set the wakeup button
  M5.setWakeupButton(BUTTON_A_PIN);

  M5.Lcd.fillScreen(TFT_BLUE);
  M5.Lcd.setTextColor(TFT_WHITE, TFT_BLUE);
  M5.Lcd.setTextSize(3);

  Wire.begin();
}

void loop() {
  if (M5.BtnA.wasPressed()) {
    M5.powerOFF();
  }
  M5.update();

  humidity = dht12.readHumidity() + 23;
  fahrenheit = dht12.readTemperature(FAHRENHEIT);

  Serial.print("Temp : ");
  M5.Lcd.print("Temp : ");
  Serial.print(fahrenheit);
  M5.Lcd.print(fahrenheit);
  Serial.println(" F");
  M5.Lcd.println(" F");

  Serial.print("Humid: ");
  M5.Lcd.print("Humid: ");
  Serial.print(humidity);
  M5.Lcd.print(humidity);
  Serial.println(" %");
  M5.Lcd.println(" %");

  counter += 2;

  delay(5000);

  if (counter >= 10) {
    counter = 0;
    M5.Lcd.fillScreen(TFT_BLUE);
    M5.Lcd.setTextColor(TFT_WHITE, TFT_BLUE);
    M5.Lcd.setTextSize(3);
    M5.Lcd.setCursor(0, 0);
  }
}
