

// include the library code
#include "Adafruit_LEDBackpack.h"
#include <Adafruit_GFX.h>
#include <TinyDHT.h>
#include <TinyWireM.h> // Wire/I2C library for Trinket and Gemma
#include <avr/power.h> // needed to up clock to 16 MHz on 5v Trinket

#define DHTTYPE DHT22
#define TEMPTYPE 1

// Trinket GPIO #1 would be better but LED prevents digital talk with DHT sensor
#define DHTPIN 3 // Sensor connected to GPIO #3
#define FANPIN 4
DHT dht(DHTPIN, DHTTYPE); // Define Temp Sensor

Adafruit_7segment matrix = Adafruit_7segment();

void setup() {
  if (F_CPU == 16000000)
    clock_prescale_set(clock_div_1); // 5V Trinket: run at 16 MHz
  dht.begin();                       // Initialize DHT Teperature Sensor
  matrix.begin(0x70);
  matrix.print(0xBEE5, HEX);
  matrix.writeDisplay();
  pinMode(FANPIN, OUTPUT);
  digitalWrite(FANPIN, HIGH);
  delay(3000);
  digitalWrite(FANPIN, LOW);
}

void loop() {
  int8_t h = dht.readHumidity();             // Read humidity
  int16_t t = dht.readTemperature(TEMPTYPE); // read temperature
  if (t == BAD_TEMP || h == BAD_HUM || t == 32 ||
      h == 0) { // if error conditions (see TinyDHT.h)
    matrix.print(0xEEEE, HEX);
    matrix.writeDisplay();
  } else {
    matrix.print(t);
    matrix.drawColon(true);
    matrix.writeDisplay();
    delay(15000);
    matrix.print(h);
    matrix.drawColon(false);
    matrix.writeDisplay();
    if (h > 55) {
      digitalWrite(FANPIN, HIGH);
    } else {
      digitalWrite(FANPIN, LOW);
    }
  }
  delay(15000);
}
