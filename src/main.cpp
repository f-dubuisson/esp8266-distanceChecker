#include <ESP8266WebServer.h>
#include <NewPing.h>
#include "wifi.h"
#include "config.h"

static const int RETRY_COUNT = 10;

ESP8266WebServer server(httpPort);
NewPing sonar(triggerPin, echoPin, maxDistance);

unsigned long getDistance(int readCount, int retryCount) {
	unsigned long median = 0;
	for (int i = 0; i < retryCount; i++) {
		median = sonar.ping_median(readCount);
		if (median > 0) {
			break;
		}
	}

	return sonar.convert_cm(median);
}

void handleRoot() {
	int readCount = (server.args() == 1 ? server.arg("c").toInt() : 1);
	String result = String(getDistance(readCount, RETRY_COUNT));

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
