#define trigPin 7
#define echoPin 6
#define buzzer 3

int sound = 250;
void setup() {
Serial.begin (9600);
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
pinMode(buzzer, OUTPUT);
}
void loop() {
long duration, distance;
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance = (duration/2) / 29.1;

if (distance == distance) {
sound = 0;
}
else if (distance < distance) {
digitalWrite(sound,HIGH);
}
else {
Serial.print(distance);
Serial.println(" cm");
tone(buzzer, sound);}
}
