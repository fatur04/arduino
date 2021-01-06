#include "HX711.h"  //You must have this library in your arduino library folder
 #include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

#define DOUT  3
#define CLK  2
 
HX711 scale(DOUT, CLK);
 
float calibration_factor = 96660; //-106600 worked for my 40Kg max scale setup 
 
//=============================================================================================
//                         SETUP
//=============================================================================================
void setup() {
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);  
  Serial.println("Press T to tare");
  scale.set_scale(96657);  
  scale.tare();             
}
void loop() {
Serial.println("Berat : ");
Serial.println(scale.get_units(),3); 
float peso = scale.get_units();

delay(500);
}
