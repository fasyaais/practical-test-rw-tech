#include <Arduino.h>
#include <Wire.h>
#include <ArduinoJson.h>
#include "MPUController.h"
#include "RTCController.h"
#define SEND_INTERVAL 2000
#define SEND_DATA_INTERVAL 40

/**
 * Terhadap 5 inisiasi sensor rtc dan mpu
 */
RTCController rtc;
MPUController mpuGyroA;
MPUController mpuAccelA;

MPUController mpuGyroB;
MPUController mpuAccelB;

/**
 * Dikarenakan menggunakna sensor-sensor menggunakna bus yang sama maka 
 * diperlukan mutual exclusion (mutex) untuk mencegah race condition 
 * dari mengakses SDA secara bersamaan
 */
SemaphoreHandle_t busMutex;

void prepareSensor();

void vGyroATask(void* pvParameter);
void vAccelATask(void* pvParameter);
void vGyroBTask(void* pvParameter);
void vAccelBTask(void* pvParameter);
void vAccelCTask(void* pvParameter);

void vRTCDateTask(void* pvParameter);
void sendData();

void setup() {
  Serial.begin(9600);
  prepareSensor();
  // memasukkan nilai mutex ke  variable busmutex 
  busMutex = xSemaphoreCreateMutex();
  /**
   * Dilakukan Pembentukan tugas, ini menggunakn konsep dari RTOS
   * yang berjalan secara concurency,
   * 
   * Method xTaskCreatePinnedToCore digunakan untuk menyamakan core
   * dari task ke core 1.
   * 
   * xTaskCreatePinnedToCore memiliki argumen 
   * - task function
   * - task name
   * - stack size
   * - parameter
   * - prioritas
   * - task handler
   * - core
   */
  xTaskCreatePinnedToCore(vGyroATask,"Gyro Sensor A",2048,NULL,1,NULL,1);
  vTaskDelay(40);
  xTaskCreatePinnedToCore(vAccelATask,"Accel Sensor A",2048,NULL,1,NULL,1);
  vTaskDelay(40);
  xTaskCreatePinnedToCore(vGyroBTask,"Gyro Sensor A",2048,NULL,1,NULL,1);
  vTaskDelay(40);
  xTaskCreatePinnedToCore(vAccelBTask,"Accel Sensor A",2048,NULL,1,NULL,1);
  vTaskDelay(40);
  xTaskCreatePinnedToCore(vRTCDateTask,"Accel Sensor A",2048,NULL,1,NULL,1);
}


void vRTCDateTask(void* pvParameter){
  JsonDocument doc;
  TickType_t xLastWakeTime;
  const TickType_t xFrequency = pdMS_TO_TICKS(SEND_INTERVAL);
  xLastWakeTime = xTaskGetTickCount();
  
  for(;;){
    vTaskDelayUntil(&xLastWakeTime,xFrequency);
    TickType_t startTick = xTaskGetTickCount();
    if (xSemaphoreTake(busMutex,portMAX_DELAY))
    {
      TickType_t readStart = xTaskGetTickCount();
      doc["sensor_name"] = "RTC DATE";
      rtc.now();
      rtc.showDate(doc);
      doc["read_time"] = (xTaskGetTickCount() - readStart) * portTICK_PERIOD_MS;
      xSemaphoreGive(busMutex);
    }
    TickType_t sendStart = xTaskGetTickCount();
    sendData();
    doc["send_time"] = (xTaskGetTickCount() - sendStart) * portTICK_PERIOD_MS;
    doc["total_time"] = (xTaskGetTickCount() - startTick) * portTICK_PERIOD_MS;

    String output;
    serializeJson(doc,output);
    Serial.println(output);
  }
}


void vGyroATask(void* pvParameter)
{
  JsonDocument doc;
  TickType_t xLastWakeTime;
  const TickType_t xFrequency = pdMS_TO_TICKS(SEND_INTERVAL);
  xLastWakeTime = xTaskGetTickCount();
  
  for(;;){
    vTaskDelayUntil(&xLastWakeTime,xFrequency);
    TickType_t startTick = xTaskGetTickCount();
    if (xSemaphoreTake(busMutex,portMAX_DELAY))
    {
      TickType_t readStart = xTaskGetTickCount();
      doc["sensor_name"] = "Gyro A sensor";
      mpuGyroA.getGyro(doc);
      doc["read_time"] = (xTaskGetTickCount() - readStart) * portTICK_PERIOD_MS;
      xSemaphoreGive(busMutex);
    }
    TickType_t sendStart = xTaskGetTickCount();
    sendData();
    doc["send_time"] = (xTaskGetTickCount() - sendStart) * portTICK_PERIOD_MS;
    doc["total_time"] = (xTaskGetTickCount() - startTick) * portTICK_PERIOD_MS;

    String output;
    serializeJson(doc,output);
    Serial.println(output);
  }
}

