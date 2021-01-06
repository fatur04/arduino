int pirSensor = D1;
int led = D2;
void setup() {
Serial.begin(300);
pinMode(pirSensor, INPUT);
pinMode(led, OUTPUT);
}
void loop() {
int sensorValue = digitalRead(pirSensor);
Serial.println(sensorValue);
if (sensorValue == 1) {
digitalWrite(led, HIGH);
} else {
  digitalWrite(led, LOW);
  }
}
