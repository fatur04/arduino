int relayPin = 8;
int hasil = 9;
int buzzerPin = 12;
int ldrPin = A0;

void setup () {
Serial.begin(9600);
pinMode(relayPin, OUTPUT);
pinMode(buzzerPin, OUTPUT);
pinMode(ldrPin, INPUT);
}

void loop() {
int ldrStatus = analogRead(ldrPin);
if (ldrStatus < 800) {
digitalWrite(relayPin, HIGH);
Serial.println(" ALARM DEACTIVATED ");
hasil = analogRead(A0);  
noTone(buzzerPin);       
}
else {
tone(buzzerPin, HIGH);
delay(100);
noTone(buzzerPin);
delay(100);
digitalWrite(relayPin, LOW);
Serial.println("ALARM ACTIVATED");
    }
}

