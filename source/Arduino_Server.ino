/**
 * @file Arduino_Server.ino
 * This code uses the WiFiS3 library to create a WiFi access point and
 * allows connected devices to turn an LED on or off via HTTP requests.
 * @author github.com/luisbaiano
 * @date 2025
 */

#include <WiFiS3.h>
/** file to put the ssid and pass of the access point */
#include "arduino_secrets.h"

/** @brief Defines the LED pin to be controlled. 
    @brief Defines the failure indicator LED pin (built-in LED).
    @brief WiFi connection status variable. */
int led = 4;
int ledvfr = LED_BUILTIN;
int status = WL_IDLE_STATUS;


/** @brief Web server on port 80. */
WiFiServer server(80);


/**
 * @brief System initial setup.
 * Initializes serial communication, configures pins, and creates a WiFi access point.
 */
void setup() {
  // Init Serial port
  Serial.begin(115200);
  while (!Serial);

  // Configures the LEDs pin as output
  pinMode(led, OUTPUT);
  pinMode(ledvfr, OUTPUT);

  // Checks if the WiFi module is available
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Failed to communicate with the WiFi module!");
    digitalWrite(ledvfr, HIGH);
    while (true);
  }

  Serial.print("Starting Access Point with SSID: ");
  Serial.println(ssid);

  // Starts the Access Point
  int status = WiFi.beginAP(SECRET_SSID, SECRET_PASS);
  if (status != WL_AP_LISTENING) {
    digitalWrite(ledvfr, HIGH);
    Serial.println("Failed to start the Access Point!");
    while (true);
  }

  // Starts the web server
  server.begin();
  Serial.println("Server started!");

  // Gets and displays the AP IP address
  IPAddress apIP = WiFi.softAPIP();
  Serial.print("Access Point started! IP Address: ");
  Serial.println(apIP);
}

/**
 * @brief Main program loop.
 * 
 * Monitors connections to the Access Point and responds to HTTP requests to control the LED.
 */
void loop() {
  // Checks for changes in connection status
  if (status != WiFi.status()) {
    status = WiFi.status();
    if (status == WL_AP_CONNECTED) {
      Serial.println("Device connected to AP");
    } else {
      Serial.println("Device disconnected from AP");
    }
  }

  // Checks if a client is connected
  WiFiClient client = server.available();
  if (client) {
    Serial.println("New client connected");
    String currentLine = "";
    
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        
        if (c == '\n') {
          if (currentLine.length() == 0) {
            // Sends HTTP response
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.print("<p style=\"font-size:7vw;\">Click <a href=\"/ON\">here</a> to turn the LED on<br></p>");
            client.print("<p style=\"font-size:7vw;\">Click <a href=\"/OFF\">here</a> to turn the LED off<br></p>");
            client.println();
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }

        // Checks HTTP requests
        if (currentLine.endsWith("GET /ON")) {
          digitalWrite(led, HIGH);
          Serial.println("LED turned on");
        }
        if (currentLine.endsWith("GET /OFF")) {
          digitalWrite(led, LOW);
          Serial.println("LED turned off");
        }
      }
    }
    // Closes the client connection
    client.stop();
    Serial.println("Client disconnected");
  }
}
