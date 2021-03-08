#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

WiFiClient client;
#include "DHT.h"
#define DHTPIN 14     // DHT PIN D5
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27,16,2);

const char* host = "192.168.140.99";
String data;
float t = 0.5;
float h = 0.5;
int Led_OnBoard = 2;   

HTTPClient http;
void setup() {
  Serial.begin(115200); 
  lcd.begin();
  lcd.backlight();
  pinMode(Led_OnBoard, OUTPUT);
 
  WiFi.mode(WIFI_STA);
  //WiFi.begin("LAN1", "1-Tiga-0_OK_ya");
  //WiFi.begin("WAP01/02", "Ifars-LabMicro");
  WiFi.begin("WAP04/01-GedungC", "Ifars_GedungC");
  while ((!(WiFi.status() == WL_CONNECTED))) {
    delay(500);
    Serial.print(".");
    lcd.setCursor(0,0);
    lcd.print("Menghubungkan...");
    digitalWrite(Led_OnBoard, LOW);
    delay(250);
    Serial.print(".");
    digitalWrite(Led_OnBoard, HIGH);
    delay(250);
  }
  Serial.println("");
  Serial.println("Connected");
  lcd.setCursor(1,0);
  lcd.print("Terhubung WiFi");
  lcd.clear();
  dht.begin();
}

void loop() {
  float h = dht.readHumidity();
 float t = dht.readTemperature();
  String ruang = "Lab Micro";

  if (isnan(h) || isnan(t) ) {
    Serial.println("Failed to read from DHT sensor!");
    lcd.setCursor(0,0);
    lcd.clear();
    lcd.print("Failde DHT");
    return;
  }

  if (!client.connect(host, 80)) {
    Serial.println("Gagal Konek");   
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Menghubungkan...");
    return;
  }

  data = "/iot/monitoring-suhu/update.php?suhu=";
  data += t;
  data += "&kelembaban=";
  data += h;
  data += "&ruang=";
  data += ruang;
  
  client.print(String("GET ") + data + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");
  Serial.print("data yang dikirim ");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C\t");
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.println(" %");

  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Suhu : ");
  lcd.print(t );
  lcd.print(" ");
  lcd.print((char)223);
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("Lembab : ");
  lcd.print(h);
  lcd.print(" %");
  delay(10000);

  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }
}
