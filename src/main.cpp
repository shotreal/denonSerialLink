#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoOTA.h>
#include <LittleFS.h> // Use LittleFS instead of SPIFFS
#include "credentials.h" // Include credentials file
#include "DenonAVR3805.h" // Include your DenonAVR3805 library

// Create an AsyncWebServer instance
AsyncWebServer server(80);

// Create an instance of DenonAVR3805
DenonAVR3805 avr(Serial); // Replace with actual serial port if necessary

void setup() {
  // Initialize Serial with baud rate 9600
  Serial.begin(9600);

  // Initialize Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  
  // Print IP address to Serial Monitor
  Serial.print("Connected to Wi-Fi. IP Address: ");
  Serial.println(WiFi.localIP());

  // Initialize LittleFS
  if (!LittleFS.begin()) {
    Serial.println("An error has occurred while mounting LittleFS");
    return;
  }

    // Serve HTML page
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        String html = "<!DOCTYPE html><html><head><title>Denon AVR Control</title>";
        html += "<style>body { padding: 20px; } .btn { margin: 5px; } table { width: 100%; border-collapse: collapse; } td { padding: 5px; text-align: center; } th { padding: 5px; text-align: center; }</style>";
        html += "</head><body><h1>Denon AVR Control</h1>";
        html += "<button class='btn' onclick='sendRequest(\"/poweron\")'>Power On</button>";
        html += "<button class='btn' onclick='sendRequest(\"/poweroff\")'>Power Off</button>";
        html += "<button class='btn' onclick='sendRequest(\"/volumeup\")'>Volume Up</button>";
        html += "<button class='btn' onclick='sendRequest(\"/volumedown\")'>Volume Down</button>";
        html += "<button class='btn' onclick='sendRequest(\"/mute\")'>Mute</button>";
        html += "<button class='btn' onclick='sendRequest(\"/unmute\")'>Unmute</button>";

        // Add volume buttons in a table format with three columns
        html += "<h2>Set Volume</h2>";
        html += "<table>";
        int volume = 99;
        while (volume >= 0) {
            html += "<tr>";
            for (int col = 0; col < 3; col++) {
                if (volume >= 0) {
                    html += "<td><button class='btn' onclick='sendRequest(\"/setvolume?level=" + String(volume) + "\")'>Volume " + String(volume) + "</button></td>";
                    volume -= 5;
                }
            }
            html += "</tr>";
        }
        html += "</table>";

    // Add radio station buttons
    html += "<h2>Radio Stations</h2>";
    html += "<table>";
    html += "<tr><td><button class='btn' onclick='sendRequest(\"/tune?freq=009720\")'>SWR3 Stuttgart</button></td>";
    html += "<td><button class='btn' onclick='sendRequest(\"/tune?freq=010770\")'>Hitradio antenne 1</button></td>";
    html += "<td><button class='btn' onclick='sendRequest(\"/tune?freq=009150\")'>SWR1 Baden-Württemberg</button></td></tr>";
    html += "<tr><td><button class='btn' onclick='sendRequest(\"/tune?freq=010730\")'>SWR4 Stuttgart</button></td>";
    html += "<td><button class='btn' onclick='sendRequest(\"/tune?freq=008950\")'>bigFM Stuttgart</button></td>";
    html += "<td><button class='btn' onclick='sendRequest(\"/tune?freq=010630\")'>Deutschlandfunk</button></td></tr>";
    html += "<tr><td><button class='btn' onclick='sendRequest(\"/tune?freq=010070\")'>Radio Energy Stuttgart</button></td>";
    html += "<td><button class='btn' onclick='sendRequest(\"/tune?freq=009180\")'>Dasding</button></td>";
    html += "<td><button class='btn' onclick='sendRequest(\"/tune?freq=010210\")'>Sunshine Live</button></td></tr>";
    html += "<tr><td><button class='btn' onclick='sendRequest(\"/tune?freq=010770\")'>Die neue 107.7</button></td>";
    html += "<td><button class='btn' onclick='sendRequest(\"/tune?freq=008910\")'>Deutschlandfunk Kultur</button></td>";
    html += "<td><button class='btn' onclick='sendRequest(\"/tune?freq=008800\")'>SWR2 Baden-Württemberg</button></td></tr>";
    html += "<tr><td><button class='btn' onclick='sendRequest(\"/tune?freq=009000\")'>SWR Aktuell</button></td>";
    html += "<td><button class='btn' onclick='sendRequest(\"/tune?freq=010110\")'>Radio Regenbogen</button></td>";
    html += "<td><button class='btn' onclick='sendRequest(\"/tune?freq=010610\")'>Klassik Radio</button></td></tr>";
    html += "<tr><td><button class='btn' onclick='sendRequest(\"/tune?freq=010750\")'>Radio TON Stuttgart</button></td>";
    html += "<td><button class='btn' onclick='sendRequest(\"/tune?freq=009680\")'>egoFM</button></td>";
    html += "<td><button class='btn' onclick='sendRequest(\"/tune?freq=010130\")'>antenne 1 Relax</button></td></tr>";
    html += "<tr><td><button class='btn' onclick='sendRequest(\"/tune?freq=010210\")'>Regenbogen Zwei</button></td>";
    html += "<td><button class='btn' onclick='sendRequest(\"/tune?freq=009300\")'>Schwarzwaldradio</button></td>";
    html += "<td><button class='btn' onclick='sendRequest(\"/tune?freq=010010\")'>Radio Seefunk</button></td></tr>";
    html += "<tr><td><button class='btn' onclick='sendRequest(\"/tune?freq=009920\")'>Freies Radio für Stuttgart</button></td></tr>";
    html += "</table>";

        html += "<script>function sendRequest(url) { fetch(url); }</script></body></html>";
        request->send(200, "text/html", html);
    });

  // Handle command requests
  server.on("/poweron", HTTP_GET, [](AsyncWebServerRequest *request){
    avr.powerOn();
    request->send(200, "text/plain", "Power On Command Sent");
  });

  server.on("/poweroff", HTTP_GET, [](AsyncWebServerRequest *request){
    avr.powerOff();
    request->send(200, "text/plain", "Power Off Command Sent");
  });

  server.on("/volumeup", HTTP_GET, [](AsyncWebServerRequest *request){
    avr.volumeUp();
    request->send(200, "text/plain", "Volume Up Command Sent");
  });

  server.on("/volumedown", HTTP_GET, [](AsyncWebServerRequest *request){
    avr.volumeDown();
    request->send(200, "text/plain", "Volume Down Command Sent");
  });

  server.on("/mute", HTTP_GET, [](AsyncWebServerRequest *request){
    avr.mute();
    request->send(200, "text/plain", "Mute Command Sent");
  });

  server.on("/unmute", HTTP_GET, [](AsyncWebServerRequest *request){
    avr.unmute();
    request->send(200, "text/plain", "Unmute Command Sent");
  });

  // Handle set volume requests
  server.on("/setvolume", HTTP_GET, [](AsyncWebServerRequest *request){
    if (request->hasParam("level")) {
      String level = request->getParam("level")->value();
      int volume = level.toInt();
      if (volume >= 0 && volume <= 99) {
        avr.setVolume(volume);
        request->send(200, "text/plain", "Set Volume to " + level);
      } else {
        request->send(400, "text/plain", "Invalid Volume Level");
      }
    } else {
      request->send(400, "text/plain", "Volume Level Not Specified");
    }
  });

    server.on("/tune", HTTP_GET, [](AsyncWebServerRequest *request){
        if (request->hasParam("freq")) {
            String freq = request->getParam("freq")->value();
            avr.setTunerInput();
            avr.setTunerFrequency(freq);
            request->send(200, "text/plain", "Tuned to " + freq + " MHz");
        } else {
            request->send(400, "text/plain", "Frequency not specified");
        }
    });

  // Start the server
  server.begin();

  // Initialize OTA
  ArduinoOTA.setHostname(otaHostname);
  ArduinoOTA.setPassword(otaPassword);

  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else {
      type = "filesystem";
    }
    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    switch (error) {
      case OTA_AUTH_ERROR:
        Serial.println("Auth Failed");
        break;
      case OTA_BEGIN_ERROR:
        Serial.println("Begin Failed");
        break;
      case OTA_CONNECT_ERROR:
        Serial.println("Connect Failed");
        break;
      case OTA_RECEIVE_ERROR:
        Serial.println("Receive Failed");
        break;
      case OTA_END_ERROR:
        Serial.println("End Failed");
        break;
    }
  });
  ArduinoOTA.begin();
}

void loop() {
  ArduinoOTA.handle(); // Handle OTA requests
}
