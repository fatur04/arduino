float tempC;
float tempF;
int tempPin = 0;
int led = 5;
void setup() {
pinMode(5, OUTPUT);
Serial.begin(9600);
}
void loop() {
tempC = analogRead(tempPin); //read the value from the sensor
tempC = (5.0 * tempC * 100.0) / 1024.0; //convert the analog
tempF = ((tempC * 9) / 5) + 32; //convert celcius to farenheit

if ( tempC > 35 ){
  digitalWrite (led,HIGH);
} else { 
 digitalWrite (led,LOW);
}
Serial.println("Temperature : ");
Serial.print(tempC);
Serial.println(" 'C");
Serial.println(" ");
delay(500);

}
