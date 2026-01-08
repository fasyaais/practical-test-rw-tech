#ifndef RTC_CONTOLLER_H
#define RTC_CONTOLLER_H

#include "RTClib.h"
#include <ArduinoJson.h>

class RTCController
{
private:
    RTC_DS1307 _rtc;
    DateTime _now;
public:
    RTCController(/* args */);
    void begin();
    void now();
    void showDate(JsonDocument &doc);
    void showTime(JsonDocument &doc);
};

#endif