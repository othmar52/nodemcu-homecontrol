
#include "ESPAsyncWebServer.h"

// library hack (non functional basic auth)
// thanks to https://github.com/me-no-dev/ESPAsyncWebServer/issues/667
// diff Arduino/libraries/ESPAsyncWebServer/src/WebAuthentication.cpp
// -  if(strlen(hash) != encodedLen)
// +  if(strlen(hash) != encodedLen-1)


AsyncWebServer server(80);

//flag to use from web update to reboot the ESP
bool shouldReboot = false;



uint16_t judge(uint8_t ZONE_NAME, uint8_t DEVICE_NAME, const char *FUNC_NAME, uint8_t CLIENT_NODE, uint16_t PUSHDURATION, uint32_t SUBMITTED_PIN) {
  if(pushDurationValid(PUSHDURATION, DEVICE_NAME) == false) {
    return 420;
  }
  if(pinRequired(ZONE_NAME, DEVICE_NAME, FUNC_NAME, CLIENT_NODE) == true && checkValidPin(SUBMITTED_PIN) == false) {
    return 403;
  }
  if(ZONE_NAME == COMBO) {
    fireCombo(ZONE_NAME, DEVICE_NAME, FUNC_NAME);
  } else {
    fire(ZONE_NAME, DEVICE_NAME, FUNC_NAME);
  }
  return (uint16_t)200;
}

/**
 * nodes have not configured what to do when pressing buttons
 * the only send the event button xx pressed to the judge
 * and this judge's function decides what to do...
 * 
 */
/*
void mapButtonIndexToParams(uint8_t CLIENT_NODE, uint8_t CLIENT_BUTTON_INDEX, uint8_t *ZONE_NAME, uint8_t *DEVICE_NAME, char *SUBMITTED_FUNC_NAME, uint8_t *standardParams){
  if(CLIENT_BUTTON_INDEX == 0) {
    return;  
  }
  switch(CLIENT_NODE) {
    case CLIENT_NODE_INDOOR1_ENTRANCE:
      switch(CLIENT_BUTTON_INDEX) {
        case 5: // D1
          *ZONE_NAME = COMBO;
          *DEVICE_NAME = GROUP_INDOOR_ALL;
          strcpy(SUBMITTED_FUNC_NAME, POWEROFF);
          *standardParams = 3;
          return;
        case 4: // D2
          *ZONE_NAME = COMBO;
          *DEVICE_NAME = GROUP_OUTDOOR_ALL;
          strcpy(SUBMITTED_FUNC_NAME, POWEROFF);
          *standardParams = 3;
          return;
      }
    case CLIENT_NODE_INDOOR2_RACK:
      switch(CLIENT_BUTTON_INDEX) {
        case 1:
          *ZONE_NAME = INDOOR2;
          *DEVICE_NAME = BEAMER;
          strcpy(SUBMITTED_FUNC_NAME, POWERTOGGLE);
          *standardParams = 3;
          return;
        case 2:
          *ZONE_NAME = OUTDOOR;
          *DEVICE_NAME = DOOR;
          strcpy(SUBMITTED_FUNC_NAME, POWERON);
          *standardParams = 3;
          return;
        case 3:
          *ZONE_NAME = INDOOR2;
          *DEVICE_NAME = JUPITER;
          strcpy(SUBMITTED_FUNC_NAME, VOLUME_UP);
          *standardParams = 3;
          return;
      }
  }
}

*/

