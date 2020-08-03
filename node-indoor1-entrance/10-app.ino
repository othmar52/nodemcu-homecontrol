

#include "ESPAsyncWebServer.h"
AsyncWebServer server(80);


#define NUM_BUTTONS 6
// helper var to track press duration
unsigned long BUTTON_LASTDOWN[NUM_BUTTONS];
// helper var to handle long press
bool BUTTON_ISPRESSED[NUM_BUTTONS];
bool BUTTON_EVENTPROCESSED[NUM_BUTTONS];
#include "buttonHandlers.h"
#include "buttonClass.h"


Button button[] = {
  Button("Button D1", D1),
  Button("Button D2", D2),
  Button("Button D3", D3),
  Button("Button D4", D4),
  Button("Button D5", D5),
  Button("Button D6", D6)
};

void setupPushButtons() {
  for (int i = 0; i < NUM_BUTTONS; i++) button[i].setup();
}

void loopPushButtons() {
  for (int i = 0; i < NUM_BUTTONS; i++) button[i].loop();
}


void setupApp(){
  pinMode(doorRelaisPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  
  server.on("/outdoor/door/toggle", HTTP_GET, [](AsyncWebServerRequest *request){
    if(!request->authenticate(http_username, http_password)) {
      debug("auth invalid");
      return request->requestAuthentication(NULL,false); // force basic auth
    }
    triggerDoorRelay();
    request->send(200, "application/json", "{message: \"ACK\"}");
  });
  setupFirmwareUploadForm();
  setupPushButtons();
  server.begin();
}

void loopApp(){
  loopPushButtons();
  loopFirmwareUploadForm();
  loopRelayHandling();
  loopBuzzer();
  processUrlQue();
  
}


String listValidUrlsHtml() {
  String markup = "<h1>gTown NODE Indoor1 entrance</h1>\n";
  markup += "<a href='/outdoor/door/toggle'>outdoor door toggle<br>\n";
  return markup;
}
