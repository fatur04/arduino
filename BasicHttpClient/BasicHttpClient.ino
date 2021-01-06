#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

WiFiClient client;
String request_string;

const char* ssid = "realme 5 Pro";
const char* password = "sembarang"; 
const char* host = "localhost";

void setup() {

    Serial.begin(9600);
    WiFi.begin(ssid, password);
    while ((!(WiFi.status() == WL_CONNECTED))){
      delay(300);
    }
}

void loop() {
    // wait for WiFi connection
    if(WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        http.begin("http://192.168.43.194/nodemcu_database/koneksi_database.php");  //HTTP
        int httpCode = http.GET();
        if(httpCode > 0) {
          //Serial.println("[HTTP] GET... code: %d\n", httpCode);
          String payload = http.getString();
          Serial.println(payload);
        } else {
          Serial.println("failed, error: ");
        }
        http.end();
    }
    delay(5000);
}