void setupApp(){

  server.on("/indoor2/tv/power/toggle", HTTP_GET, [](AsyncWebServerRequest *request){
    fire(INDOOR2, TV, POWERTOGGLE); request->send(200, "text/plain", "ACK");
  });

  server.on("/judge", HTTP_GET, [](AsyncWebServerRequest *request){
    
    uint8_t standardParams = 0;
    uint8_t ZONE_NAME, DEVICE_NAME;
    char* SUBMITTED_FUNC_NAME;
    uint8_t CLIENT_NODE = CLIENT_NODE_OTHER;
    int16_t CLIENT_BUTTON_INDEX = -1;
    uint16_t PUSHDURATION = 0;
    uint32_t SUBMITTED_PIN = 0;
    uint16_t judgement;
    //int paramsNr = request->params();


    if(!request->authenticate(http_username, http_password))
       return request->requestAuthentication(NULL,false); // force basic auth
        
    //Serial.println(paramsNr);
 
    for(int i=0;i<request->params();i++){
 
        AsyncWebParameter* p = request->getParam(i);
        if(p->name() == "zone") {
          if(p->value() == "outdoor") { ZONE_NAME = OUTDOOR; standardParams++; continue; }
          if(p->value() == "indoor1") { ZONE_NAME = INDOOR1; standardParams++; continue; }
          if(p->value() == "indoor2") { ZONE_NAME = INDOOR2; standardParams++; continue; }
          if(p->value() == "combo")   { ZONE_NAME = COMBO;   standardParams++; continue; }
        }
        if(p->name() == "device") {
          if(p->value() == "light_main")   { DEVICE_NAME = LIGHT_MAIN;   standardParams++; continue; }
          if(p->value() == "light_main2")  { DEVICE_NAME = LIGHT_MAIN2;  standardParams++; continue; }
          if(p->value() == "light_color")  { DEVICE_NAME = LIGHT_COLOR;  standardParams++; continue; }
          if(p->value() == "light_color2") { DEVICE_NAME = LIGHT_COLOR2; standardParams++; continue; }
          if(p->value() == "light_color3") { DEVICE_NAME = LIGHT_COLOR3; standardParams++; continue; }
          if(p->value() == "sound_amp")    { DEVICE_NAME = SOUND_AMP;    standardParams++; continue; }
          if(p->value() == "sound_amp2")   { DEVICE_NAME = SOUND_AMP2;   standardParams++; continue; }
          if(p->value() == "sound_mixer")  { DEVICE_NAME = SOUND_MIXER;  standardParams++; continue; }
          if(p->value() == "subwoofer")    { DEVICE_NAME = SUBWOOFER;    standardParams++; continue; }
          if(p->value() == "door")         { DEVICE_NAME = DOOR;         standardParams++; continue; }
          if(p->value() == "pc")           { DEVICE_NAME = PC;           standardParams++; continue; }
          if(p->value() == "lazer")        { DEVICE_NAME = LAZER;        standardParams++; continue; }
          if(p->value() == "fogmachine")   { DEVICE_NAME = FOGMACHINE;   standardParams++; continue; }
          if(p->value() == "aircon")       { DEVICE_NAME = AIRCON;       standardParams++; continue; }
          if(p->value() == "beamer")       { DEVICE_NAME = BEAMER;       standardParams++; continue; }
          if(p->value() == "tv")           { DEVICE_NAME = TV;           standardParams++; continue; }
          if(p->value() == "mist")         { DEVICE_NAME = MIST;         standardParams++; continue; }
          if(p->value() == "tv")           { DEVICE_NAME = TV;           standardParams++; continue; }
          if(p->value() == "hdmi_switch")  { DEVICE_NAME = HDMI_SWITCH;  standardParams++; continue; }
          if(p->value() == "jupiter")      { DEVICE_NAME = JUPITER;      standardParams++; continue; }
          if(p->value() == "soccer")       { DEVICE_NAME = SOCCER;       standardParams++; continue; }
          if(p->value() == "darts")        { DEVICE_NAME = DARTS;        standardParams++; continue; }
          
          if(p->value() == "group_indoor2_all"){ DEVICE_NAME = GROUP_INDOOR2_ALL; standardParams++; continue; }
          if(p->value() == "group_indoor1_all"){ DEVICE_NAME = GROUP_INDOOR1_ALL; standardParams++; continue; }
          if(p->value() == "group_outdoor_all"){ DEVICE_NAME = GROUP_OUTDOOR_ALL; standardParams++; continue; }
          if(p->value() == "group_indoor_all") { DEVICE_NAME = GROUP_INDOOR_ALL;  standardParams++; continue; }
          if(p->value() == "group_all")        { DEVICE_NAME = GROUP_ALL;         standardParams++; continue; }
        }
        if(p->name() == "func") {
          if(p->value() == "poweron")     { SUBMITTED_FUNC_NAME = strdup(POWERON);     standardParams++; continue; }
          if(p->value() == "poweroff")    { SUBMITTED_FUNC_NAME = strdup(POWEROFF);    standardParams++; continue; }
          if(p->value() == "powertoggle") { SUBMITTED_FUNC_NAME = strdup(POWERTOGGLE); standardParams++; continue; }
          if(p->value() == "temp_up")     { SUBMITTED_FUNC_NAME = strdup(TEMP_UP);     standardParams++; continue; }
          if(p->value() == "temp_down")   { SUBMITTED_FUNC_NAME = strdup(TEMP_DOWN);   standardParams++; continue; }
          if(p->value() == "volume_up")   { SUBMITTED_FUNC_NAME = strdup(VOLUME_UP);   standardParams++; continue; }
          if(p->value() == "volume_down") { SUBMITTED_FUNC_NAME = strdup(VOLUME_DOWN); standardParams++; continue; }
          if(p->value() == "outa_off")    { SUBMITTED_FUNC_NAME = strdup(OUTA_OFF);    standardParams++; continue; }
          if(p->value() == "outa_in1")    { SUBMITTED_FUNC_NAME = strdup(OUTA_IN1);    standardParams++; continue; }
          if(p->value() == "outa_in2")    { SUBMITTED_FUNC_NAME = strdup(OUTA_IN2);    standardParams++; continue; }
          if(p->value() == "outa_in3")    { SUBMITTED_FUNC_NAME = strdup(OUTA_IN3);    standardParams++; continue; }
          if(p->value() == "outa_in4")    { SUBMITTED_FUNC_NAME = strdup(OUTA_IN4);    standardParams++; continue; }
          if(p->value() == "outb_off")    { SUBMITTED_FUNC_NAME = strdup(OUTB_OFF);    standardParams++; continue; }
          if(p->value() == "outb_in1")    { SUBMITTED_FUNC_NAME = strdup(OUTB_IN1);    standardParams++; continue; }
          if(p->value() == "outb_in2")    { SUBMITTED_FUNC_NAME = strdup(OUTB_IN2);    standardParams++; continue; }
          if(p->value() == "outb_in3")    { SUBMITTED_FUNC_NAME = strdup(OUTB_IN3);    standardParams++; continue; }
          if(p->value() == "outb_in4")    { SUBMITTED_FUNC_NAME = strdup(OUTB_IN4);    standardParams++; continue; }
          if(p->value() == "mode")        { SUBMITTED_FUNC_NAME = strdup(MODE);        standardParams++; continue; }
          if(p->value() == "shutdown")    { SUBMITTED_FUNC_NAME = strdup(SHUTDOWN);    standardParams++; continue; }
          if(p->value() == "wakeonlan")   { SUBMITTED_FUNC_NAME = strdup(WAKEONLAN);   standardParams++; continue; }
          if(p->value() == "toggle")      { SUBMITTED_FUNC_NAME = strdup(TOGGLE);      standardParams++; continue; }

        }
        if(p->name() == "client") {
          if(p->value() == "outdoor_console")  { CLIENT_NODE = CLIENT_NODE_OUTDOOR_CONSOLE;  continue; }
          if(p->value() == "outdoor_irtrans")  { CLIENT_NODE = CLIENT_NODE_OUTDOOR_IRTRANS;  continue; }
          if(p->value() == "indoor1_entrance") { CLIENT_NODE = CLIENT_NODE_INDOOR1_ENTRANCE; continue; }
          if(p->value() == "indoor2_entrance") { CLIENT_NODE = CLIENT_NODE_INDOOR2_ENTRANCE; continue; }
          if(p->value() == "indoor2_console")  { CLIENT_NODE = CLIENT_NODE_INDOOR2_CONSOLE;  continue; }
          if(p->value() == "indoor2_rack")     { CLIENT_NODE = CLIENT_NODE_INDOOR2_RACK;     continue; }
        }
        if(p->name() == "push_duration") {
          PUSHDURATION = atoi( p->value().c_str() ); continue;
        }
        if(p->name() == "pin") {
          SUBMITTED_PIN = atoi( p->value().c_str() ); continue;
        }
        if(p->name() == "button_index") {
          CLIENT_BUTTON_INDEX = atoi( p->value().c_str() ); continue;
        }
        /*
        Serial.print("Param name: ");
        Serial.println(p->name());
        Serial.print("Param value: ");
        Serial.println(p->value());
        Serial.println("------");
        */
        
    }

    // TODO move this to function and override variables
    //mapButtonIndexToParams(CLIENT_NODE, CLIENT_BUTTON_INDEX, &ZONE_NAME, &DEVICE_NAME, SUBMITTED_FUNC_NAME, &standardParams);

    if(CLIENT_BUTTON_INDEX >= 0) {
      switch(CLIENT_NODE) {
        case CLIENT_NODE_INDOOR1_ENTRANCE:
          switch(CLIENT_BUTTON_INDEX) {
            case D1:
              ZONE_NAME = COMBO;
              DEVICE_NAME = GROUP_INDOOR_ALL;
              SUBMITTED_FUNC_NAME = strdup(POWEROFF);
              standardParams = 3;
              break;
            case D2:
              ZONE_NAME = COMBO;
              DEVICE_NAME = GROUP_OUTDOOR_ALL;
              SUBMITTED_FUNC_NAME = strdup(POWEROFF);
              standardParams = 3;
              break;
            case D3:
              ZONE_NAME = OUTDOOR;
              DEVICE_NAME = LIGHT_MAIN;
              SUBMITTED_FUNC_NAME = strdup(POWERTOGGLE);
              standardParams = 3;
              break;
            case D4:
              ZONE_NAME = OUTDOOR;
              DEVICE_NAME = LIGHT_MAIN2;
              SUBMITTED_FUNC_NAME = strdup(POWERTOGGLE);
              standardParams = 3;
              break;
          }
          break;
        case CLIENT_NODE_INDOOR2_RACK:
          switch(CLIENT_BUTTON_INDEX) {
            case 1:
              ZONE_NAME = INDOOR2;
              DEVICE_NAME = BEAMER;
              SUBMITTED_FUNC_NAME = strdup(POWERTOGGLE);
              standardParams = 3;
              break;
            case 2:
              ZONE_NAME = OUTDOOR;
              DEVICE_NAME = DOOR;
              SUBMITTED_FUNC_NAME = strdup(POWERON);
              standardParams = 3;
              break;
            case 3:
              ZONE_NAME = INDOOR2;
              DEVICE_NAME = JUPITER;
              SUBMITTED_FUNC_NAME = strdup(VOLUME_UP);
              standardParams = 3;
              break;
          }
          break;
      }
    }

  
    if(standardParams < 3) {
        request->send(404, "text/html", listValidUrlsHtml());
        return;
    }
    const char* FUNC_NAME = SUBMITTED_FUNC_NAME;
    judgement = judge(ZONE_NAME, DEVICE_NAME, FUNC_NAME, CLIENT_NODE, PUSHDURATION, SUBMITTED_PIN);
    char* jsonReponse;
    switch(judgement) {
      case 200: jsonReponse = "{message: \"ACK\"}"; break;
      case 420: jsonReponse = "{message: \"ERROR_PUSH_DURATION\"}"; break;
      case 403: jsonReponse = "{message: \"ERROR_PINCODE\"}"; break;
    }
    request->send(judgement, "application/json", jsonReponse);
  });
  //server.setAuthentication(http_username, http_password);
  server.begin();
}



