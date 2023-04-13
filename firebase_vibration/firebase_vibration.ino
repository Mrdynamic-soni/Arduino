#include <FirebaseESP8266.h>
#include <ESP8266WiFi.h>

// Replace with your network credentials
const char* ssid = "Redmi 7";
const char* password = "88888888";

// Replace with your Firebase project ID and authentication information
#define FIREBASE_HOST "escort-dash.firebaseio.com"
#define FIREBASE_AUTH "gOWtNCT5mpz0mKE3eNBywRFLKyK77av6C882SsEK"


// Initialize Firebase library
FirebaseData firebaseData;

// Replace with your database path
#define DATABASE_PATH "/vibration"

#define vib_pin D0

void setup() {
  Serial.begin(9600);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected to Wi-Fi, IP address: ");
  Serial.println(WiFi.localIP());

  // Initialize Firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
   pinMode(vib_pin,INPUT);
}

void loop() {
  int vibration = vib_init();
  Serial.print("Vibration ");
  Serial.println(vibration);

  // Send temperature reading to Firebase
  Firebase.pushInt(firebaseData,"/vibration", vibration);
  
  // Wait 5 seconds before taking the next temperature reading
  delay(5000);
  Serial.println("Data Sent");
}

long vib_init(){
  long vibration = pulseIn(vib_pin,HIGH); 
  return vibration;
}
