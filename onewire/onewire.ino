#include <OneWire.h>
#include <DallasTemperature.h>

#define OW_PIN  2
OneWire ds(OW_PIN);
DallasTemperature DS18B20(&ds);

void setup() 
{
  Serial.begin(9600);
  DS18B20.begin();
}

void loop() 
{
  byte i;
  byte present = 0;
  byte type_s;
  byte data[9];
  byte addr[8];
  float celsius = -2;

  delay(2000);

  DS18B20.requestTemperatures();
  celsius = DS18B20.getTempCByIndex(0);

  Serial.print("Celsius: ");
  Serial.println(celsius,DEC);
}
