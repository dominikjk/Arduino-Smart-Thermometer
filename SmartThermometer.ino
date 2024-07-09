#define BLYNK_TEMPLATE_ID "TMPL5SFQIga0Y"
#define BLYNK_TEMPLATE_NAME "Smart Cooking Pot Thermometer"
#define BLYNK_AUTH_TOKEN "GrWlBjYx_UQ25mhJJ4Gmy7epgT5bpdOJ"

#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define oneWireBus D8
OneWire oneWire(oneWireBus);
DallasTemperature sensors(&oneWire);

#define TIMER_DATASTREAM_PIN V2  // Assign the DataStream virtual pin

int timerDuration = 0;  // Variable to store the timer duration in seconds
int sliderValue = 0;    // Variable to track the slider value

unsigned long previousMillis = 0;  // Variable to store the previous time

char auth[] = BLYNK_AUTH_TOKEN;

//char ssid[] = "SHELL-483758_EXT";  
//char pass[] = "hkfKvfM3MQhk";  

char ssid[] = "microlab_IoT";
char pass[] = "shibboleet";
BlynkTimer timer;

void sendTimerDoneEvent() {
  Blynk.logEvent("timer_done"); // Log the 'timer_done' event
}

void sendSensor()
{
  sensors.requestTemperatures(); 
  
  Serial.print("Celsius temperature: ");
  Serial.print(sensors.getTempCByIndex(0)); 
  Serial.print(" - Fahrenheit temperature: ");
  Serial.println(sensors.getTempFByIndex(0));
  int tempC = sensors.getTempCByIndex(0);
  int tempF = sensors.getTempFByIndex(0);
  
  if (tempC > 100) {
    Blynk.logEvent("boiling_water");
  }

  Blynk.virtualWrite(V0, tempC);
  Blynk.virtualWrite(V1, tempF);
}

BLYNK_WRITE(TIMER_DATASTREAM_PIN) {
  timerDuration = param.asInt() * 60; // Convert minutes to seconds
  sliderValue = param.asInt(); // Update slider value
  if (timerDuration > 0) {
    // Start the timer
    previousMillis = millis();
  }
}

void checkTimer() {
  if (timerDuration > 0) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= 1000) {
      previousMillis = currentMillis;
      timerDuration--; // Decrement the timer duration

      Blynk.virtualWrite(TIMER_DATASTREAM_PIN, timerDuration);

      if (timerDuration == 0) {
        sendTimerDoneEvent();
      }
    }
  }
}

void setup() {
  Serial.begin(9600);
  sensors.begin();

  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, sendSensor);
  timer.setInterval(1000L, checkTimer); // Check the timer every second
}

void loop() {
  Blynk.run();
  timer.run();
}
