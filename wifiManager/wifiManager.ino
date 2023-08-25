#include "captivePortal_webServer.h"
#include "wifiScan.h"
#include "wifiPreferences.h"

void setup() {
  Serial.begin(115200);

  Serial.println("MODE: WIFI_AP_STA");
  WiFi.mode(WIFI_AP_STA);

  setupPortal();
}

void loop() {
  dnsServer.processNextRequest();

}
