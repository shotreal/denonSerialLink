#include <ESP8266WiFi.h>
#include <ArduinoHA.h>

// Include WiFi credentials
#ifdef __has_include
#  if __has_include("credentials.h")
#    include "credentials.h"
#  else
const char* ssid = "default_ssid";
const char* password = "default_password";
const char* mqttServer = "192.168.0.17"; // Default MQTT server IP
const int mqttPort = 1883;               // Default MQTT port
#  endif
#endif

// put function declarations here:
int myFunction(int, int);

void setup() {
  // put your setup code here, to run once:
  int result = myFunction(2, 3);
}

void loop() {
  // put your main code here, to run repeatedly:
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}