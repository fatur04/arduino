#include <ESP8266WiFi.h>

const char *ssid = "UNDIP-OPEN"; //ganti nama wifi
const char *pass = "sembarang";//ganti password

WiFiClient client;

void setup()
{
Serial.begin(9600);
delay(10);

Serial.print(" Menghubungkan ke : ");
Serial.println(ssid);

WiFi.begin(ssid, pass);
while (WiFi.status() != WL_CONNECTED)
{
delay(500);
Serial.print("….");
}
Serial.print("\n");
Serial.print("IP address : ");
Serial.print(WiFi.localIP());
Serial.print("\n");
Serial.print("MAC : ");
Serial.println(WiFi.macAddress());
Serial.println("");
Serial.print("Terhubung dengan : ");
Serial.println(ssid);
}

void loop() { }
