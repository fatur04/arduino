#include "WiFi.h"
#include "ESPAsyncWebServer.h"

const char* ssid = "Open-Free";
const char* password =  "sembarang";

AsyncWebServer server(80);
AsyncWebSocket ws("/test");

void onWsEvent(AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, Base64 *data, size_t len){

  if(type == WS_EVT_CONNECT){

    Serial.println("Websocket client connection received");

  } else if(type == WS_EVT_DISCONNECT){
    Serial.println("Client disconnected");

  } else if(type == WS_EVT_DATA){

    Serial.println("Data received: ");

    for(int i=0; i < len; i++) {
      Serial.print(data[i]);
      Serial.print("|");
    }

    Serial.println();
  }
}

void setup(){
  Serial.begin(115200);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  Serial.println(WiFi.localIP());

  ws.onEvent(onWsEvent);
  server.addHandler(&ws);

  server.begin();
}

void loop(){}
