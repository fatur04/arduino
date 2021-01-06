#include "HX711.h"  //You must have this library in your arduino library folder
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#define DOUT  3
#define CLK  2

LiquidCrystal_I2C lcd(0x27,16,2); 
HX711 scale(DOUT, CLK);
float calibration_factor = 96660;
Servo myservo;
int berat;
int relayPin = 8;
int hasil = 9;
int buzzerPin = 10;
int fanPin = 11;
int ldrPin = A0;

void setup () {
  lcd.init();
  lcd.backlight(); 
  Serial.println("Press T to tare");
  scale.set_scale(96657);  //Calibration Factor obtained from first sketch
  scale.tare(); 
Serial.begin(9600);
pinMode(relayPin, OUTPUT);
pinMode(buzzerPin, OUTPUT);
pinMode(fanPin, OUTPUT);
pinMode(ldrPin, INPUT);
myservo.attach(9);
}

void loop() {
int ldrStatus = analogRead(ldrPin);
lcd.clear(); //Limpa LCD
lcd.setCursor(0,0);
lcd.print("Berat :");
lcd.print(scale.get_units(),3); //Up to 3 decimal points
berat = scale.get_units(); // Here I get the same value shown in lcd but with only two decimals
Serial.println(berat);
lcd.setCursor(12,0);
lcd.print(" g"); //Change this to kg and re-adjust the calibration factor if you follow lbs
delay(1500);

if (ldrStatus > 800 && berat < 1 ) {
digitalWrite(buzzerPin, LOW);
digitalWrite(relayPin, HIGH);
Serial.println(" ALARM ACTIVATED ");
hasil = analogRead(A0);       //hasil = input dari sensor LDR
  hasil = map(hasil, 0, 800, 0, 130);         //Convert hasil LDR untuk Servo
  myservo.write(hasil);                               //Putar servo sesuai hasil LDR
  analogWrite(fanPin, 255); 

}
else {
digitalWrite(buzzerPin, HIGH);
delay(100);
digitalWrite(buzzerPin, LOW);
delay(100);
digitalWrite(relayPin, LOW);
  hasil = analogRead(A0);       //hasil = input dari sensor LDR
  hasil = map(hasil, 0, 800, 0, 0);         //Convert hasil LDR untuk Servo
  myservo.write(hasil);                               //Putar servo sesuai hasil LDR
analogWrite(fanPin, 0);  
Serial.println("ALARM DEACTIVATED");
}
}
