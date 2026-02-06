#include <WiFi.h>                 // Includes the WiFi library to connect the ESP32 to a WiFi network
#include <WebServer.h>            // Includes the lightweight HTTP server library
#include <TFT_eSPI.h>             // Includes the TFT display library (configured via User_Setup.h)
#include <SPI.h>                  // Includes SPI communication support (used by the TFT display)

const char* ssid = "3399";   // Stores your WiFi network name (SSID)
const char* password = "mazatlan123"; // Stores your WiFi password

WebServer server(80);             // Creates a web server object that listens on port 80 (HTTP)

String wifiString = "";           // Variable to store the text received from the PC

TFT_eSPI tft = TFT_eSPI();        // Creates a TFT display object using settings from User_Setup.h

// Function that runs when a POST request is received at /setString
void handleSetString() {
  wifiString = server.arg("plain");   // Reads the raw POST body and stores it in wifiString

  Serial.print("wifiString updated: "); // Prints a label to the Serial Monitor
  Serial.println(wifiString);           // Prints the updated string value

 // --- VALIDATION LOGIC ---
  if (wifiString == "red") {           // If the received string is exactly "red"
    tft.fillScreen(TFT_RED);           // Change the entire screen background to red
    tft.setCursor(0, 0);               // Reset cursor to top-left
    tft.setTextColor(TFT_WHITE, TFT_RED); // White text on red background
    tft.setTextSize(2);                // Medium text size
    tft.println("Background set to RED"); // Display confirmation message
  } else {
    // Default behavior: show the string normally
    tft.fillScreen(TFT_BLACK);         // Clear screen to black
    tft.setCursor(0, 0);               // Move cursor to top-left
    tft.setTextColor(TFT_WHITE, TFT_BLACK); // White text on black background
    tft.setTextSize(2);                // Medium text size
    tft.println("wifiString:");        // Label
    tft.println(wifiString);           // Display the received string
  }

  server.send(200, "text/plain", "OK"); // Send HTTP 200 OK response

}

void setup() {
  Serial.begin(115200);                 // Starts the Serial Monitor at 115200 baud

  tft.init();                           // Initializes the TFT display hardware
  tft.setRotation(1);                   // Sets screen rotation (1 = landscape)
  tft.fillScreen(TFT_BLACK);            // Clears the screen to black
  tft.setTextColor(TFT_WHITE, TFT_BLACK); // Sets default text colors
  tft.setTextSize(2);                   // Sets default text size
  tft.setCursor(0, 0);                  // Positions cursor at top-left
  tft.println("Waiting for WiFi...");   // Displays a message while connecting

  WiFi.begin(ssid, password);           // Starts connecting to the WiFi network
  Serial.print("Connecting to WiFi");   // Prints connection status to Serial Monitor

  while (WiFi.status() != WL_CONNECTED) { // Loops until the ESP32 successfully connects
    delay(500);                         // Waits 500 ms between checks
    Serial.print(".");                  // Prints a dot to show progress
  }

  Serial.println("\nConnected!");       // Prints confirmation message
  Serial.print("ESP32 IP Address: ");   // Prints label for IP address
  Serial.println(WiFi.localIP());       // Prints the actual IP address

  tft.fillScreen(TFT_BLACK);            // Clears the TFT screen
  tft.setCursor(0, 0);                  // Moves cursor to top-left
  tft.println("Connected!");            // Shows connection status on TFT
  tft.println("IP:");                   // Label for IP address
  tft.println(WiFi.localIP().toString()); // Prints the IP address on the TFT

  server.on("/setString", HTTP_POST, handleSetString); // Registers the /setString POST endpoint
  server.begin();                       // Starts the web server
}

void loop() {
  server.handleClient();                // Continuously checks for incoming HTTP requests
}