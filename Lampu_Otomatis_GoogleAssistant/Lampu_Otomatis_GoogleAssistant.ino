// Perintah ON dan OFF
#include <ESP8266WiFi.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>
#include <Servo.h> 

#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h> 


#define MQTT_SERV "io.adafruit.com"
#define MQTT_PORT 1883
#define MQTT_NAME "sajojo11"
#define MQTT_PASS "aio_hltK01ukcTWlkoV30ujfdMibdRJz"

int led = D5;
Servo servoKu;

char ssid[] = "";
 char pass[] = "";
 
WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, MQTT_SERV, MQTT_PORT, MQTT_NAME, MQTT_PASS);

Adafruit_MQTT_Subscribe onoff = Adafruit_MQTT_Subscribe(&mqtt, MQTT_NAME "/f/onoff");
Adafruit_MQTT_Publish LightStat = Adafruit_MQTT_Publish(&mqtt, MQTT_NAME "/f/LightStat");


void setup()
{
  Serial.begin(115200); //Sesuaikan dengan Baudrate ESP8266 kalian
  pinMode(LED_BUILTIN, OUTPUT);

  //Connect to WiFi
  Serial.print("\n\nConnecting Wifi>");
  WiFi.begin(ssid, pass);
  WiFiManager wifiManager;
  
  digitalWrite(LED_BUILTIN, LOW);
  servoKu.attach(D4);

  wifiManager.autoConnect("Patur", "password");
  
  Serial.println("OK!");

  //Subscribe to the onoff topic
  mqtt.subscribe(&onoff);

  pinMode(led, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(led, LOW);

}

void loop()
{
  //Connect/Reconnect to MQTT
  MQTT_connect();

  //Read from our subscription queue until we run out, or
  //wait up to 5 seconds for subscription to update
  Adafruit_MQTT_Subscribe * subscription;
  while ((subscription = mqtt.readSubscription(5000)))
  {
    //If we're in here, a subscription updated...
    if (subscription == &onoff)
    {
      //Print the new value to the serial monitor
      Serial.print("onoff: ");
      Serial.println((char*) onoff.lastread);

      //If the new value is  "ON", turn the light on.
      //Otherwise, turn it off.
      if (!strcmp((char*) onoff.lastread, "ON"))
      {
        //active low logic
        digitalWrite(led, HIGH);
        LightStat.publish("ON");
        servoKu.write (90);
      }
      else if (!strcmp((char*) onoff.lastread, "OFF"))
      {
        digitalWrite(led, LOW);
        LightStat.publish("OFF");
        servoKu.write (180);

      }
      else
      {
        LightStat.publish("ERROR");
      }
    }
    else
    {
      //LightStat.publish("ERROR");
    }
  }
}


void MQTT_connect()
{
  // Stop if already connected
  if (mqtt.connected() && mqtt.ping())
  {
    return;
  }

  int8_t ret;

  mqtt.disconnect();

  Serial.print("Connecting to MQTT... ");
  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) // connect will return 0 for connected
  {
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying MQTT connection in 5 seconds...");
    mqtt.disconnect();
    delay(5000);  // wait 5 seconds
    retries--;
    if (retries == 0)
    {
      ESP.reset();
    }
  }
  Serial.println("MQTT Connected!");
}