void fireCombo(uint8_t ZONE_NAME, uint8_t DEVICE_NAME, const char *FUNC_NAME) {
  if(ZONE_NAME != COMBO) {
    return;  
  }
  if(DEVICE_NAME == GROUP_OUTDOOR_ALL && strcmp(FUNC_NAME, POWEROFF) == 0) {
    fire(OUTDOOR, LIGHT_MAIN,  POWEROFF);
    fire(OUTDOOR, LIGHT_MAIN2, POWEROFF);
    fire(OUTDOOR, LIGHT_COLOR, POWEROFF);
    fire(OUTDOOR, SOUND_AMP,   POWEROFF);
    fire(OUTDOOR, BEAMER,      POWEROFF);
    fire(OUTDOOR, PC,          SHUTDOWN);
    return;
  }
  if(DEVICE_NAME == GROUP_INDOOR1_ALL && strcmp(FUNC_NAME, POWEROFF) == 0) {
    fire(INDOOR1, LIGHT_MAIN,  POWEROFF);
    fire(INDOOR1, LIGHT_COLOR, POWEROFF);
    fire(INDOOR1, LIGHT_COLOR2,POWEROFF);
    fire(INDOOR1, SOUND_AMP,   POWEROFF);
    return;
  }
  if(DEVICE_NAME == GROUP_INDOOR2_ALL && strcmp(FUNC_NAME, POWEROFF) == 0) {
    fire(INDOOR2, LIGHT_MAIN,  POWEROFF);
    fire(INDOOR2, LIGHT_MAIN2, POWEROFF);
    fire(INDOOR2, LIGHT_COLOR, POWEROFF);
    fire(INDOOR2, LIGHT_COLOR2,POWEROFF);
    fire(INDOOR2, SOUND_AMP,   POWEROFF);
    fire(INDOOR2, SOUND_MIXER, POWEROFF);
    fire(INDOOR2, LAZER,       POWEROFF);
    fire(INDOOR2, FOGMACHINE,  POWEROFF);
    fire(INDOOR2, SOCCER,      POWEROFF);
    fire(INDOOR2, DARTS,       POWEROFF);

    fire(INDOOR2, BEAMER,      POWEROFF);
    fire(INDOOR2, TV,          POWEROFF);
    fire(INDOOR2, AIRCON,      POWEROFF);
    fire(INDOOR2, SUBWOOFER,   POWEROFF);

    return;
  }
  if(DEVICE_NAME == GROUP_INDOOR_ALL && strcmp(FUNC_NAME, POWEROFF) == 0) {
    fireCombo(COMBO, GROUP_INDOOR1_ALL, POWEROFF);
    fireCombo(COMBO, GROUP_INDOOR2_ALL, POWEROFF);
    return;
  }
  if(DEVICE_NAME == GROUP_ALL && strcmp(FUNC_NAME, POWEROFF) == 0) {
    fireCombo(COMBO, GROUP_INDOOR_ALL,  POWEROFF);
    fireCombo(COMBO, GROUP_OUTDOOR_ALL, POWEROFF);
    return;
  }
  
}

