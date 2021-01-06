#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#include "DHT.h"
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
#define DHTPIN D7  
DHT dht(DHTPIN, DHTTYPE);

char auth[] = " EoEyxL6StaVeTWtuMiexzqGanj3dmna2";
char ssid[] = "UNDIP-OPEN";
char pass[] = "sembarang";

const char* host = "api.thingspeak.com";
const int httpPort = 80;
String ApiKey = "322GW4JCHQQEBBBC"; // your API Key for temperature and humidity from ThingSpeak
String path = "/update?key=" + ApiKey + "&field1=";  
String path2 = "&field2=";

float Temp,Suhu,Lembap,TempF;


int setsuhu;

void setup()
{
  Serial.begin(9600);
  dht.begin();
  Blynk.begin(auth, ssid, pass);
  pinMode(D1, OUTPUT);
  pinMode(D0, OUTPUT);
  pinMode(V0, OUTPUT);
  pinMode(V1, OUTPUT);
   WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}
BLYNK_WRITE(V1)
{
  setsuhu = param.asInt(); // assigning incoming value from pin V1 to a variable
}

BLYNK_READ(V2)
{
  Blynk.virtualWrite(V2, Suhu);
}

BLYNK_READ(V3)
{
  Blynk.virtualWrite(V3, Lembap);
}


void loop()
{
  Blynk.run();
  Suhu = dht.readTemperature(); // Ambil nilai Suhu
  Lembap = dht.readHumidity(); // Ambil nilai Kelembaban
  
  float val = analogRead(A0);
  float mv = (val/1024.0)*3300; 
  Temp = (mv/10);
  TempF = ((Temp*9)/5) + 32;

  if ( Suhu > setsuhu ){
    digitalWrite(D1, HIGH);
    digitalWrite(D0, LOW);
  }
  else if ( Suhu < setsuhu ){
    digitalWrite(D1, LOW);
    digitalWrite(D0, HIGH);
  }
  
  Serial.print(Temp);
  Serial.print("C ");
  Serial.print("|");
  Serial.print(TempF);
  Serial.print("F ");
  Serial.print("|");
  Serial.print(Suhu);
  Serial.print("C");
  Serial.print("|");
  Serial.print(Lembap);
  Serial.println("");
  delay(100);
  WiFiClient client;

  // connecting to ThingSpeak
  if (!client.connect(host, httpPort)) return;

  // Sending data do ThinkSpeak
  client.print(String("GET ") + path + suhu + path2 + kelembapan + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: keep-alive\r\n\r\n");       
                     
  client.stop();
}
