#include "HX711.h"  
 #include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

#define DOUT  3
#define CLK  2

int berat;
int buzzerPin = 10;
HX711 scale(DOUT, CLK);
 
void setup() {
  pinMode(buzzerPin, OUTPUT);
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);  
  Serial.println("Press T to tare");
  scale.set_scale(-96657);  //Calibration Factor obtained from first sketch
  scale.tare();             //Reset the scale to 0  
}
void loop() {
lcd.clear(); 
lcd.setCursor(0,0);
lcd.print("Berat :");
lcd.print(scale.get_units(),3); 
berat = scale.get_units();
Serial.println(berat);
lcd.setCursor(12,0);
lcd.print(" g"); 
delay(1500);

if (berat < 1) {
  digitalWrite (buzzerPin, LOW);
}
else {
  digitalWrite (buzzerPin, HIGH);
  delay (100);
}

}
