#include "MPUController.h"

MPUController::MPUController(){
    _addr = 0x68;
    _intervalRead = 40;
}

bool MPUController::begin()
{
    return _mpu.begin(_addr);
}

bool MPUController::begin(uint8_t addr)
{
    _addr = addr;
    return _mpu.begin(addr);
}


void MPUController::getAccel(JsonDocument &doc)
{

    bool verif = true;
    unsigned long _previousMillis = millis();
    while (verif)
    {
        if(millis() - _previousMillis >= _intervalRead) verif = false;     
        sensors_event_t a,g,temp;
        _mpu.getEvent(&a, &g, &temp);
        doc["x"] = a.acceleration.x;
        doc["y"] = a.acceleration.y;
        doc["z"] = a.acceleration.z;
    }
}

void MPUController::getGyro(JsonDocument &doc)
{
    bool verif = true;
    unsigned long _previousMillis = millis();
    while (verif)
    {
        sensors_event_t a,g,temp;
        _mpu.getEvent(&a, &g, &temp);
        doc["x"] = g.gyro.x;
        doc["y"] = g.gyro.y;
        doc["z"] = g.gyro.z;
        if(millis() - _previousMillis >= _intervalRead) verif = false;
    }
}
