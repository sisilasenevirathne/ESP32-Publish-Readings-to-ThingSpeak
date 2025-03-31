#include <WiFi.h>
#include "ThingSpeak.h"

const char* ssid = "SJAY-5G";   // your network SSID (name) 
const char* password = "12345678";   // your network password

WiFiClient  client;

unsigned long ChannelID = xxxxxxx;
const char * WriteAPIKey = "xxxxxxxxxxxxxxxxx";

// Timer variables
unsigned long lastTime = 0;
unsigned long timerDelay = 30000;

void setup() {
  Serial.begin(115200);  //Initialize serial
  
  WiFi.mode(WIFI_STA);   
  
  ThingSpeak.begin(client);  // Initialize ThingSpeak
}

void loop() {
  if ((millis() - lastTime) > timerDelay) {
    
    // Connect or reconnect to WiFi
    if(WiFi.status() != WL_CONNECTED){
      Serial.print("Attempting to connect");
      while(WiFi.status() != WL_CONNECTED){
        WiFi.begin(ssid, password); 
        delay(5000);     
      } 
      Serial.println("\nConnected.");
    }

    // Hardcoded values
    int DoorOpen = 1;
    int FanOn = 1;
    Serial.print("DoorOpen: ");
    Serial.println(DoorOpen);
    Serial.print("FanOn: ");
    Serial.println(FanOn);
    
    // Write to ThingSpeak
    ThingSpeak.setField(1, DoorOpen);
    ThingSpeak.setField(2, FanOn);
    int x = ThingSpeak.writeFields(ChannelID, WriteAPIKey);

    if(x == 200){
      Serial.println("Channel update successful.");
    }
    else{
      Serial.println("Problem updating channel. HTTP error code " + String(x));
    }
    lastTime = millis();
  }
}
