#include <DHT_U.h>

         /////////////////////////////////////////////  
        //     WhatsApp Notification Station       //
       //             (via Twilio)                //
      //          ---------------------          //
     //             NodeMCU (ESP-12E)           //           
    //            by Kutluhan Aktar            // 
   //                                         //
  /////////////////////////////////////////////

// By only subscribing to TheAmplituhedron, you will be able get your data packets from NodeMCU, or any other device that can make an HTTP GET Request, to your phone as WhatsApp messages via Twilio through TheAmplituhedron.
// You will need a Twilio account to get WhatsApp messages automatically from the webhook.
// Then, you can use the webhook including the Twilio WhatsApp API by defining these five paranaters below.
// Note: Do not use the plus sign(+) when entering the phone numbers if you are using the webhook application or source code provied by TheAmplituhedron.
// Note: You will also need your unique hedron to connect the webhook application(WhatsApp WebHook).
// Parameters:
// 1) Twilio Account SID
// 2) Twilio Account AUTH TOKEN
// 3) Message Body
// 4) From: Dedicated Business Phone Number
// 5) To: Your Verified Phone Number
// Click the links below for more information about Twilio.
// https://www.twilio.com/whatsapp
// https://www.theamplituhedron.com/dashboard/WhatsApp-Web-Hook/
//
// As a reminder, my website has SSL protection so that you need to identify your NodeMCU connection by entering TheAmplituhedron FingerPrint or ThumbPrint.
// You can learn about it more from the link below.
// https://www.theamplituhedron.com/projects/WhatsApp-Notification-Station/
//
// In this project turorial, I decided to use an HC-SR04 Ultrasonic Sensor, and a DHT11 Temperature and Humidity as data providers.
// To detect any tresspasser trespasser, I used the ultrasonic sensor which triggers the notification message: "Someone is trespassing!"
// Every half minute, the board send a message body to the webhook that transmits it to your phone as a WhatsApp message via Twilio.
// I created a free webhook application for TheAmplituhedron subscribers and used it in this project. But, if you do not want to use this service,
// you can copy the source code from the link on the top.
//
// Connections
// NodeMCU (ESP-12E) :           
//                                DHT11 Temperature and Humidity Sensor Module
// D2  --------------------------- Data
//                                HC-SR04 Ultrasonic Sensor
// D4  --------------------------- Trig
// D5  --------------------------- Echo
int ledPin = 12;                                           // Memilih pin indikator LED
int inputPin = 13;                                         // Memilih input PIR Sensor
int pirState = LOW; 
int val = 0; 
// Include required libraries to send data to a website, in this case TheAmplituhedron.com.
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

// Include DHT master library to elicit information from DHT11 Temperture and Humidity Sensor.
#include "DHT.h"

// Define DHT object.
DHT dht();

// Define your WIFI settings.
const char *ssid = "UNDIP-OPEN";
const char *password = "sembarang";

// Create data holders to send data packets.
String temperature, humidity;
String fingerprint, WebHook, HEDRON, id, token, message, from, to, trespass;

// Define HC-SR04 pins and measurements to detect any movement.
#define trig D4
#define echo D5
long duration, distance;

void setup() {
  // Start DHT object at digital pin 2.
  
  
  // Initiate HC-SR04 pins.
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
 
  // Wait until connected.
  delay(1000);
  Serial.begin(115200);

  // It is just for assuring connection is alive.
  WiFi.mode(WIFI_OFF);
  delay(1000);
  // This mode allows NodeMCU to connect any WiFi directly.
  WiFi.mode(WIFI_STA);        
  // Connect NodeMCU to your WiFi.
  WiFi.begin(ssid, password);
  
  Serial.print("\n\n");
  Serial.print("Try to connect to WiFi. Please wait! ");
  Serial.print("\n\n");
  // Halt the code until connected to WiFi.
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("*");
  }
 
  // If connection is successful, turn control led(if used) on and write WiFi SSID to serial monitor along with assigned IPAddress.
  Serial.print("\n\n");
  Serial.print("-------------------------------------");
  Serial.print("\n\n");
  Serial.print("Connection is successful!");
  Serial.print("\n\n");
  Serial.print("Connected WiFi SSID : ");
  Serial.print(ssid);
  Serial.print("\n\n");
  Serial.println("Connected IPAddress : ");
  Serial.println(WiFi.localIP());
  Serial.print("\n\n"); 
}

void loop() {
  // Get tenperature and humidity from DHT11. And, detect any tresspasser.
  collectData();
  val = digitalRead(inputPin);
  // Enter the fingerprint.
  fingerprint = "46 3c 5c 2c 67 11 cd 88 b7 e9 76 74 41 34 48 bd bc a5 b9 cf";

  // Enter your hedron provided by TheAmplituhedron, Twilio Account Information, and phone numbers.
  HEDRON = "TheAmplituhedron_Hedron";
  id= "AC9b8d08c968a453b5285216e5abc4b19a";
  token = "69d0dce12a58d449bb4ed7e46c63fd70";
  from = "+6283107396111"; // Enter numbers.
  to = "+6283107396111";

  // Create message,use %0A to start a new line.
  message = "Status:+Data+Obtained++%0A%0ATemperature:+" + temperature + "C%0A%0AHumidity:+" + humidity + "%%0A%0AMovement:+" + trespass + "%0A%0AWaiting...";

  // Create the webhook path.
  WebHook = "https://www.theamplituhedron.com/dashboard/WhatsApp-Web-Hook/" + HEDRON + ".php?id=" + id + "&token=" + token + "&body=" + message + "&from=" + from + "&to=" + to;
  
  // Create HTTP object to make a request.
  HTTPClient http;
  
  // Send a request. 
  http.begin(WebHook, fingerprint);
  
  int httpCode = http.GET();           
  String payload = http.getString();    
 
  if(httpCode == 200){ Serial.println("\n Message Sent Successfully..."); }else{ Serial.println("\n Not Working! Error Code: " + httpCode); }
 
  // End HTTP Get Request.
  http.end(); 
  
  // Send data packets every half minute to the webhook.
  delay(30000);
 
}

  void collectData(){
      // Wait until DHT11 Temperature and Humidity Sensor became ready.

      // Detect any movement by using the trigger pin.
      digitalWrite(trig, LOW);
      delay(2);
      digitalWrite(trig, HIGH);
      delay(10);
      digitalWrite(trig, HIGH);
      duration = pulseIn(echo, HIGH);
      distance = (duration / 2) / 29.1;
      if(distance < 8){ trespass = "No+movement+detected!"; }else{ trespass = "Someone+is+trespassing!"; }

      // Dump data packets.
      String data = "\n Tempature: " + temperature + "\n Humidity: " + humidity + "\n Movement: " + trespass + "\n";
      Serial.print(data);
  }
