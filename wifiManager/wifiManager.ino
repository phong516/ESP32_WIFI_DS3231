#include "captivePortal_webServer.h"
#include "wifiScan.h"

void setup() {
  Serial.begin(115200);

  setupPortal();

}

bool isAP = false;

void loop() {
  //check if wifi is connected
  if (WiFi.status() != WL_CONNECTED){
    if (!isAP){
      setupPortal();
      isAP = true;
    }
    else{
      dnsServer.processNextRequest();
    }
  }
    
  // }
  }
