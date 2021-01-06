#include <ESP8266WiFi.h>   //  ESP8266 library
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h> 
#include <WiFiClient.h> 
#include <ESP8266mDNS.h>

// Set web server port number to 80
ESP8266WebServer server(80);

const int pinLED = D5;
const int ledPin =  LED_BUILTIN;
String page = "<html><head><title>Kontrol Lampu Boss</title></head><body><a href=\"/on\"><h3> ON </h3></a><a href=\"/off\"><h3> OFF </h3></a></body></html>";

void HOMEPAGE() {
  server.send(200, "text/html", page);
    
}
void onLED(){
  digitalWrite(pinLED, HIGH);
  digitalWrite(ledPin, HIGH);
 server.send(200, "text/html", page);
}
void offLED(){
  digitalWrite(pinLED, LOW);
  digitalWrite(ledPin, LOW);
  server.send(200, "text/html", page);
}
void setup() {
  Serial.begin(115200);
  
  pinMode(pinLED, OUTPUT);
  pinMode(ledPin, OUTPUT);
  
  WiFiManager wifiManager;
  wifiManager.resetSettings();
  wifiManager.autoConnect("Fatur");
  Serial.println("Connected... Berhasil Hore...");
  if (MDNS.begin("patur")){
    Serial.println("MDNS responder started");
  }
  Serial.println("");
  Serial.println("connected to...");
  
  Serial.print("IP Adrress: ");
  Serial.println(WiFi.localIP());

  server.on("/", HOMEPAGE);
  server.on("/on", onLED);
  server.on("/off", offLED);
  server.begin();
}

void loop() {
  MDNS.update();
  server.handleClient();

}
