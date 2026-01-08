#include <Arduino.h>
#include "MPUController.h"
#include "RTCController.h"
#include <ArduinoJson.h>

/**
 * Membuat sebuah variabel yang akan menyimpan data
 */
JsonDocument sharedDataBuffer;
// Untuk mengatasi permasalahan data 
SemaphoreHandle_t dataMutex;

MPUController gyroSensor;
MPUController accelSensor;
RTCController RTCDateSensor;
RTCController RTCTimeSensor;

void vTaskSensor(void* pvParameter);
void vCommTask(void* pvParameter);

void setup() {
  Serial.begin(9600);
  if(!gyroSensor.begin(0x69)){
    Serial.println("MPU6050 not connected!");
    delay(1000);
  }
  if(!accelSensor.begin(0x69)){
    Serial.println("MPU6050 not connected!");
    delay(1000);
  }

  RTCDateSensor.begin();
  RTCTimeSensor.begin();
  dataMutex = xSemaphoreCreateMutex();
  xTaskCreatePinnedToCore(vTaskSensor,"TASK Sensor",4186,NULL,5,NULL,1);
  xTaskCreatePinnedToCore(vCommTask,"Communication Sensor",2048,NULL,5,NULL,1);
}

void vTaskSensor(void* pvParameter)
{
  JsonDocument doc;
  for(;;){
    if(xSemaphoreTake(dataMutex,portMAX_DELAY))
    {
      doc.clear();
      accelSensor.getAccel(doc);
      sharedDataBuffer["Accel Sensor"] = doc;
      doc.clear();
      gyroSensor.getGyro(doc);
      sharedDataBuffer["Gyro Sensor"] = doc;
      doc.clear();
      RTCDateSensor.showDate(doc);
      sharedDataBuffer["RTC DATE Sensor"] = doc;
      doc.clear();
      RTCTimeSensor.showTime(doc);
      sharedDataBuffer["RTC TIME Sensor"] = doc;
      doc.clear();
      Serial.println("[SENSOR TASK] Updating data..");
      xSemaphoreGive(dataMutex);
    }
    
    vTaskDelay(pdMS_TO_TICKS(1));
  }
}

void vCommTask(void* pvParameter)
{
  for(;;){
    if(xSemaphoreTake(dataMutex,portMAX_DELAY))
    {
      serializeJson(sharedDataBuffer,Serial);
      Serial.println("[COMMUNICATION TASK] Sending data..");
      xSemaphoreGive(dataMutex);
    }
    
    vTaskDelay(pdMS_TO_TICKS(200));
  }
}


void loop() {
  // put your main code here, to run repeatedly:
}
