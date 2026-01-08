#include <Arduino.h>
#include "RW_DHT11.h"

RW_DHT11 dht(4);

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
    Serial.println("LOOP HIT");
  if(!dht.read()){
    Serial.println("FAILED");
  }
  Serial.printf("Humadity : %.2f, Temp : %.2f\n",dht.getHumadity(),dht.getTemp());
  delay(1000);
}
