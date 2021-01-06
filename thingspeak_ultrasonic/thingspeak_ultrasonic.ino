#include "ThingSpeak.h"
#include <ESP8266WiFi.h>
  
//----------- Enter you Wi-Fi Details---------//
char ssid[] = "UNDIP-OPEN"; //SSID
char pass[] = "sembarang"; // Password
//-------------------------------------------//

const int trigger = 16; //D0
const int echo = 5; //D1
long T;
float distanceCM;
WiFiClient  client;
int led = D2;
unsigned long myChannelField = 920715; // Channel ID
const int ChannelField = 1; // Which channel to write data
const char * myWriteAPIKey = "WVUETRLEYKV5JORI"; // Your write API Key

void setup()
{
  Serial.begin(115200);
  pinMode(trigger, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(echo, INPUT);
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);
}
void loop()
{
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    while (WiFi.status() != WL_CONNECTED)
    {
      WiFi.begin(ssid, pass);
      Serial.print(".");
      delay(5000);
    }
    Serial.println("\nConnected.");
  }
  digitalWrite(trigger, LOW);
  delay(1);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  T = pulseIn(echo, HIGH);
  distanceCM = T * 0.034;
  distanceCM = distanceCM / 2;
  if (distanceCM < 10) {
     digitalWrite(led,HIGH);
  }
  else {
  digitalWrite(led,LOW);
  }
  Serial.print("Distance in cm: ");
  Serial.println(distanceCM);
  ThingSpeak.writeField(myChannelField, ChannelField, distanceCM, myWriteAPIKey);
  delay(1000);
}
