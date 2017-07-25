
#include "DHT.h"

#define DHTPIN 2     // what pin we're connected to

// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11 
#define DHTTYPE DHT22   // DHT 22  (AM2302)

#define FANPIN 4
#define BLUE 3
DHT dht(DHTPIN, DHTTYPE);                     
void setup() {
   dht.begin();
  pinMode(FANPIN, OUTPUT);
   pinMode(BLUE, OUTPUT);
  // Set the pin high as the default state
  digitalWrite(FANPIN, HIGH); 
  delay(500);
  digitalWrite(FANPIN, LOW); 
    digitalWrite(BLUE, HIGH); 
delay(500);
  digitalWrite(BLUE, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  float t = dht.readTemperature(true);
//  t = 60;
  if ( t > 75) {
    digitalWrite(FANPIN, HIGH);   
    digitalWrite(BLUE, LOW);
  } else {
    digitalWrite(BLUE, HIGH);
    digitalWrite(FANPIN, LOW); 
  }
  delay(2000);
}
