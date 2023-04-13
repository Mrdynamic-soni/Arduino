#include <OneWire.h>
#include <DallasTemperature.h>


#define DS18B20 4

OneWire ourWire(DS18B20);
DallasTemperature sensor(&ourWire);

void setup()
{
   Serial.begin(9600); 
   delay(1000);
   sensor.begin();
 
}

void loop()
{
   sensor.requestTemperatures();
   Serial.print(sensor.getTempCByIndex(0));
   Serial.println("°C");
  
   delay(1000);
}
