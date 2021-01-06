#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
WiFiClient client;
String request_string;
const char* host = “192.168.43.194”; // ip computer agan, bisa di lihat ipv4 di CMD dengan perintah ipconfig
HTTPClient http;
void setup()
{
    WiFi.disconnect();
   WiFi.begin(“realme 5 Pro”,”sembarang″); // nama wifi ssid dan Passwordnya
    while ((!(WiFi.status() == WL_CONNECTED))){
      delay(300);
    }
    Serial.begin(9600);
pinMode(D5, INPUT);
}

void loop()
{
int sensor1 = analogRead(A0); // membaca tegangan analog A0
int sensor2 = digitalRead(D5); // membaca tegangan digital D5
    if (!client.connect(host,80)) {
      Serial.println(“Gagal Konek”);
      return;
    }
    request_string = “/esp8266/index.php?data1=”;
    request_string += sensor1;
    request_string += “&data2=”;
    request_string += sensor2;
    Serial.print(“requesting URL: “);
    Serial.println(request_string);
    client.print(String(“GET “) + request_string + “HTTP/1.1rn” + “Host: ” + host + “rn” + “Connection: closernrn”);
 
    
  }
}
