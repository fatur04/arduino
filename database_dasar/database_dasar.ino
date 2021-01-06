#include<ESP8266WiFi.h>
#include<ESP8266HTTPClient.h>

const char* ssid = "Gratis";
const char* password = "sembarang";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting...");
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  if(WiFi.status() == WL_CONNECTED){
    HTTPClient http;
    http.begin("http://192.168.1.44");
    int httpCode = http.GET();
    if(httpCode > 0){
      String payload = http.getString();
      Serial.println(payload);
    }
    http.end();
  }
  delay(5000);
}
