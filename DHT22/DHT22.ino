#include <DHT.h>
DHT dht9(9,DHT22);
void setup()
{
Serial.begin(9600);
}
void loop()
{
Serial.println("Temperature in C");
Serial.println((dht2.readTemperature(
)));
Serial.println("Humidity in C");
Serial.println((dht2.readHumidity(
))); delay(2000);
}
