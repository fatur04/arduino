#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// if you don't know your display address, run an I2C scanner sketch
LiquidCrystal_I2C lcd(0x27, 16, 2);  
String messageStatic = "Static message";
String messageToScroll = "This is a scrolling message with more than 16 characters";

void scrollText(int row, String message, int delayTime, int lcdColumns) {
  for (int i=0; i < lcdColumns; i++) {
    message = " " + message;  
  } 
  message = message + " "; 
  for (int pos = 0; pos < message.length(); pos++) {
    lcd.setCursor(0, row);
    lcd.print(message.substring(pos, pos + lcdColumns));
    delay(delayTime);
  }
}
void setup(){
  // initialize LCD
  lcd.init();
  // turn on LCD backlight                      
  lcd.backlight();
}
void loop(){
  // set cursor to first column, first row
  lcd.setCursor(0, 0);
  // print static message
  lcd.print(messageStatic);
  // print scrolling message
  scrollText(1, messageToScroll, 250, 16);
}
