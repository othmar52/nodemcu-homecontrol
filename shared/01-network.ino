 
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

WiFiClient client;
WiFiUDP UDP;

void setupNetwork() 
{
  connectWlan();
}

void connectWlan() {
               
   Serial.println("Connecting to ");
   Serial.println(ssid); 

   //WiFi.config(ip, gateway, subnet);
   WiFi.begin(ssid, pass);
   WiFi.setAutoReconnect (true);
   while (WiFi.status() != WL_CONNECTED) 
      {
        delay(500);
        Serial.print(".");
      }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println(WiFi.localIP());
  UDP.begin(9); //start UDP client, not sure if really necessary.
}

void reconnectWlan() {
  if(WiFi.status() == WL_CONNECTED) {
    WiFi.disconnect(true);
    delay(500);
  }
  connectWlan();
}

void loopNetwork() {

}
