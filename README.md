# Smart Cooking Pot Thermometer

An Internet of Things project from my Computer Science degree at the University of Kent, awarded a First. It's a Wi-Fi thermometer that sits in a cooking pot, sends the water temperature to a phone dashboard, tells you when the water is boiling and runs a cooking timer you set from the app.

## Hardware

- Seeed Studio XIAO ESP32C3
- DS18B20 waterproof temperature probe (OneWire), rated -55 to 125°C so it can sit in boiling water

## How it works

- Reads the probe every second and sends Celsius and Fahrenheit readings to a Blynk dashboard (virtual pins V0 and V1)
- Logs a `boiling_water` event in Blynk once the temperature goes over 100°C, which can trigger a phone notification
- A slider in the app sets a countdown timer in minutes (V2). When it reaches zero the board logs a `timer_done` event

## Setup

1. Install the Arduino IDE with ESP32 board support, plus the Blynk, OneWire and DallasTemperature libraries.
2. Create a Blynk template with datastreams V0 (°C), V1 (°F) and V2 (timer, in minutes), and events called `boiling_water` and `timer_done`.
3. Put your own Blynk template ID, auth token and Wi-Fi details at the top of `SmartThermometer.ino`, then upload it to the board.
