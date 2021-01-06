#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN D4 //RX slave select
#define RST_PIN D2

MFRC522 mfrc522(SS_PIN, RST_PIN);

String CardID="";

void setup() {
  delay(1000);
  Serial.begin(115200);
  SPI.begin();  // Init SPI bus
  mfrc522.PCD_Init();
  
}

void loop() {
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
  return;//got to start of loop if there is no card present
 }
 // Select one of the cards
 if ( ! mfrc522.PICC_ReadCardSerial()) {
  return;//if read card serial(0) returns 1, the uid struct contians the ID of the read card.
 }

 for (byte i = 0; i < mfrc522.uid.size; i++) {
     CardID += mfrc522.uid.uidByte[i];

  Serial.println(CardID);
delay(500);
  
  CardID = "";
 
}
}
