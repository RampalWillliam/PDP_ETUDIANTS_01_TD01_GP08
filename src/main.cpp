#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

// Define the pins that we will use
#define SENSOR 33
#define LED 26
#define DHTPIN 14 
#define DHTTYPE    DHT11
#define uS_TO_S_FACTOR 1000000  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  5

DHT_Unified dht(DHTPIN, DHTTYPE);

uint32_t delayMS;

void setup() {
Serial.begin(9600);
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  Serial.println("Setup ESP32 to sleep for every " + String(TIME_TO_SLEEP) +
  " Seconds");
  // Initialize device.
  dht.begin();
  // Print temperature sensor details.
  sensor_t sensor;
  // Set delay between sensor readings based on sensor details.
  pinMode(LED, OUTPUT);

  // Get temperature event and print its value.
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
  }
  else {
    Serial.print(F("Temperature: "));
    Serial.print(event.temperature);
    Serial.println(F("°C"));
  }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
  }
  else {
    Serial.print(F("Humidity: "));
    Serial.print(event.relative_humidity);
    Serial.println(F("%"));
  }

  Serial.println("Going to sleep now");
  Serial.flush(); 
  esp_deep_sleep_start();
}

void loop() {
  
}