#ifndef LED_CONTROLLER_H
#define LED_CONTROLLER_H

#include <Arduino.h>

/*
    Class untuk melakukan kontrol pada LED 
*/

class LedController
{
public:
    enum LedMode {
        LED_ON,
        LED_OFF,
        LED_BLINK
    };

    LedController(uint8_t pin,uint8_t active = HIGH);
    void begin();
    void turnOn();
    void turnOff();
    void setMode(LedMode mode, int frequency);
    void blink();

private:
    uint8_t _pin;
    uint8_t _active;
    LedMode _currentMode;
    bool _currentState;
    unsigned long _interval;
    unsigned long _previousMilis;
};

#endif