bool pushDurationValid(uint16_t PUSHDURATION, uint8_t DEVICE_NAME) {
  if(PUSHDURATION >= 3000) {
    return true;
  }
  switch(DEVICE_NAME) {
    case GROUP_INDOOR2_ALL:
    case GROUP_INDOOR1_ALL:
    case GROUP_OUTDOOR_ALL:
    case GROUP_INDOOR_ALL:
    case GROUP_ALL:
      return false;
  }
  return true;
}

bool pinRequired(uint8_t ZONE_NAME, uint8_t DEVICE_NAME, const char *FUNC_NAME, uint8_t CLIENT_NODE) {
  switch(DEVICE_NAME) {
    case DOOR:
      return true;
  }
  // TODO: check lock status indoor<->outdoor
  return false;
}

bool checkValidPin(uint32_t SUBMITTED_PIN) {
  return (SUBMITTED_PIN == 71777);
}
 
void loopApp(){
  loopFirmwareUploadForm();
  processUrlQue();
}

 void echoUrls() {
  /*
    fire(OUTDOOR, DOOR, POWERON);
    fire(INDOOR2, BEAMER, POWERON);
    fire(INDOOR2, HDMI_SWITCH, OUTA_IN3);
    fire(INDOOR2, AIRCON, MODE);
    fire(OUTDOOR, SOUND_AMP, POWERTOGGLE);
    fire(INDOOR2, JUPITER, VOLUME_UP);
    fire(OUTDOOR, PC, WAKEONLAN);
    fire(OUTDOOR, PC, VOLUME_UP);
    fire(OUTDOOR, PC, SHUTDOWN);
   */
}

