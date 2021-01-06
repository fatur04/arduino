#include <ESP8266WiFi.h>   //  ESP8266 library
#include <WiFiManager.h> 
#include <WiFiClient.h> 
#define BLYNK_PRINT Serial
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>

// Set web server port number to 80

char auth[] = "5BppfhpivyTkQlUFICxspKQwqmWVNCqi";

const int pinLED = D5;
const int ledPin =  LED_BUILTIN;

void setup() {
  Serial.begin(115200);
  
  pinMode(ledPin, OUTPUT);
  
  WiFiManager wifiManager;
  wifiManager.resetSettings();
  wifiManager.autoConnect("Fatur");

  Blynk.config(auth);
  
  
  Serial.println("");
  Serial.println("connected BOSS...");
  
  Serial.print("IP Adrress: ");
  Serial.println(WiFi.localIP());

}

void loop() {
  Blynk.run(); 

}
