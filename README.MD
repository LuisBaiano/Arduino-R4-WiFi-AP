# Arduino WiFi Access Point & LED Control

## Overview

This project sets up an Arduino board as a WiFi access point using the **WiFiS3** library. Connected devices can send HTTP requests to turn an LED on or off. The project is useful for IoT applications and basic network control using an embedded web server.

## Features

* Creates a WiFi access point (SoftAP mode)
* Hosts a simple web server on port 80
* Provides HTTP endpoints to control an LED
* Displays real-time connection status via serial output

## Hardware Requirements

* **Arduino R4 WiFi** (or another board with WiFi support)
* LED and resistor (if using an external LED)
* USB cable for programming

## Installation

1. Install the **WiFiS3** library in the Arduino IDE.
2. Clone this repository:
   ```sh
   git clone https://github.com/luisbaiano/Arduino-R4-WiFi-AP.git
   ```
3. Open the `Arduino_Server.ino` file in the Arduino IDE.
4. Upload the sketch to your **Arduino R4 WiFi** board.
5. Open the Serial Monitor (baud rate:  **115200** ) to check the assigned IP.

## Usage

1. Connect your device (phone, PC) to the **"R4WIFI"** network (password:  **12345678** ) (you can chage it ate the code)).
2. Open a web browser and enter the device's IP address.
3. Click the links on the page to turn the LED **on** or  **off** .

## HTTP Endpoints

| Method | Endpoint | Description                |
| ------ | -------- | -------------------------- |
| GET    | `/ON`  | Turns the LED**ON**  |
| GET    | `/OFF` | Turns the LED**OFF** |

## Tags

* **Router**
* **Arduino Access Point**
* **Arduino R4WiFi as a Router**
* **WiFi Web Server**
* **IoT LED Control**
* **Embedded Systems**

## Author

GitHub: [github.com/luisbaiano](https://github.com/luisbaiano)
