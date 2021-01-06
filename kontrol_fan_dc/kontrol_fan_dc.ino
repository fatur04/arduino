int fanpin = 12; 
void setup() { 
  pinMode(fanpin, OUTPUT); 
  } 
  void loop() { 
    analogWrite(fanpin, 255); 
    delay(10000); 
    analogWrite(fanpin, 0);
    delay(6000); 
}

