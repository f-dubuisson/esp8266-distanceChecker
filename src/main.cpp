#include <ESP8266WebServer.h>
#include <NewPing.h>
#include "wifi.h"
#include "RollingAverage.h"
#include "config.h"


ESP8266WebServer server(httpPort);
NewPing sonar(triggerPin, echoPin, maxDistance);
RollingAverage rollingAverage(10);

void handleRoot() {
  int readCount = (server.args() == 1 ? server.arg("c").toInt() : 1);
  int value = sonar.convert_cm(sonar.ping_median(readCount));
  rollingAverage.add(value);
  String result = String(rollingAverage.getAverage());

  Serial.println("Distance: " + result + "cm in " + readCount + " reads");
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

/** Fonction loop() **/
void loop() {
  server.handleClient();
  delay(100);
}
