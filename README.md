# IoT Enabled Web-Based System for Solar Power Generation and Load Monitoring with Remote Control

<div align="center">

## Smart Solar Energy Monitoring and Remote Control System Using ESP32

Real-Time Monitoring | Web Dashboard | Blynk IoT | Remote Relay Control

</div>

---

# Overview

This project is an IoT-based solar energy monitoring and remote control system developed using the ESP32 microcontroller. The system continuously monitors important electrical parameters such as voltage, current, power, and energy consumption in real time.

The monitored data is transmitted over WiFi and displayed on both a live web dashboard and the Blynk IoT platform. The project also supports remote relay control, allowing users to switch electrical loads ON or OFF through the internet.

---

# Features

- Real-time Voltage Monitoring
- Real-time Current Monitoring
- Power Calculation
- Energy Consumption Monitoring
- Web-Based Live Dashboard
- Blynk IoT Integration
- Remote Relay Control
- WebSocket Live Data Updates
- ESP32 WiFi Connectivity
- Lightweight Responsive Interface

---

# Hardware Components

| Component | Description |
|---|---|
| ESP32 Development Board | Main controller with WiFi |
| ACS712 Current Sensor | Current measurement |
| Voltage Sensor Module | Voltage measurement |
| Relay Module | Remote load switching |
| Solar Panel / DC Supply | Power source |
| DC Load | Connected electrical load |
| Connecting Wires | Circuit connections |
| Power Supply | ESP32 powering |

---

# Software and Technologies

- Arduino IDE
- ESP32 Board Package
- Blynk IoT Platform
- HTML
- CSS
- JavaScript
- WebSocket Communication

---

# Required Libraries

Install the following libraries from Arduino IDE Library Manager:

- WiFi
- Blynk
- WebServer
- WebSocketsServer

---

# Pin Configuration

| Device | ESP32 Pin |
|---|---|
| ACS712 Current Sensor | GPIO34 |
| Voltage Sensor | GPIO35 |
| Relay Module | GPIO5 |

---

# Circuit Connections

## ACS712 Current Sensor

| ACS712 Pin | ESP32 Connection |
|---|---|
| VCC | 5V |
| GND | GND |
| OUT | GPIO34 |

### Current Flow Connection

```text
Power Source → Load → ACS712 → GND
```

---

## Voltage Sensor Module

| Voltage Sensor Pin | ESP32 Connection |
|---|---|
| VCC | 5V |
| GND | GND |
| OUT | GPIO35 |

---

## Relay Module

| Relay Pin | ESP32 Connection |
|---|---|
| VCC | 5V |
| GND | GND |
| IN | GPIO5 |

---

# Blynk Virtual Pins

| Virtual Pin | Function |
|---|---|
| V0 | Voltage |
| V1 | Current |
| V2 | Power |
| V3 | Relay Control |

---

# Parameters Monitored

- Voltage in Volts
- Current in mA
- Power in Watts
- Energy Consumption in Wh

---

# Working Principle

- Voltage and current sensors collect electrical parameters from the connected load.
- ESP32 processes the sensor readings and calculates power and energy values.
- Data is transmitted over WiFi in real time.
- Values are displayed on:
  - Web Dashboard
  - Blynk IoT Application
- Relay switching can be controlled remotely through:
  - Web Interface
  - Blynk Mobile App

---

# Web Dashboard Features

- Live Voltage Display
- Live Current Display
- Live Power Monitoring
- Energy Consumption Monitoring
- Relay ON/OFF Switching
- Real-Time Data Updates Using WebSocket

---

# Setup Instructions

## Step 1

Install Arduino IDE and ESP32 Board Package.

## Step 2

Install all required libraries.

## Step 3

Update WiFi and Blynk credentials inside the code.

```cpp
char ssid[] = "YOUR_WIFI_NAME";
char pass[] = "YOUR_WIFI_PASSWORD";

#define BLYNK_AUTH_TOKEN "YOUR_BLYNK_AUTH_TOKEN"
```

## Step 4

Select:

- ESP32 Development Board
- Correct COM Port

Then upload the code.

## Step 5

Open Serial Monitor and note the ESP32 IP address.

Example:

```text
http://192.168.x.x
```

Open the IP address in a browser to access the live dashboard.

---

# Project Structure

```text
├── main_code.ino
├── README.md
├── images
│   └── dashboard.png
```

---

# Future Improvements

- Cloud Database Integration
- Data Logging System
- Battery Monitoring
- PWM-Based Smart Load Control
- Automatic Solar Tracking
- Mobile App Enhancement
- AI-Based Energy Optimization

---

# Applications

- Solar Energy Monitoring
- Smart Energy Management
- Remote Load Control
- IoT-Based Automation
- Educational Projects
- Renewable Energy Research

---

# Author

Swamya Ranjan

---

# License

This project is developed for educational, research, and learning purposes.