String listValidUrlsHtml() {
  String markup = "<h1>gTown JUDGE</h1>\n";
  markup += "<a href='/judge?zone=outdoor&device=light_main&func=poweroff'>outdoor light_main poweroff<br>\n";
  markup += "<a href='/judge?zone=outdoor&device=light_main&func=poweron'>outdoor light_main poweron<br>\n";
  markup += "<a href='/judge?zone=outdoor&device=light_main&func=powertoggle'>outdoor light_main powertoggle<br>\n";
  markup += "<a href='/judge?zone=indoor2&device=airconditioning&func=temperatureup'>indoor2 airconditioning temperatureup<br>\n";
  markup += "<a href='/judge?zone=indoor2&device=jupiter&func=volumeup'>indoor2 jupiter volumeup<br>\n";
  return markup;
}

void setupFirmwareUploadForm() {

// Simple Firmware Update Form
  server.on("/update", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", "<form method='POST' action='/update' enctype='multipart/form-data'><input type='file' name='update'><input type='submit' value='Update'></form>");
  });
  server.on("/update", HTTP_POST, [](AsyncWebServerRequest *request){
    shouldReboot = !Update.hasError();
    AsyncWebServerResponse *response = request->beginResponse(200, "text/plain", shouldReboot?"UPDATE SUCCESS":"UPDATE FAIL");
    response->addHeader("Connection", "close");
    request->send(response);
    
  },[](AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final){
    if(!index){
      Serial.printf("Update Start: %s\n", filename.c_str());
      Update.runAsync(true);
      if(!Update.begin((ESP.getFreeSketchSpace() - 0x1000) & 0xFFFFF000)){
        Update.printError(Serial);
      }
    }
    if(!Update.hasError()){
      if(Update.write(data, len) != len){
        Update.printError(Serial);
      }
    }
    if(final){
      if(Update.end(true)){
        Serial.printf("Update Success: %uB\n", index+len);
      } else {
        Update.printError(Serial);
      }
    }
  });
}

void loopFirmwareUploadForm(){
  if(!shouldReboot){
    return;
  }
  Serial.println("Rebooting...");
  delay(100);
  ESP.restart();
}
