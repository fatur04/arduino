

#include <ESP8266WebServer.h> //memasukan library NodeMCU sebagai web server
#include <ESP8266WiFi.h> //memasukan library NodeMCU
#include <WiFiClient.h> //memasukan library NodeMCU sebagai client

ESP8266WebServer server(80); //menggunakan port 80

//Masukan nama wifi dan password yang akan dibuat
const char *ssid = "Bismillah TA lulus ";
const char *password = "sembarang";
int statusLED = LOW;
int LED = 13;

//membuat fungsi untuk kondisi led built in
void handleLedOn() {
  statusLED = LOW; //Kondisi logika "LOW" membuat led nyala
  digitalWrite(LED, statusLED);
  response();
}

void handleLedOff() {
  statusLED = HIGH; ////Kondisi logika "HIGH" membuat led nyala
  digitalWrite(LED, statusLED);
  response();
}
void handleRoot() {
    response();
}

const String HtmlHtml = "<html><head>"
"<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\" /></head>";
const String HtmlHtmlClose = "</html>";
const String HtmlTitle = "<h1>Bismillah TA LULUS (aamiin) Kendali LED</h1><br/>\n";
const String HtmlLedStateLow = "<big>LED is now <b>OFF</b></big><br/>\n";
const String HtmlLedStateHigh = "<big>LED is now <b>ON</b></big><br/>\n";
const String HtmlButtons = 
"<a href=\"LEDOn\"><button style=\"display: block; width: 100%;\">OFF</button></a><br/>"
"<a href=\"LEDOff\"><button style=\"display: block; width: 100%;\">ON</button></a><br/>";

void response(){
  String htmlRes = HtmlHtml + HtmlTitle;
  if(statusLED == LOW){
    htmlRes += HtmlLedStateLow;
  }else{
    htmlRes += HtmlLedStateHigh;
  }

  htmlRes += HtmlButtons;
  htmlRes += HtmlHtmlClose;

  server.send(200, "text/html", htmlRes);
}

void setup() {
    delay(1000); //waktu tunda 1 detik
    Serial.begin(9600);
    Serial.println();

    WiFi.softAP(ssid, password);
    //bertindak sebagai access point dengan nama wifi dan pass diatas

    IPAddress apip = WiFi.softAPIP(); //alamat IP
    Serial.print("visit: \n");
    Serial.println(apip); //menuliskan alamat IP yang bisa dikunjungi
    
    server.on("/", handleRoot); //memanggil fungsi handleRoot()
    server.on("/LEDOn", handleLedOn);
    server.on("/LEDOff", handleLedOff);

    server.begin(); //proses pemulaian menjadi server
    Serial.println("HTTP server beginned");
   
    pinMode(LED, OUTPUT);
    digitalWrite(LED, statusLED);
}

void loop() {
    server.handleClient();
}
