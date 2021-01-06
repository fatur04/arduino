#define roomId            1
#define pinTombolCall     D2
#define pinTombolCancel   D3

#include <ESP8266WiFi.h>

//Konfigurasi WiFi
const char *ssid = "nasibkupiye";
const char *password = "1234567890";

const char *host = "192.168.4.1";
String statusCall;
bool eventCall;

void setup() {
  Serial.begin(115200);
  
  pinMode(pinTombolCall, INPUT);
  pinMode(pinTombolCancel, INPUT);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  //Jika koneksi berhasil, maka akan muncul address di serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

int value = 0;

void loop() {
  // Proses Pengiriman -----------------------------------------------------------
  delay(1000);
  ++value;

  Serial.print("connecting to ");
  Serial.println(host);

// Mengirimkan ke alamat host dengan port 80 -----------------------------------
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  if (!digitalRead(pinTombolCall))
  {
    delay(100);
    if (!digitalRead(pinTombolCall))
    {
      statusCall = "call";
      eventCall = true;
    }
  }
  if (!digitalRead(pinTombolCancel))
  {
    delay(100);
    if (!digitalRead(pinTombolCancel))
    {
      statusCall = "cancel";
      eventCall = true;
    }
  }

  if (eventCall)
  {
    //String url = "Hello cuk";
    String url = (String(roomId) + "&status=" + (statusCall));
    
    Serial.print("Requesting URL: ");
    Serial.println(url);
  
  // Mengirimkan Request ke Server -----------------------------------------------
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n\r\n");
    
    unsigned long timeout = millis();
    while (client.available() == 0) {
      if (millis() - timeout > 1000) {
        Serial.println(">>> Client Timeout !");
        client.stop();
        return;
      }
  }

// Read all the lines of the reply from server and print them to Serial
  while (client.available()) {
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }

  Serial.println();
  Serial.println("closing connection");
}
}
