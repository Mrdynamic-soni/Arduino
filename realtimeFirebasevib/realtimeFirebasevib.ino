
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

// Set the credentials of your WiFi network
const char* ssid = "Redmi 7";
const char* password = "88888888";

// Set the URL and authentication token of your Firebase project
#define FIREBASE_HOST "escort-dash.firebaseio.com"
#define FIREBASE_AUTH "gOWtNCT5mpz0mKE3eNBywRFLKyK77av6C882SsEK"

// Initialize Firebase library
FirebaseData firebaseData;

void setup() {
  Serial.begin(9600);
  // Connect to WiFi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }

  // Initialize Firebase library
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
  // Send data to Firebase
  Firebase.setFloat(firebaseData, "/temperature", 25.0);
  Firebase.setInt(firebaseData, "/humidity", 60);
  Serial.printlnt("SEnt")

  // Wait for a few seconds before sending more data
  delay(5000);
}
