#include "HX711.h" 
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#define DOUT  3
#define CLK  2

LiquidCrystal_I2C lcd(0x27,16,2); 
HX711 scale(DOUT, CLK);
float calibration_factor = -96650;
Servo myservo;
Servo myservo2;
int berat;
int relayPin = 8;
int hasil = 9;
int hasil2 = 10;
int buzzerPin = 11;
int fanPin = 12;
int ldrPin = A0;

void setup () {
  lcd.init();
  lcd.backlight(); 
  Serial.println("Press T to tare");
  scale.set_scale(-96652);  //Calibration Factor obtained from first sketch
  scale.tare(); 
Serial.begin(9600);
pinMode(relayPin, OUTPUT);
pinMode(buzzerPin, OUTPUT);
pinMode(fanPin, OUTPUT);
pinMode(ldrPin, INPUT);
myservo.attach(9);
myservo2.attach(10);
}

void loop() {
int ldrStatus = analogRead(ldrPin);
berat = scale.get_units(); 

if (ldrStatus > 800 ) {
  if ((berat < 1) || (berat > 2)) {
    digitalWrite(buzzerPin, HIGH);
    delay(100);
    digitalWrite(buzzerPin, LOW);
    delay(100);
    digitalWrite(relayPin, HIGH);
      hasil = analogRead(A0);       
      hasil = map(hasil, 0, 800, 0, 80);        
      myservo.write(hasil);                               
      hasil2 = analogRead(A0);       
      hasil2 = map(hasil2, 0, 800, 0, 0);        
      myservo2.write(hasil2);                               
    analogWrite(fanPin, 0); 
    lcd.clear(); 
    lcd.backlight();
    lcd.setCursor(0,0);
    lcd.print("Berat :");
    lcd.print(scale.get_units(),3); 
    Serial.println(berat);
    lcd.setCursor(12,0);
    lcd.print(" g"); 
    delay(1500); }

  else {
    digitalWrite(buzzerPin, LOW);
    digitalWrite(relayPin, LOW);
    Serial.println(" ALARM ACTIVATED ");
      hasil = analogRead(A0);       
      hasil = map(hasil, 0, 800, 0, 0); 
      myservo.write(hasil);          
      hasil2 = analogRead(A0);       
      hasil2 = map(hasil2, 0, 800, 0, 80);        
      myservo2.write(hasil2);                               
      analogWrite(fanPin, 255); 
      lcd.clear(); 
      lcd.backlight();
    lcd.setCursor(0,0);
    lcd.print("Berat :");
    lcd.print(scale.get_units(),3); 
    Serial.println(berat);
    lcd.setCursor(12,0);
    lcd.print(" g"); 
    delay(1500);}

}  
else
 {
digitalWrite(buzzerPin, HIGH);
delay(100);
digitalWrite(buzzerPin, LOW);
delay(100);
digitalWrite(relayPin, HIGH);
  hasil = analogRead(A0);       
  hasil = map(hasil, 0, 800, 0, 80);        
  myservo.write(hasil);   
  hasil2 = analogRead(A0);       
  hasil2 = map(hasil2, 0, 800, 0, 0);        
  myservo2.write(hasil2);                                                           
analogWrite(fanPin, 0); 
lcd.clear(); 
lcd.backlight();
lcd.setCursor(0,0);
lcd.print("Berat :");
lcd.print(scale.get_units(),3); 
Serial.println(berat);
lcd.setCursor(12,0);
lcd.print(" g"); 
delay(1500); 
Serial.println("ALARM DEACTIVATED");}
}
