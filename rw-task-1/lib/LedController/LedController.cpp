#include "LedController.h"

/**
 * @brief Inisiasi kelas dari LED CONTROLLER untuk melakukan kontrol pada LED 
 * @param pin Pin untuk LED yang akan dikontrol
 * @param active Active level pada led pada LOW atau HIGH, default = HIGH
 */
LedController::LedController(uint8_t pin,uint8_t active)
{
    _pin = pin;
    _active = active;
    _previousMilis = millis();
    turnOff();
}

/**
 * @brief Method begin() digunakna untuk mendaftarkan mode pin sebagai output
 */
void LedController::begin()
{
    _currentMode = LED_OFF;
    pinMode(_pin, OUTPUT);
    if(_active == LOW) digitalWrite(_pin,HIGH); // Jika active level LOW maka pin akan memberikan nilai HIGH supaya LED padam.
}

/**
 * @brief Method turnOn() digunakan untuk menyalakan LED
 */
void LedController::turnOn()
{
    _currentMode = LED_ON;
    _currentState = true;
    digitalWrite(_pin,_active);
    Serial.printf("[Led] Led pin %d is ON\n",_pin);
}
/**
 * @brief Method turnOff() digunakan untuk mematikan LED
 */
void LedController::turnOff()
{
    _currentMode = LED_OFF;
    _currentState = false;
    digitalWrite(_pin,(_active == HIGH) ? LOW : HIGH); // Dilakukan logika untuk mematikan LED.
    Serial.printf("[Led] Led pin %d is OFF\n",_pin);
}
/**
 *@brief Method setMode() digunakan untuk mengatur mode pada led dan mengatur frekuensi kedipan dari led dengan satuan Hz
 */
void LedController::setMode(LedMode mode, int frequency)
{
    _currentMode = mode;
    _currentState = (_currentMode == LED_ON) ? true : false;
    if(frequency > 0)
    {
        _interval = 500/frequency;
    }
    Serial.println(_currentMode);
}

/**
 * @brief Method blink() digunakan untuk melakukan kedipan sesuai sedangan frekuensi yang telah ditentunkan
 */
void LedController::blink()
{
    if(_currentMode != LED_BLINK)return;
    unsigned long currentMillis = millis();
    if(currentMillis - _previousMilis > _interval)
    {
        _previousMilis = currentMillis;
        _currentState = !_currentState;
        if(_currentState){
            digitalWrite(_pin,_active);
        }else {
            digitalWrite(_pin,(_active == HIGH) ? LOW : HIGH);
        }
    }
} 