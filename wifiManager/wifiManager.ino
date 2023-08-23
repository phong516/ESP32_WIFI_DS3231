#include <WiFi.h>
#include <ESPAsyncWebSrv.h>
#include <AsyncTCP.h>
#include <DNSServer.h>
#include "webDesign.h"

DNSServer dnsServer;
AsyncWebServer server(80);

class CaptiveRequestHandler : public AsyncWebHandler{
  public:
    CaptiveRequestHandler(){}
    virtual ~CaptiveRequestHandler(){}
  
  bool canHandle(AsyncWebServerRequest *request){
    //request->addInterestingHeader("ANY");
    return !request->hasArg("notfound");
  }

  void handleRequest(AsyncWebServerRequest *request){
    Serial.println("GOT REQUEST");

    request->send_P(200, "text/html", index_html);
    Serial.println("SEND HTML");
  }
};

void setupServer(){

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
  request->send_P(200, "text/html", index_html);
  Serial.println("SEND HTML");
  });

  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/css", style_css);
    Serial.println("SEND CSS");
  });

  server.on("/code.js", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/js", code_js);
    Serial.println("SEND JS");
  });

  server.on("/ap.json", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/json", ap_json);
    Serial.println("SEND AP JSON");
  });

  server.on("/status.json", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/json", status_json);
    Serial.println("SEND STATUS JSON");
  });

  server.on("/connect.json", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/json", connect_json);
    Serial.println("SEND CONNECT JSON");
  });
};



void setup() {
  Serial.begin(115200);

  Serial.println("MODE: WIFI_AP");
  WiFi.mode(WIFI_AP);

  Serial.println("SET SSID");
  WiFi.softAP("PHONG_PORTAL");
  Serial.println(WiFi.softAPIP());

  Serial.println("SETUP SERVER");
  setupServer();

  Serial.println("START SERVER");
  dnsServer.start(53, "*", WiFi.softAPIP());

  Serial.println("ADD HANDLER");
  server.addHandler(new CaptiveRequestHandler()).setFilter(ON_AP_FILTER);
  Serial.println("SERVER BEGIN");
  server.begin();

}

void loop() {
  dnsServer.processNextRequest();
  }
