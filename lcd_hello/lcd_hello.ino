#include <Wire.h>
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27,16,2);


void setup() {
lcd.init();

}

void loop() {
 lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print("Dian Fattu");
  lcd.setCursor(0,1);
  lcd.print("Josss...");
  delay(1000);
  lcd.setBacklight(HIGH);
  delay(1000); 
}

