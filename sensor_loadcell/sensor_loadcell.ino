#include "HX711.h"  
#define DOUT  3
#define CLK  2
 
HX711 scale(DOUT, CLK);
float calibration_factor = -96660; 

void setup () {
  Serial.begin(9600);
  Serial.println("Modul HX711");
  scale.set_scale(calibration_factor);
  scale.tare(); 
}
void loop() {
  Serial.print("Berat: ");
  Serial.print(scale.get_units(), 3); 
  Serial.print(" gram"); 
  Serial.println();
  delay(1000);
}
