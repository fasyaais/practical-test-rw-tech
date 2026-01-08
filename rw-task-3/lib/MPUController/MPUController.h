#ifndef MPU_CONTROLLER_H
#define MPU_CONTROLLER_H

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <ArduinoJson.h>
#include <Wire.h>

class MPUController
{
private:
    uint8_t _addr;
    Adafruit_MPU6050 _mpu;
    unsigned long _intervalRead;
public:
    MPUController();
    bool begin();
    bool begin(uint8_t addr);
    void getAccel(JsonDocument &doc);
    void getGyro(JsonDocument &doc);
};


#endif