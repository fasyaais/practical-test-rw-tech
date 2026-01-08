#include "RW_DHT11.h"

RW_DHT11::RW_DHT11(uint8_t pin):_pin(pin){}

void RW_DHT11::begin()
{
    pinMode(_pin,OUTPUT);
    digitalWrite(_pin,HIGH);
}

/**
 * Pada Method ini akan membaca nilai pulse
 * yang dikirim dari sensor maupun mcu
 */
bool RW_DHT11::_readRaw(uint8_t data[5]){
    /**
     * variable bits akan menyimpan nilai bit
     * yang memiliki panjang 40
     */
    uint8_t bits[40] = {0};
    uint32_t timeout;
    
    // Mengirimkan pulse ke sensor DHT
    pinMode(_pin,OUTPUT);
    digitalWrite(_pin,LOW);
    // dilakukan pull down sebesar 18ms dikarenakan
    // untuk memulai start pulse
    delay(18);
    digitalWrite(_pin,HIGH);
    delayMicroseconds(40);
    // merubah pin menjadi pull up
    pinMode(_pin,INPUT_PULLUP);
    
    /**
     * Menunggu apakah DHT11 merespon start pulse
     * dari MCU
     */
    timeout = micros();
    while (digitalRead(_pin) == HIGH){
        if(micros() - timeout > 80) return false;
    }
    /**
     * Menunggu DHT memberikan pulse HIGH 
     */
    timeout = micros();
    while (digitalRead(_pin) == LOW){
        if(micros() - timeout > 54) return false;
    }
    /**
     * Menunggu DHT Memberikan pulse LOW untuk
     * memulai pengiriman data
     */
    timeout = micros();
    while (digitalRead(_pin) == HIGH){
        if(micros() - timeout > 80) return false;
    }
    /**
     * Akan melakukan penyimpanan bit yang telah diterima
     */
    for(int i = 0; i <40;i++){
        while (digitalRead(_pin) == LOW);
        uint32_t start = micros();
        while (digitalRead(_pin) == HIGH);
        /**
         * disini merupakan logika untuk menyimpan apakah data
         * bernilai 1 atau 0.
         * Untuk nilai 1, pulse akan diberikan pull up selama 70us dan
         * untuk nilai 0, pulse akan diberikan pull up selama 24us
         */
        bits[i] = (micros() - start) > 26 ? 1:0;
    }
    /**
     * Dilakukan konveksi bit ke byte
     * for pertama untuk segmentasi atau bagian yang memiliki 5 segmentasi
     * for kedua untuk panjang dari per segmentasi
     */
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
    /**
     * Dilakukan pengecekkan checksum apakah data yang diterima
     * telah sesuai dengan cara menambahkan bagian 1 sampai 4 dan 
     * melakukan komparasi pada bagian terakhir
     */
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