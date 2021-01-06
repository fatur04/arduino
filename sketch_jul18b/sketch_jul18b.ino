#include <Hx711.h>
Hx711 scale(3, 2);

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print(scale.getGram(),2);
  Serial.println(" g");
  delay(200);
}
