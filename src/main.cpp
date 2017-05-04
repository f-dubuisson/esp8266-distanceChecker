#include <ESP8266WebServer.h>
#include <NewPing.h>
#include "wifi.h"
#include "RollingAverage.h"
#include "config.h"


ESP8266WebServer server(httpPort);
NewPing sonar(triggerPin, echoPin, maxDistance);
RollingAverage rollingAverage(10);
unsigned long lastValueRead = 0;

void handleRoot() {
  String result = String(rollingAverage.getAverage());

  Serial.println("Distance: " + result + "cm");
  server.send(200, "text/plain", result);
}

void handleNotFound() {
  String message = "File Not Found\n\n";
  server.send(404, "text/plain", message);
}

void setup() {
  Serial.begin(9600);

  setupWifi(ssid, password);

  server.on("/", handleRoot);
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  if (millis() - lastValueRead > 1000) {
    // Get last value
    int value = sonar.convert_cm(sonar.ping_median());
    rollingAverage.add(value);
    lastValueRead = millis();

    String text = "New value: ";
    text += value;
    text += "; average is now: ";
    text += rollingAverage.getAverage();
    Serial.println(text);
  }

  // Handle client requests
  server.handleClient();

  delay(100);
}
