#include <Servo.h> 

Servo servoKu;

void setup (){
  servoKu.attach(D4);
}

void loop(){
  servoKu.write (90);
  delay (1000);
  servoKu.write (180);
  delay (1000);
}
