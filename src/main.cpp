#include <ESP8266WebServer.h>
#include <NewPing.h>
#include "wifi.h"
#include "RunningAverage.h"
#include "config.h"


ESP8266WebServer server(httpPort);
NewPing sonar(triggerPin, echoPin, maxDistance);
RunningAverage averageValue(10);

void handleRoot() {
  int readCount = (server.args() == 1 ? server.arg("c").toInt() : 1);
  int distance = sonar.convert_cm(sonar.ping_median(readCount));
  Serial.println("Initial distance: " + String(distance) + "cm");
  averageValue.addValue(distance);

  String result = String(averageValue.getAverage());

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
