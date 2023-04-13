#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>
#include "DHT.h"
#include <ESPAsyncTCP.h>
#include "webpage.h"


// Replace with your network credentials
const char* ssid = "realme5";
const char* password = "9807474701";

#define DHTPIN 4 // Digital pin 2 (GPIO 4) connected to the DHT sensor

// Uncomment the type of sensor in use:
 #define DHTTYPE DHT11 // DHT 11
//#define DHTTYPE DHT22 // DHT 22 (AM2302)
//#define DHTTYPE DHT21 // DHT 21 (AM2301)

DHT dht(DHTPIN, DHTTYPE);

// current temperature & humidity, this will be updated in loop function
float t = 0.0;
float tf = 0.0;
float h = 0.0;

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

unsigned long previousMillis = 0; //stoe last time DHT was updated
const long interval = 1000; // Updates DHT readings every 1 seconds

//web page


void setup(){
// Serial port for debugging purposes
Serial.begin(115200);


// Connect to Wi-Fi
WiFi.begin(ssid, password);
Serial.println("Connecting to WiFi");
while (WiFi.status() != WL_CONNECTED) {
delay(1000);
Serial.println(".");
}

// Print ESP32 Local IP Address
Serial.println(WiFi.localIP());

// Route for root / web page
server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
request->send_P(200, "text/html", index_html);
});
server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
request->send_P(200, "text/plain", String(t).c_str());
});
server.on("/fahrenheit", HTTP_GET, [](AsyncWebServerRequest *request){
request->send_P(200, "text/plain", String(tf).c_str());
});
server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest *request){
request->send_P(200, "text/plain", String(h).c_str());
});

// Start server
server.begin();
dht.begin();
}

void loop(){ 
unsigned long currentMillis = millis();
if (currentMillis - previousMillis >= interval) {
// save the last time you updated the DHT values
previousMillis = currentMillis;
// Read temperature as Celsius (the default)
float currentT = dht.readTemperature();

// if temperature read failed, we don't want to change t value
if (isnan(currentT)) {
Serial.println("Failed to read from DHT sensor!");
Serial.println(currentT);
}
else {
t = currentT;
Serial.println(t);
}
// Read temperature as Fahrenheit 
float currentTf = dht.readTemperature(true);
// if temperature read failed, we don't want to change tf value
if (isnan(currentTf)) {
Serial.println("Failed to read from DHT sensor!");
}
else {
tf = currentTf;
Serial.println(tf);
}


// Read Humidity
float currentH = dht.readHumidity();
// if humidity read failed, we don't want to change h value 
if (isnan(currentH)) {
Serial.println("Failed to read from DHT sensor!");
}
else {
h = currentH;
Serial.println(h);
}
}
}
