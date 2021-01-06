#define echoPin 3 // Echo Pin
#define trigPin 2 // Trigger Pin
int maximumRange = 200; // Maximum range needed
int minimumRange = 0; // Minimum range needed
long duration, distance; // Duration used to calculate distance
void setup() {
Serial.begin (9600);
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
}
void loop() {
/* The following trigPin/echoPin cycle is used to determine the
distance of the nearest object by bouncing soundwaves off of it.
*/
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
//Calculate the distance (in cm) based on the speed of sound.
distance = duration/58.2;
Serial.println("distance : ");
Serial.print(distance);
Serial.println(" cm ");
//Delay 50ms before next reading.
delay(1000);
}
