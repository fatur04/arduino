//Library yang digunakan
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <LiquidCrystal_I2C.h>
#include <ESP8266WebServer.h>

#include "DHT.h"
#define DHTPIN 14     // DHT PIN D5 pada ESP8266
//#define DHTPIN 12   //PIN 6
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal_I2C lcd(0x27,16,2); //Alamat LCD 0x27
int Led_OnBoard = 2;  //Led Pada ESP8266

#define SERVER_IP "192.168.140.99" //Alamat Server 

//Nama SSID dan Password WiFi
#ifndef STASSID
#define STASSID "WAP04/01-GedungC"
#define STAPSK  "Ifars_GedungC"
//#define STASSID "LAN1"
//#define STAPSK  "1-Tiga-0_OK_ya"
//#define STASSID "WAP01/02"
//#define STAPSK  "Ifars-LabMicro"
#endif

void setup() {

  Serial.begin(115200); 
  lcd.begin();
  lcd.backlight();
  pinMode(Led_OnBoard, OUTPUT); //Output LED pad ESP8266
  
  Serial.println();
  Serial.println();
  Serial.println();

  WiFi.begin(STASSID, STAPSK);

  //Koneksi ke WiFi
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

//Perulangan Void Loop
void loop() {
        //Perulangan waktu 1754000
  int timeDelay = 0;
  while (timeDelay <= 1754000) {
        
        float h = dht.readHumidity(); //Pembacaan sensor kelembaban dengan tipe data float
        float t = dht.readTemperature(); //Pembacaan sensor suhu dengan tipe data float
        String ruang = "Lab Micro"; //Penambahan Ruang 
        String id_alat = "THL02/01"; //Penambahan ID Alat
      
        //kalibrasi
        float Ksuhu = t-2.2;
        float Klembab = h+5.5;
      
        //Perulangan jika sensor tidak terdektsi atau pemasangan sensor tidak sesuai
        if (isnan(Ksuhu) || isnan(Klembab) ) {
          Serial.println("Failed to read from DHT sensor!");
          lcd.setCursor(0,0);
          lcd.clear();
          lcd.print("Failde DHT");
          return;
        }
        lcd.backlight();
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Suhu : ");
        lcd.print(Ksuhu );
        lcd.print(" ");
        lcd.print((char)223);
        lcd.print("C");
        lcd.setCursor(0,1);
        lcd.print("Lembab : ");
        lcd.print(Klembab);
        lcd.print(" %");
        delay(2000);
        timeDelay=timeDelay +2000;
     }
  
  //perulangan pengiriman data ke database
  if ((WiFi.status() == WL_CONNECTED)) {

    WiFiClient client;
    HTTPClient http;
    
    float h = dht.readHumidity(); //Pembacaan sensor kelembaban dengan tipe data float
    float t = dht.readTemperature(); //Pembacaan sensor suhu dengan tipe data float
    String ruang = "Lab Micro"; //Penambahan Ruang 
    String id_alat = "THL02/01"; //Penambahan ID Alat
      
        //kalibrasi
    float Ksuhu = t-2.2;
    float Klembab = h+5.5;
        
    String suhu, kelembaban, postData;
    
    suhu = String(Ksuhu); //sensor suhu diubah menjadi string
    kelembaban = String(Klembab); //sensor kelembaban di ubah menjadi string
    postData = "suhu=" + suhu + "&kelembaban=" + kelembaban + "&ruang=" + ruang + "&id_alat=" + id_alat ; //string pengiriman data ke php

    http.begin("http://192.168.140.99/iot/monitoring-suhu/update.php");  //alamat ip server dan letak file php pada server
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");           

    int httpCode = http.POST(postData); //pengiriman dengan method POST
    String payload = http.getString(); 
  
    //menampilkan hasil pembacaan sensor ke serial monitor
    Serial.print("data yang dikirim ");
    Serial.print("Temperature: ");
    Serial.print(Ksuhu);
    Serial.print(" *C\t");
    Serial.print("Humidity: ");
    Serial.print(Klembab);
    Serial.println(" %");
  
    //menampilkan hasil pembacaan sensor ke LCD
    lcd.backlight();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Suhu : ");
    lcd.print(Ksuhu );
    lcd.print(" ");
    lcd.print((char)223);
    lcd.print("C");
    lcd.setCursor(0,1);
    lcd.print("Lembab : ");
    lcd.print(Klembab);
    lcd.print(" %");
    //delay(1800.000);
      
    http.end();
    }
  
}
