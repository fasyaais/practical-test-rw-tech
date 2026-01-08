#include "RTCController.h"

RTCController::RTCController(){}

void RTCController::begin(){
    if (! _rtc.begin()) {
    Serial.println("Couldn't find_ RTC");
    Serial.flush();
    while (1) delay(10);
  }
  if (! _rtc.isrunning()) {
    Serial.println("RTC is NOT running, let's set the time!");
    _rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  _now = _rtc.now();
}

void RTCController::showDate(JsonDocument &doc)
{
    unsigned long previousMillis = millis();
    char date[128];
    snprintf(date, sizeof(date), "%d/%d/%d",_now.day(),_now.month(),_now.year());
    doc["date"] = date;
    while(millis() - previousMillis <= 40);
}

void RTCController::showTime(JsonDocument &doc)
{
    unsigned long previousMillis = millis();
    char time[128];
    snprintf(time, sizeof(time), "%d:%d",_now.hour(),_now.minute());
    doc["time"] = time;
    while(millis() - previousMillis <= 40);
}

void RTCController::now()
{
    _now = _rtc.now();
}