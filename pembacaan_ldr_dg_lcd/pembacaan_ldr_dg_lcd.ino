#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

int hasilSensorLDR;
int progressBari = 0;
int i = 0;

byte progressBar[8] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
};

void setup() {
  lcd.init();
  lcd.setBacklight(HIGH);
  lcd.print("Hasil LDR :");
  lcd.createChar(0, progressBar);
}

void loop() {
  lcd.clear();
  lcd.print("Hasil LDR :");
  lcd.setCursor(0,1);
  hasilSensorLDR = analogRead(0);
  lcd.setCursor(12,0);
  lcd.print(hasilSensorLDR);
  progressBari=map(hasilSensorLDR, 0, 1000, 0, 17);
  for (i=0; i<progressBari; i++)
  {
    lcd.setCursor(i, 1);
    lcd.write(byte(0));
  }
  delay(300);     
} 
