#include <WiFi.h>

#include <ThingsBoard.h>

const char* ssid = "your ssid";
const char* password = "your password";

#define TOKEN               "your token"
#define THINGSBOARD_SERVER  "thingsboard.cloud"

// Initialize ThingsBoard client
WiFiClient espClient;
// Initialize ThingsBoard instance
ThingsBoard tb(espClient);
// the Wifi radio's status
int status = WL_IDLE_STATUS;

void setup()
{
  Serial.begin(9600);
  if(Serial) Serial.println("Serial is open");

  WiFi.begin(ssid, password);

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
}
 

void loop() {
  if (!tb.connected()) {
    // Connect to the ThingsBoard
    Serial.print("Connecting to: ");
    Serial.print(THINGSBOARD_SERVER);
    Serial.print(" with token ");
    Serial.println(TOKEN);
    if (!tb.connect(THINGSBOARD_SERVER, TOKEN)) {
      Serial.println("Failed to connect");
      return;
    }
  }

  Serial.println("Sending data...");
// Here is the data sending 
  tb.sendTelemetryFloat("Temp", 10);  
  

  tb.loop();
  
  delay(1000); //Sampling frequency
}

