
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16,2);
void setup() {
lcd.begin(16, 2); 

}
void loop() 
{
  lcd.init();
  lcd.setBacklight(HIGH);
lcd.print("  DIAN FATTU R"); 
lcd.setCursor(0, 0);
delay(1500);
lcd.clear();
lcd.print("ARDUINO PROJECTS");
lcd.setCursor(0, 1);
delay(1500);
lcd.setCursor(5, 1);
lcd.print("TUGAS AKHIR");
delay(1500);
lcd.clear();
lcd.setCursor(1, 0);
lcd.print("UNIV TRUNOJOYO");

delay(1500);
lcd.setCursor(5, 1);
lcd.print("MADURA");
delay(1500);
lcd.clear();
}

