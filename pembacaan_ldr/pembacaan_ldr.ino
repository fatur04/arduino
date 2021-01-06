#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  lcd.init();
  lcd.setBacklight(HIGH);

  Serial.begin(9200);//mengaktifkan fungsi serial
}
void loop() {
  //membaca nilai LDR pada pin analog 0
  int sensorValue = analogRead(A0);
  //mencetak nilai yang terbaca pada serial monitor
  lcd.println(sensorValue);
  Serial.println(sensorValue);
  delay(500);   //delay untuk memperlambat pembacaan
  lcd.clear();
}
