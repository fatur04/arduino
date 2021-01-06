#include <ESP8266WiFi.h>
#include "DHT.h"

#define DHTPIN 2  // NodeMCU Pin D4 (watch the pinout image) to connect to data pin from DHT
#define DHTTYPE DHT22
int led_telu = 14; //kita menggunakan pin 5 untuk led merah indikator awas
int led_papat = 12;

const char* ssid = "UNDIP-OPEN"; // your WiFi SSID
const char* password = "sembarang"; //your WiFi password

const int httpPort = 80;

const char* host = "api.thingspeak.com"; // ThingSpeak domain 

String ApiKey = "322GW4JCHQQEBBBC"; // your API Key for temperature and humidity from ThingSpeak
String path = "/update?key=" + ApiKey + "&field1=";  
String path2 = "&field2=";


DHT dht(DHTPIN, DHTTYPE);

void setup() {
  pinMode(led_telu, OUTPUT); //mengatur led sebagai OUTPUT
  pinMode(led_papat, OUTPUT);
  dht.begin();
  Serial.begin(9600);
  delay(10);
 
  
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

}

void loop() {

  // reading data from DHT sensor
  float kelembapan = dht.readHumidity();
  float suhu = dht.readTemperature();
  if ( suhu > 30.00){
  digitalWrite(led_telu, HIGH);
  digitalWrite(led_papat, LOW);
  }
  else if ( suhu < 30.00){
  digitalWrite(led_telu, LOW);
  digitalWrite(led_papat, HIGH);
  }
  Serial.print("Kelembaban: ");
  Serial.print(kelembapan);
  Serial.print("Suhu: ");
  Serial.println(suhu);
  delay(500);
  
 
  // we need this delay for the DHT sensor
  delay(500);

  WiFiClient client;

  // connecting to ThingSpeak
  if (!client.connect(host, httpPort)) return;

  // Sending data do ThinkSpeak
  client.print(String("GET ") + path + suhu + path2 + kelembapan + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: keep-alive\r\n\r\n");       
                     
  client.stop(); // Closing the connection with ThingSpeak
}
