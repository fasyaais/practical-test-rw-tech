#ifndef RW_DHT11_H
#define RW_DHT11_H

#include <Arduino.h>
class RW_DHT11
{
private:
    uint8_t _pin;
    uint8_t _humadity;
    uint8_t _temp;

    bool _readRaw(uint8_t data[5]);
public:
    RW_DHT11(uint8_t pin);
    bool read();
    float getHumadity();
    float getTemp();
    void begin();
};


#endif