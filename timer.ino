#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

#include <NewRemoteTransmitter.h>

WiFiUDP ntpUDP;

#define WLAN_SSID       ""
#define WLAN_PASS       ""

NTPClient timeClient(ntpUDP);

void setup() {
  Serial.begin(115200);
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());

  timeClient.begin();
}

void loop() {
  NewRemoteTransmitter transmitter(33233314, 14, 232);

  timeClient.setTimeOffset(3600);
  timeClient.update();
  
  String formattedTime = timeClient.getFormattedTime();
  
  if(formattedTime == "20:00:00"){
    Serial.println("Release the dragon!");
    transmitter.sendUnit(1, 0);
  }
  
  if(formattedTime == "08:00:00"){
    Serial.println("Bed time for spot");
    transmitter.sendUnit(1, 1);
  }
  
  delay(500);

  
}
