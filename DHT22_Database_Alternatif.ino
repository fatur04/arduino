#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <LiquidCrystal_I2C.h>
#include <ESP8266WebServer.h>

#include "DHT.h"
#define DHTPIN 14     // DHT PIN D5
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27,16,2);
int Led_OnBoard = 2;  

#define SERVER_IP "192.168.140.99"

#ifndef STASSID
//#define STASSID "WAP04/01-GedungC"
//#define STAPSK  "Ifars_GedungC"
//#define STASSID "LAN1"
//#define STAPSK  "1-Tiga-0_OK_ya"
#define STASSID "WAP01/02"
#define STAPSK  "Ifars-LabMicro"
#endif

float t = 0.7;
float h = 0.5;

void setup() {

  Serial.begin(115200);
  lcd.begin();
  lcd.backlight();
  pinMode(Led_OnBoard, OUTPUT);
  
  Serial.println();
  Serial.println();
  Serial.println();

  WiFi.begin(STASSID, STAPSK);

  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(Led_OnBoard, LOW);
    delay(250);
    Serial.print(".");
    digitalWrite(Led_OnBoard, HIGH);
    delay(250);
    Serial.print(".");
    lcd.setCursor(0,0);
    lcd.print("Menghubungkan...");
  }
  Serial.println("");
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());
  lcd.setCursor(1,0);
  lcd.print("Terhubung WiFi");
  lcd.clear();
  dht.begin();
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  String ruang = "Lab Micro";
  String id_alat = "THL02/01";

  if (isnan(h) || isnan(t) ) {
    Serial.println("Failed to read from DHT sensor!");
    lcd.setCursor(0,0);
    lcd.clear();
    lcd.print("Failde DHT");
    return;
  }
  
  // wait for WiFi connection
  if ((WiFi.status() == WL_CONNECTED)) {

    WiFiClient client;
    HTTPClient http;

    String suhu, kelembaban, postData;
    
    suhu = String(t); 
    kelembaban = String(h);
    postData = "suhu=" + suhu + "&kelembaban=" + kelembaban + "&ruang=" + ruang + "&id_alat=" + id_alat ;

    http.begin("http://192.168.140.99/iot/monitoring-suhu/update.php");  
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");           

  int httpCode = http.POST(postData);
  String payload = http.getString();

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
  delay(1800000);
    
  http.end();
  }
}
