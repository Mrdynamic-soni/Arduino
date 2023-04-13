#include<ESP8266WiFi.h>
#define ssid "Redmi"
#define PASS "samridhi2204"

//Port of http = 80
// For creating a server by NodeMCU
WiFiServer server (80);

void setup() {
  // put your setup code here, to run once:
Serial.begin(115200); //Serial bond
Serial.println("\nConnecting to network...");
WiFi.begin(ssid,PASS);

while(WiFi.status()!=WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }
Serial.println("Connected to Network");
server.begin();
Serial.println(WiFi.localIP());
}

void loop() {
  // put your main code here, to run repeatedly:
WiFiClient client = server.available();
delay(200);
if(!client){
  return;
  }
}
