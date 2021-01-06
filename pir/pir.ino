int ledPin = 12;                                           // Memilih pin indikator LED
int inputPin = D1;                                         // Memilih input PIR Sensor
int pirState = LOW;                                 // Pada saat mulai, Matikan sensor
int val = 0;                                               // Variable pembaca status pin
int pinSpeaker = D2;                               // Memilih pin buzzer, dengan pin PWM
void setup() {
  pinMode(ledPin, OUTPUT);                // jadikan LED sebagai Output
  pinMode(inputPin, INPUT);               // jadikan Sensor sebagai Input
  pinMode(pinSpeaker, OUTPUT);      // jadikan buzzer sebagai output
  Serial.begin(9600);
}
void loop(){
  val = digitalRead(inputPin);
  if (val == HIGH) {
    digitalWrite(ledPin, HIGH);
    digitalWrite (pinSpeaker, HIGH);
    delay(150);
    digitalWrite (pinSpeaker, LOW);
    delay(150);
 
    if (pirState == LOW) {
      Serial.println("Terdeteksi suatu pergerakan!");
      pirState = HIGH;
    }
  } else {
      digitalWrite(ledPin, LOW);
     digitalWrite (pinSpeaker, LOW);
    delay(150);
     
      if (pirState == HIGH){
      Serial.println("Motion ended!");
      pirState = LOW;
    }
  }
}