void vAccelATask(void* pvParameter)
{
  JsonDocument doc;
  TickType_t xLastWakeTime;
  const TickType_t xFrequency = pdMS_TO_TICKS(SEND_INTERVAL);
  xLastWakeTime = xTaskGetTickCount();
  
  for(;;){
    vTaskDelayUntil(&xLastWakeTime,xFrequency);
    TickType_t startTick = xTaskGetTickCount();
    if (xSemaphoreTake(busMutex,portMAX_DELAY))
    {
      TickType_t readStart = xTaskGetTickCount();
      doc["sensor_name"] = "Accel A sensor";
      mpuGyroA.getGyro(doc);
      doc["read_time"] = (xTaskGetTickCount() - readStart) * portTICK_PERIOD_MS;
      xSemaphoreGive(busMutex);
    }
    TickType_t sendStart = xTaskGetTickCount();
    sendData();
    doc["send_time"] = (xTaskGetTickCount() - sendStart) * portTICK_PERIOD_MS;
    doc["total_time"] = (xTaskGetTickCount() - startTick)* portTICK_PERIOD_MS;

    String output;
    serializeJson(doc,output);
    Serial.println(output);
  }
}

void vGyroBTask(void* pvParameter)
{
  JsonDocument doc;
  TickType_t xLastWakeTime;
  const TickType_t xFrequency = pdMS_TO_TICKS(SEND_INTERVAL);
  xLastWakeTime = xTaskGetTickCount();
  
  for(;;){
    vTaskDelayUntil(&xLastWakeTime,xFrequency);
    TickType_t startTick = xTaskGetTickCount();
    if (xSemaphoreTake(busMutex,portMAX_DELAY))
    {
      TickType_t readStart = xTaskGetTickCount();
      doc["sensor_name"] = "Gyro B sensor";
      mpuGyroA.getGyro(doc);
      doc["read_time"] = (xTaskGetTickCount() - readStart) * portTICK_PERIOD_MS;
      xSemaphoreGive(busMutex);
    }
    TickType_t sendStart = xTaskGetTickCount();
    sendData();
    doc["send_time"] = (xTaskGetTickCount() - sendStart) * portTICK_PERIOD_MS;
    doc["total_time"] = (xTaskGetTickCount() - startTick)* portTICK_PERIOD_MS;

    String output;
    serializeJson(doc,output);
    Serial.println(output);
  }
}

void vAccelBTask(void* pvParameter)
{
  JsonDocument doc;
  TickType_t xLastWakeTime;
  const TickType_t xFrequency = pdMS_TO_TICKS(SEND_INTERVAL);
  xLastWakeTime = xTaskGetTickCount();
  
  for(;;){
    vTaskDelayUntil(&xLastWakeTime,xFrequency);
    TickType_t startTick = xTaskGetTickCount();
    if (xSemaphoreTake(busMutex,portMAX_DELAY))
    {
      TickType_t readStart = xTaskGetTickCount();
      doc["sensor_name"] = "Accel B sensor";
      mpuGyroA.getGyro(doc);
      doc["read_time"] = (xTaskGetTickCount() - readStart) * portTICK_PERIOD_MS;
      xSemaphoreGive(busMutex);
    }
    TickType_t sendStart = xTaskGetTickCount();
    sendData();
    doc["send_time"] = (xTaskGetTickCount() - sendStart) * portTICK_PERIOD_MS;
    doc["total_time"] = (xTaskGetTickCount() - startTick)* portTICK_PERIOD_MS;

    String output;
    serializeJson(doc,output);
    Serial.println(output);
  }
}

void vAccelCTask(void* pvParameter)
{
  JsonDocument doc;
  TickType_t xLastWakeTime;
  const TickType_t xFrequency = pdMS_TO_TICKS(SEND_INTERVAL);
  xLastWakeTime = xTaskGetTickCount();
  
  for(;;){
    vTaskDelayUntil(&xLastWakeTime,xFrequency);
    TickType_t startTick = xTaskGetTickCount();
    /**
     * Pengambilan mutex untuk memberitahu bahwasan nya task ini
     * sedang mengambil data
     */
    if (xSemaphoreTake(busMutex,portMAX_DELAY))
    {
      TickType_t readStart = xTaskGetTickCount();
      doc["sensor_name"] = "Accel C sensor";
      mpuGyroA.getGyro(doc);
      doc["read_time"] = (xTaskGetTickCount() - readStart) * portTICK_PERIOD_MS;
      /**
       * Ketika selesai mengambil data maka mutex yang diambil
       * dilepas kembali untuk digunakan oleh task lainnya.
       */
      xSemaphoreGive(busMutex);
    }
    TickType_t sendStart = xTaskGetTickCount();
    sendData();
    doc["send_time"] = (xTaskGetTickCount() - sendStart) * portTICK_PERIOD_MS;
    doc["total_time"] = (xTaskGetTickCount() - startTick)* portTICK_PERIOD_MS;

    String output;
    serializeJson(doc,output);
    Serial.println(output);
  }
}

void prepareSensor()
{
  rtc.begin();

  if (!mpuGyroA.begin(0x69)) {
    Serial.println("Failed to find MPU6050 69 chip");
    while (1) {
      delay(10);
    }
  }
  
}

/**
 * Pada fungsi send data digunakan untuk memberikan jeda sebanyak 40ms
 * sesuai dari constraint yang ditentukan
 */
void sendData()
{
  unsigned long previousMillis = millis();
  while (millis() - previousMillis <= SEND_DATA_INTERVAL){};
}

void loop() {
  // put your main code here, to run repeatedly:
}