#include <painlessMesh.h>
 
// Define Pin GPIO dengan nama -----------------------------------
#define LED  2   //GPIO untuk blink
 
// Define untuk timing led indikator -----------------------------
#define   BLINK_PERIOD    3000 // milliseconds until cycle repeat
#define   BLINK_DURATION  100  // milliseconds LED is on for
 
// Define untuk koneksi dan port jaringan ------------------------
#define   MESH_SSID       "warriornux.com"
#define   MESH_PASSWORD   "1234567890"
#define   MESH_PORT       5555
int ldrPin = A0;
 
// Prototypes ----------------------------------------------------
void sendMessage(); 
void receivedCallback(uint32_t from, String & msg);
void newConnectionCallback(uint32_t nodeId);
void changedConnectionCallback(); 
void nodeTimeAdjustedCallback(int32_t offset); 
void delayReceivedCallback(uint32_t from, int32_t delay);
 
// Mengontrol Personal Task dan memanggil library painlessmesh ---
Scheduler     userScheduler;
painlessMesh  mesh;
 
bool calc_delay = false;
SimpleList<uint32_t> nodes;
 
// Mejalankan perintah untuk mengirim pesan ----------------------
void sendMessage() ; // Prototype
Task taskSendMessage( TASK_SECOND * 1, TASK_FOREVER, &sendMessage ); // start with a one second interval
 
// Task untuk menjalankan indikator sesuai jumlah node -----------
Task blinkNoNodes;
bool onFlag = false;
 
void setup() {
  Serial.begin(115200);
 
  pinMode(LED, OUTPUT);
  pinMode(ldrPin, INPUT);
 
// Untuk menampilkan log pesan mesh di serial --------------------
  mesh.setDebugMsgTypes(ERROR | DEBUG | CONNECTION);  // set before init() so that you can see startup messages
 
// Menjalankan Program dari Mesh Network --------------------------
  mesh.init(MESH_SSID, MESH_PASSWORD, &userScheduler, MESH_PORT);
  mesh.onReceive(&receivedCallback);
  mesh.onNewConnection(&newConnectionCallback);
  mesh.onChangedConnections(&changedConnectionCallback);
  mesh.onNodeTimeAdjusted(&nodeTimeAdjustedCallback);
  mesh.onNodeDelayReceived(&delayReceivedCallback);
 
// Mengaktifkan Schedule untuk mengirim pesan ---------------------
  userScheduler.addTask( taskSendMessage );
  taskSendMessage.enable();
 
// Mengaktifkan parameter pada led indikator ----------------------
// dengan menyesuaikan dengan node yang aktif ---------------------
  blinkNoNodes.set(BLINK_PERIOD, (mesh.getNodeList().size() + 1) * 2, []() {
      // If on, switch off, else switch on
      if (onFlag)
        onFlag = false;
      else
        onFlag = true;
      blinkNoNodes.delay(BLINK_DURATION);
 
      if (blinkNoNodes.isLastIteration()) {
        // Finished blinking. Reset task for next run 
        // blink number of nodes (including this node) times
        blinkNoNodes.setIterations((mesh.getNodeList().size() + 1) * 2);
        // Calculate delay based on current mesh time and BLINK_PERIOD
        // This results in blinks between nodes being synced
        blinkNoNodes.enableDelayed(BLINK_PERIOD - 
            (mesh.getNodeTime() % (BLINK_PERIOD*1000))/1000);
      }
  });
  userScheduler.addTask(blinkNoNodes);
  blinkNoNodes.enable();
 
  randomSeed(analogRead(A0));
}
 
void loop() {
// Menjalankan scheduler dan mesh untuk update -----------------------------
  userScheduler.execute(); // it will run mesh scheduler as well
  mesh.update();
 
// Menjalankan LED Indikator -----------------------------------------------
  digitalWrite(LED, !onFlag);
 
  
}
 
// void untuk mengirim pesan ke node lain -----------------------------------
void sendMessage() {
  int ldrStatus = analogRead(ldrPin);
  Serial.print("Nilai LDR: ");
  Serial.println(ldrStatus);
  String msg = "Hello from node "+ldrStatus;
  msg += mesh.getNodeId();
  msg += " myFreeMemory: " + String(ESP.getFreeHeap());
  mesh.sendBroadcast(msg);
 
  if (calc_delay) {
    SimpleList<uint32_t>::iterator node = nodes.begin();
    while (node != nodes.end()) {
      mesh.startDelayMeas(*node);
      node++;
    }
    calc_delay = false;
  }
 
  Serial.printf("Sending message: %s\n", msg.c_str());
  
  taskSendMessage.setInterval( random(TASK_SECOND * 1, TASK_SECOND * 5));  // between 1 and 5 seconds
}
 
// void untuk meminta callback pesan dari node lain ---------------------------
void receivedCallback(uint32_t from, String & msg) {
  Serial.printf("startHere: Received from %u msg=%s\n", from, msg.c_str());
}
 
// 
void newConnectionCallback(uint32_t nodeId) {
  // Reset blink task
  onFlag = false;
  blinkNoNodes.setIterations((mesh.getNodeList().size() + 1) * 2);
  blinkNoNodes.enableDelayed(BLINK_PERIOD - (mesh.getNodeTime() % (BLINK_PERIOD*1000))/1000);
 
  Serial.printf("--> startHere: New Connection, nodeId = %u\n", nodeId);
}
 
// void untuk menginformasikan koneksi ketika berpindah ------------------------
void changedConnectionCallback() {
  Serial.printf("Changed connections %s\n", mesh.subConnectionJson().c_str());
  // Reset blink task
  onFlag = false;
  blinkNoNodes.setIterations((mesh.getNodeList().size() + 1) * 2);
  blinkNoNodes.enableDelayed(BLINK_PERIOD - (mesh.getNodeTime() % (BLINK_PERIOD*1000))/1000);
 
  nodes = mesh.getNodeList();
 
  Serial.printf("Num nodes: %d\n", nodes.size());
  Serial.printf("Connection list:");
 
  SimpleList<uint32_t>::iterator node = nodes.begin();
  while (node != nodes.end()) {
    Serial.printf(" %u", *node);
    node++;
  }
  Serial.println();
  calc_delay = true;
}
 
void nodeTimeAdjustedCallback(int32_t offset) {
  Serial.printf("Adjusted time %u. Offset = %d\n", mesh.getNodeTime(), offset);
}
 
void delayReceivedCallback(uint32_t from, int32_t delay) {
  Serial.printf("Delay to node %u is %d us\n", from, delay);
}
