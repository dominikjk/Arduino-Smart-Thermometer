# Arduino Smart Thermometer

A simple smart thermometer built using an Arduino board and temperature sensor. It reads temperature data, displays it on an LCD screen, and optionally sends it to a serial monitor or web server.

## Tech & Tools Used

- Arduino Uno
- DHT11 / DHT22 Temperature & Humidity Sensor
- LCD Display (16x2)
- Breadboard + jumper wires
- Arduino IDE (C/C++)

## 🛠️ Features

- Real-time temperature reading
- LCD screen output
- Serial monitor logging
- Optional: web integration (ESP8266 or similar)

## 🚀 Getting Started

### Hardware Setup
1. Connect the DHT sensor to digital pin 2.
2. Wire the LCD to I2C pins or digital pins depending on your display.
3. Upload the `.ino` file using Arduino IDE.

### Software Requirements
- Arduino IDE
- DHT sensor library (`DHT.h`)
- LiquidCrystal / LiquidCrystal_I2C library

```bash
Sketch > Include Library > Manage Libraries...
