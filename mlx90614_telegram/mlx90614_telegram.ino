#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <LiquidCrystal_I2C.h> 
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define relay D3
#include "CTBot.h"
CTBot myBot;
int kirim;
const int buttonPin = D4;
int buttonState = 0;

String ssid  = "Open-Free"    ; //nama wifi
String pass  = "sembarang"; // password wifi
String token = "1326835713:AAEb9nrK_mR2Eqwkh7pLye5vvVrM0J1yoQ8"; //token telegram
const int id = 925607567;

void setup() {
pinMode(relay, OUTPUT);
pinMode(buttonPin, INPUT);
digitalWrite(relay,LOW);

  Serial.begin(115200);
  Serial.println("Memulai Telegram Bot...");

  //kalau eror ganti "lcd.begin();"
  lcd.init();
  //lcd.begin();
 
  // Turn on the blacklight and print a message.
  lcd.backlight();
  Serial.println("Adafruit MLX90614 test");  
  lcd.clear();
  lcd.setCursor(0,0); // Move cursor to 0
  lcd.print(" SELAMAT DATANG"); 
  lcd.setCursor(1,1);
  lcd.print("PRESS TO SCAN");  

  mlx.begin();
  myBot.wifiConnect(ssid, pass);

  // set the telegram bot token
  myBot.setTelegramToken(token);
  
  // check if all things are ok
  if (myBot.testConnection())
    Serial.println("Koneksi OK");
  else
    Serial.println("Koneksi gagal");  
}

void loop() {
 if (buttonState==HIGH)
 {
  TBMessage msg;
  int suhu = mlx.readObjectTempC();
  int ambien = mlx.readAmbientTempC();
  
  Serial.print("Ambient = "); 
  Serial.print(ambien); 
  Serial.print("*C\tObject = "); 
  Serial.print(suhu); 
  Serial.println("*C");
  
  lcd.clear(); 
  lcd.setCursor(0,0); 
  lcd.print("Object ="); 
  lcd.print(suhu);
  lcd.print("*C ");


  //Serial.println("Pesan Masuk : " + msg.text);
    Serial.println ((String)ambien);
    Serial.print ((String)suhu);
  
  //String pesan = msg.text;

  //hasil pembacaan sensor suhu disimpan ke string pesan
  String pesan = (String)suhu;

  //nilainya sesuaikan dg hasil pembacaan sensor
  //contohnya hasil pembcaan serial monitor sensor suhu 38.00 
  //pesan >= 38.00 & pesan < 37.00
  //jika hasil pembcaan serial monitor sensor suhu 38
  // pesan >= 38 & pesan < 37
   if( pesan >= "38")
    {
      myBot.sendMessage(id, "PERINGATAN SUHU TUBUH TINGGI");
      
      // Untuk Menampilkan hasil pembacaan sensor ke telegram 
      //myBot.sendMessage(msg.sender.id, "Ambient = "+(String)ambien+ "*C" );
      //myBot.sendMessage(msg.sender.id, "Object = "+(String)suhu+ "*C" );
   
      digitalWrite(relay, LOW); 
      lcd.setCursor(0,1);
      lcd.print(" DILARANG MASUK");
    }
    else if ( pesan < "37"){  
      myBot.sendMessage(id, "SUHU TUBUH NORMAL");

      // Untuk Menampilkan hasil pembacaan sensor ke telegram
      //myBot.sendMessage(msg.sender.id, "Ambient = "+(String)ambien+ "*C" );
      //myBot.sendMessage(msg.sender.id, "Object = "+(String)suhu+ "*C" );
      
      digitalWrite(relay, HIGH); 
      lcd.setCursor(0,1);
      lcd.print(" SILAHKAN MASUK");
    }   
    
  
  Serial.println();
  //delay(15000);

 }
 else {
  int suhu = 0;
  //Serial.print (suhu);
  
 }
}
