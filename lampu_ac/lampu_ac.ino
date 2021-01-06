int pinInput = 8;

void setup() {
  // put your setup code here, to run once:
pinMode(pinInput, OUTPUT);
}

void loop() {
  digitalWrite(pinInput, HIGH);
  delay(5000);
  digitalWrite(pinInput, LOW);
  delay(2000);
  // put your main code here, to run repeatedly:

}
