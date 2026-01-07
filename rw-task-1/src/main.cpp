#include <Arduino.h>
#include "LedController.h"

#define PIN_RED 33
#define PIN_GREEN 26
#define PIN_BLUE 25

LedController ledRed(PIN_RED,LOW);
LedController ledGreen(PIN_GREEN);
LedController ledBlue(PIN_BLUE);

void setup() {
  Serial.begin(9600);
  ledRed.begin();
  ledGreen.begin();
  ledBlue.begin();
  
  ledRed.turnOn();
  ledGreen.turnOn();
  ledBlue.turnOn();
  delay(5000);

  ledRed.turnOff();
  ledGreen.turnOff();
  ledBlue.turnOff();
  delay(5000);

  ledRed.setMode(LedController::LED_BLINK,10);
  ledGreen.setMode(LedController::LED_BLINK,5);
  ledBlue.setMode(LedController::LED_BLINK,2);
}

void loop() {
  ledRed.blink();
  ledGreen.blink();
  ledBlue.blink();
}
