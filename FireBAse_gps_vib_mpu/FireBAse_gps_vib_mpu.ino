
#include <Adafruit_MPU6050.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
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


#define vib_pin D0

Adafruit_MPU6050 mpu;

static const int RXPin = D6, TXPin = D7;
static const uint32_t GPSBaud = 9600;
// The TinyGPS++ object
TinyGPSPlus gps;
// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);
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
   mpu.begin();
   ss.begin(GPSBaud);

}

void loop() {
    int vibration = vib_init();
    Serial.print("Vibration ");
    Serial.println(vibration);
    Firebase.pushInt(firebaseData,"/vibration", vibration);
    
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

      
//Accelerometer reading
  Serial.print("Acceleration X: ");
  Serial.print(a.acceleration.x);
  Serial.print(", Y: ");
  Serial.print(a.acceleration.y);
  Serial.print(", Z: ");
  Serial.print(a.acceleration.z);
  Serial.println(" m/s^2");
  Firebase.pushFloat(firebaseData,"/acceleration/x", a.acceleration.x);
  Firebase.pushFloat(firebaseData,"/acceleration/y", a.acceleration.y);
  Firebase.pushFloat(firebaseData,"/acceleration/z", a.acceleration.z);
  
//gyroscope reading
  Serial.print("Rotation X: ");
  Serial.print(g.gyro.x);
  Serial.print(", Y: ");
  Serial.print(g.gyro.y);
  Serial.print(", Z: ");
  Serial.print(g.gyro.z);
  Serial.println(" rad/s");
  Firebase.pushFloat(firebaseData,"/rotation/x", a.acceleration.x);
  Firebase.pushFloat(firebaseData,"/rotation/y", a.acceleration.y);
  Firebase.pushFloat(firebaseData,"/rotation/z", a.acceleration.z);

  while (ss.available() > 0)
    if (gps.encode(ss.read())){
      if (gps.location.isValid())
        {
          String locat = String(gps.location.lat(),6)+","+String(gps.location.lng(),6);
          Serial.print("location ");
          Serial.println(locat);
          Firebase.pushString(firebaseData,"/location", locat);
        }
      if (gps.date.isValid())
        {
          String today = String(gps.date.day())+"/"+String(gps.date.month())+"/"+String(gps.date.year())+" ";
          Serial.print("Date ");
          Serial.println(today);
          Firebase.pushString(firebaseData,"/date", today);
        }
      if (gps.time.isValid())
        {
          String nowTime = "";
          if (gps.time.hour() < 10) nowTime+=0;
          nowTime+=String(gps.time.hour()+5)+":";
          if (gps.time.minute() < 10) nowTime+=0;
          nowTime+=String(gps.time.minute()+30)+":";
          if (gps.time.second() < 10) nowTime+=0;
          nowTime+=String(gps.time.second());
          if (gps.time.centisecond() < 10) nowTime+=0;
          Serial.print("Time ");
          Serial.println(nowTime);
          Firebase.pushString(firebaseData,"/time", nowTime);
        }
      }
  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    while(true);
  }
  delay(1000); 
  Serial.println();
  Serial.println();
}

long vib_init(){
  long vibration = pulseIn(vib_pin,HIGH); 
  return vibration;
}


void displayInfo()
{
  Serial.print(F("Location: ")); 
  if (gps.location.isValid())
  {
    String loc = String(gps.location.lat(),6)+","+String(gps.location.lng(),6);
    Serial.print(loc);
    Firebase.pushString(firebaseData,"/location", loc);
    Serial.print(" ");
  }
  else
  {
    Serial.print(F("INVALID"));
  }
  Serial.print(F("  Date/Time: "));
  if (gps.date.isValid())
  {
    String today = String(gps.date.day())+"/"+String(gps.date.month())+"/"+String(gps.date.year())+" ";
    Serial.print(today);
    Firebase.pushString(firebaseData,"/date", today);
    Serial.print(" ");
  }
  else
  {
    Serial.print(F("INVALID"));
  }
  Serial.print(F(" "));
  if (gps.time.isValid())
  {
    String nowTime = "";
    if (gps.time.hour() < 10) nowTime+=0;
    nowTime+=String(gps.time.hour()+5)+":";
    if (gps.time.minute() < 10) nowTime+=0;
    nowTime+=String(gps.time.minute()+30)+":";
    if (gps.time.second() < 10) nowTime+=0;
    nowTime+=String(gps.time.second());
    if (gps.time.centisecond() < 10) nowTime+=0;
    Serial.print(nowTime);
    Firebase.pushString(firebaseData,"/time", nowTime);
  }
  else
  {
    Serial.print(F("INVALID"));
  }
  Serial.println();
}
