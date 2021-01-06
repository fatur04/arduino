int ledPin = 8;
int hasil = 9;
int buzzerPin = 12;
int ldrPin = A0;

void setup () {
Serial.begin(9600);
pinMode(ledPin, OUTPUT);
pinMode(buzzerPin, OUTPUT);
pinMode(ldrPin, INPUT);
}

void loop() {
int ldrStatus = analogRead(ldrPin);
Serial.println(ldrStatus);
if (ldrStatus < 650) {
digitalWrite(ledPin, HIGH);
digitalWrite(buzzerPin, HIGH);
Serial.println("Buzzer Nyala");
delay(100); }
else {
digitalWrite(ledPin, LOW);
digitalWrite(buzzerPin, LOW);
Serial.println("Buzzer Mati");
delay(100); }
}
