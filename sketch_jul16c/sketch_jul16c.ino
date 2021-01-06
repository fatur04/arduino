#include "HX711.h"  //You must have this library in your arduino library folder
 #include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

#define DOUT  3
#define CLK  2
 
HX711 scale(DOUT, CLK);
 
//Change this calibration factor as per your load cell once it is found you many need to vary it in thousands
float calibration_factor = -96650; //-106600 worked for my 40Kg max scale setup 
 
//=============================================================================================
//                         SETUP
//=============================================================================================
void setup() {
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);  
  Serial.println("Press T to tare");
  scale.set_scale(-96650);  //Calibration Factor obtained from first sketch
  scale.tare();             //Reset the scale to 0  
}
void loop() {
lcd.clear(); //Limpa LCD
lcd.setCursor(0,0);
lcd.print("Berat :");
lcd.print(scale.get_units(),3); //Up to 3 decimal points
float peso = scale.get_units(); // Here I get the same value shown in lcd but with only two decimals
Serial.println(peso);
lcd.setCursor(12,0);
lcd.print(" g"); //Change this to kg and re-adjust the calibration factor if you follow lbs
delay(500);
}
