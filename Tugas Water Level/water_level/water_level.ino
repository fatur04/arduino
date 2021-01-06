int SensorAtas = 10;
int SensorBawah = 11;
int RelayPompa = 12;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode (SensorAtas, INPUT);
pinMode (SensorBawah, INPUT);
pinMode (RelayPompa, OUTPUT);

}
void loop() {
  // put your main code here, to run repeatedly:
if ((SensorAtas == 1) && (SensorBawah == 1)) {
  digitalWrite(RelayPompa, HIGH);
}
else if ((SensorAtas == 1) && (SensorBawah == 0)) {
  digitalWrite(RelayPompa, HIGH);
}
else {
  digitalWrite(RelayPompa, LOW);
}
}
