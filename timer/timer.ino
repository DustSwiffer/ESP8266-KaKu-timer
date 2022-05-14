#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <NewRemoteTransmitter.h>

WiFiUDP ntpUDP;

#define WLAN_SSID       ""
#define WLAN_PASS       ""

NTPClient timeClient(ntpUDP, "pool.ntp.org");
NewRemoteTransmitter transmitter(33233314, 14, 232);

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
 
  // Give timeClient the time to wake-up
  delay(1000);
}

void loop() {
  timeClient.update();
  
  String date = timeClient.getFormattedDate();
  
  if(getTimeZone(date) == 0){
    timeClient.setTimeOffset(3600);
  } else{
    timeClient.setTimeOffset(7200);
  }
  
  String ntpTime = timeClient.getFormattedTime();
  Serial.println(date + " time: " + ntpTime);

  if(ntpTime == "21:00:00"){
    transmitter.sendUnit(1, 0);
  }
  
  if(ntpTime == "09:00:00"){
    transmitter.sendUnit(1, 1);
  }
  
  delay(500);
}
