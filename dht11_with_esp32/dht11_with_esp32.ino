#include "DHT.h"

#define DHTPIN 4
#define DHTTYPE DHT11 

DHT dht(DHTPIN,DHTTYPE);

void setup()
{
  Serial.begin(115200);

   dht.begin();
}

void loop()
{
  delay(1000);  /* Delay of amount equal to sampling period */  

  float h = dht.readHumidity();     /* Get humidity value */
  float t = dht.readTemperature(); /* Get temperatureu value */


   Serial.print(" Temperature: ");
  Serial.print(t);
  Serial.println("°C ");

   Serial.print(" Humidity: ");
  Serial.print(h);
  Serial.println("% ");
}
