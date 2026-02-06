#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "3399";
const char* password = "mazatlan123";

WebServer server(80);

String wifiString = "";

void handleSetString() {
  wifiString = server.arg("plain");  // Read raw POST body

  // Print to Arduino IDE Serial Monitor
  Serial.print("wifiString updated: ");
  Serial.println(wifiString);

  server.send(200, "text/plain", "OK");
}

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected!");
  Serial.print("ESP32 IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/setString", HTTP_POST, handleSetString);
  server.begin();
}

void loop() {
  server.handleClient();

  // Optional: continuously show the current value
   Serial.println(wifiString);
   delay(1000);
}