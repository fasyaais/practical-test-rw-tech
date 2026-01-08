#include "RW_DHT11.h"

RW_DHT11::RW_DHT11(uint8_t pin):_pin(pin){}

void RW_DHT11::begin()
{
    pinMode(_pin,OUTPUT);
    digitalWrite(_pin,HIGH);
}

bool RW_DHT11::_readRaw(uint8_t data[5]){
    uint8_t bits[40] = {0};
    uint32_t timeout;
    
    pinMode(_pin,OUTPUT);
    digitalWrite(_pin,LOW);
    delay(18);
    digitalWrite(_pin,HIGH);
    delayMicroseconds(40);
    Serial.println("HELLO");
    pinMode(_pin,INPUT_PULLUP);
    
    timeout = micros();
    
    while (digitalRead(_pin) == HIGH){
        if(micros() - timeout > 80) return false;
    }

    timeout = micros();
    while (digitalRead(_pin) == LOW){
        if(micros() - timeout > 54) return false;
    }
    
    timeout = micros();
    while (digitalRead(_pin) == HIGH){
        if(micros() - timeout > 80) return false;
    }

    for(int i = 0; i <40;i++){
        while (digitalRead(_pin) == LOW);
        uint32_t start = micros();
        while (digitalRead(_pin) == HIGH);
        bits[i] = (micros() - start) > 26 ? 1:0;
    }

    for(int i = 0; i < 5; i++){
        for (int j = 0; j < 8; j++)
        {
            data[i] <<= i;
            data[i] |= bits[i*8+j];
        }
        
    }
    return true;
}

bool RW_DHT11::read(){
    uint8_t data[5] ={0};
    if(!_readRaw(data)){
        Serial.println("Failed");
        return false;
    }
    if(data[0]+ data[1] + data[3] + data[2] != data[4]){
        return false;
    }

    _humadity = data[0];
    _temp = data[2];

    return true;
}

float RW_DHT11::getHumadity()
{
    return _humadity;
}

float RW_DHT11::getTemp()
{
    return _temp;
}