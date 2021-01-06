#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>//Install these library
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

char auth[] = "REijMWcNun7ahfINfa8ju-80cs5sz7MQ";
char ssid[] = "Open-Free";
char pass[] = "sembarang";
DHT dht(2, DHT22); //d4
float temp;
float humi;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
dht.begin();
Blynk.begin(auth, ssid, pass);
}

BLYNK_READ(V3)
{
  Blynk.virtualWrite(V3, temp);
}
BLYNK_READ(V4)
{
  Blynk.virtualWrite(V4, humi);
}

void loop() {
  Blynk.run();
  temp=dht.readTemperature();
  humi=dht.readHumidity();
  // put your main code here, to run repeatedly:

  Serial.print("temp:");
  Serial.print(temp);
  Serial.print(" : ");
  Serial.print("humi:");
  Serial.print(humi);
  Serial.println("");
  delay(1000);
  if ( temp > 35 ){
    digitalWrite(D5, HIGH);
    digitalWrite(D6, LOW);
  }
  else  {
    digitalWrite(D5, LOW);
    digitalWrite(D6, HIGH);
  }
}
