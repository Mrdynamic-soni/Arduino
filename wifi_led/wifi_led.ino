#include<ESP8266WiFi.h>
#define ssid "Redmi 7"
#define PASS "88888888"

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
 String request=client.readStringUntil('\r');
  if(request.indexOf("/LED-ON")!=-1)
  {
    digitalWrite(LED_BUILTIN,0);
  }
  if(request.indexOf("/LED-OFF")!=-1)
  {
    digitalWrite(LED_BUILTIN,1);
  }
  client.print("<html><head><title>IOT</title></head><body><a href='LED-ON'><button>ON</button></a><a href='LED-OFF'><button>OFF</button></a></body></html>");
  
  
}
