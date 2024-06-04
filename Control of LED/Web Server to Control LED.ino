#include <WiFi.h>
#include <WebServer.h>

// Replace with your network credentials
const char* ssid = "Alpha"; 
const char* password = "Alpha015";

// Create a web server object that listens for HTTP request on port 80
WebServer server(80);

// Variable to store the current state of the LED
bool ledState = LOW;

// Assign GPIO 2 to the LED
const int ledPin = 2;

void handleRoot() {
  float temp = 000;
  String html = "<html>\
                  <head>\
                    <meta name='viewport' content='width=device-width, initial-scale=1'>\
                    <style>\
                      body { text-align: center; font-family: 'Arial'; }\
                      .button { padding: 16px 40px; font-size: 30px; }\
                      #on {background-color : green}\
                      #off {background-color : red}\
                    </style>\
                  </head>\
                  <body>\
                    <h1>Omakar Home</h1>\
                    <p>LED State: " + String(ledState ? "ON" : "OFF") + "</p>\
                    <p ><a href='/LED/on'><button class='button' id='on'>ON</button></a></p>\
                    <p  ><a href='/LED/off'><button class='button' id='off'>OFF</button></a></p>\
                    <p>Temperature " + String(temp) + "</p>\
                  </body>\
                </html>";
  server.send(200, "text/html", html);
}

void handleLEDOn() {
  digitalWrite(ledPin, HIGH);
  ledState = HIGH;
  handleRoot();
}

void handleLEDOff() {
  digitalWrite(ledPin, LOW);
  ledState = LOW;
  handleRoot();
}

void setup() {
  Serial.begin(115200);
  
  // Initialize the LED pin as an output
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  // Connect to Wi-Fi network
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  server.on("/", handleRoot);
  server.on("/LED/on", handleLEDOn);
  server.on("/LED/off", handleLEDOff);
  server.begin();
}

void loop() {
  server.handleClient();
}
