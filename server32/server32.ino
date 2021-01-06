#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>

const char* ssid = "nasibkupiye";      // Nama AP/Hotspot
const char* password = "1234567890";    // Password AP/Hotspot

WiFiServer server(80);
void setup() {
  Serial.begin(115200);
  delay(10);
  
 // Mengatur WiFi ----------------------------------------------------------
  Serial.println();
  Serial.print("Configuring access point...");
   
  WiFi.mode(WIFI_AP);             // Mode AP/Hotspot
  WiFi.softAP(ssid, password);
  
 // Start the server -------------------------------------------------------
  server.begin();
  Serial.println("Server dijalankan");
  
 // Print the IP address ---------------------------------------------------
  Serial.println(WiFi.localIP());
 }


void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
  
  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  Serial.println("Sukses Boss");
  client.flush();
  Serial.println("Client disonnected");

  // The client will actually be disconnected 
  // when the function returns and 'client' object is detroyed
}
