
#include <ESP8266HTTPClient.h>


unsigned long lastFiredRequest = 0;
uint8_t pauseBetweenRequests = 400;

void messageToJudge(byte buttonPin, int holdTime) {
  if(strcmp(clientIdentifier, CLIENT_IDENTIFIER_JUDGE) == 0) {
    debug("ABORTING... judge is not allowed to request himself");
    return;
  }
  String judgeUrl = String(HTTP_PREFIX) + String(IP_JUDGE) + "/judge?client="+String(clientIdentifier)+"&button_index=" + String(buttonPin)+"&push_duration=" + String(holdTime);
  debug(judgeUrl);
  addToUrlQue(judgeUrl);
}

void fireUrl(String url) {
  if(WiFi.status() != WL_CONNECTED){
    return;
  }
  lastFiredRequest = millis();
  HTTPClient http;
  http.setReuse(true);
  http.setTimeout(200);

  // Your Domain name with URL path or IP address with path
  http.begin(url.c_str());
  http.setAuthorization(http_username, http_password);
  
  // Send HTTP GET request
  int httpResponseCode = http.GET();
  debug("STATUS " +  String(httpResponseCode));
  
  /*
  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    String payload = http.getString();
    Serial.println(payload);
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  */
  
  // Free resources
  http.end();
}



/**
 *   i have no idea of c++
 *   this is a horrible approach to have something like a queue
 */
int8_t queLength = 0;
String urlque1,urlque2,urlque3,urlque4,urlque5,urlque6,urlque7,urlque8,urlque9,urlque10,
       urlque11,urlque12,urlque13,urlque14,urlque15,urlque16,urlque17,urlque18,urlque19,urlque20,
       urlque21,urlque22,urlque23,urlque24,urlque25,urlque26,urlque27,urlque28,urlque29,urlque30;


void addToUrlQue(String urlToAdd) {

  if(urlque1 == "") { urlque1 = urlToAdd; queLength++; return; }
  if(urlque2 == "") { urlque2 = urlToAdd; queLength++; return; }
  if(urlque3 == "") { urlque3 = urlToAdd; queLength++; return; }
  if(urlque4 == "") { urlque4 = urlToAdd; queLength++; return; }
  if(urlque5 == "") { urlque5 = urlToAdd; queLength++; return; }
  if(urlque6 == "") { urlque6 = urlToAdd; queLength++; return; }
  if(urlque7 == "") { urlque7 = urlToAdd; queLength++; return; }
  if(urlque8 == "") { urlque8 = urlToAdd; queLength++; return; }
  if(urlque9 == "") { urlque9 = urlToAdd; queLength++; return; }
  if(urlque10 == "") { urlque10 = urlToAdd; queLength++; return; }
  if(urlque11 == "") { urlque11 = urlToAdd; queLength++; return; }
  if(urlque12 == "") { urlque12 = urlToAdd; queLength++; return; }
  if(urlque13 == "") { urlque13 = urlToAdd; queLength++; return; }
  if(urlque14 == "") { urlque14 = urlToAdd; queLength++; return; }
  if(urlque15 == "") { urlque15 = urlToAdd; queLength++; return; }
  if(urlque16 == "") { urlque16 = urlToAdd; queLength++; return; }
  if(urlque17 == "") { urlque17 = urlToAdd; queLength++; return; }
  if(urlque18 == "") { urlque18 = urlToAdd; queLength++; return; }
  if(urlque19 == "") { urlque19 = urlToAdd; queLength++; return; }
  if(urlque20 == "") { urlque20 = urlToAdd; queLength++; return; }
  if(urlque21 == "") { urlque21 = urlToAdd; queLength++; return; }
  if(urlque22 == "") { urlque22 = urlToAdd; queLength++; return; }
  if(urlque23 == "") { urlque23 = urlToAdd; queLength++; return; }
  if(urlque24 == "") { urlque24 = urlToAdd; queLength++; return; }
  if(urlque25 == "") { urlque25 = urlToAdd; queLength++; return; }
  if(urlque26 == "") { urlque26 = urlToAdd; queLength++; return; }
  if(urlque27 == "") { urlque27 = urlToAdd; queLength++; return; }
  if(urlque28 == "") { urlque28 = urlToAdd; queLength++; return; }
  if(urlque29 == "") { urlque29 = urlToAdd; queLength++; return; }
  if(urlque30 == "") { urlque30 = urlToAdd; queLength++; return; }

}

void processUrlQue() {
  if(queLength < 1) {
    queLength = 0;
    return;  
  }
  if(millis() - lastFiredRequest < pauseBetweenRequests) {
    return;
  }

  if(urlque1 != "") {fireUrl(urlque1); urlque1=""; queLength--; return; }
  if(urlque2 != "") {fireUrl(urlque2); urlque2=""; queLength--; return; }
  if(urlque3 != "") {fireUrl(urlque3); urlque3=""; queLength--; return; }
  if(urlque4 != "") {fireUrl(urlque4); urlque4=""; queLength--; return; }
  if(urlque5 != "") {fireUrl(urlque5); urlque5=""; queLength--; return; }
  if(urlque6 != "") {fireUrl(urlque6); urlque6=""; queLength--; return; }
  if(urlque7 != "") {fireUrl(urlque7); urlque7=""; queLength--; return; }
  if(urlque8 != "") {fireUrl(urlque8); urlque8=""; queLength--; return; }
  if(urlque9 != "")  {fireUrl(urlque9); urlque9=""; queLength--; return; }
  if(urlque10 != "") {fireUrl(urlque10); urlque10=""; queLength--; return; }
  if(urlque11 != "") {fireUrl(urlque11); urlque11=""; queLength--; return; }
  if(urlque12 != "") {fireUrl(urlque12); urlque12=""; queLength--; return; }
  if(urlque13 != "") {fireUrl(urlque13); urlque13=""; queLength--; return; }
  if(urlque14 != "") {fireUrl(urlque14); urlque14=""; queLength--; return; }
  if(urlque15 != "") {fireUrl(urlque15); urlque15=""; queLength--; return; }
  if(urlque16 != "") {fireUrl(urlque16); urlque16=""; queLength--; return; }
  if(urlque17 != "") {fireUrl(urlque17); urlque17=""; queLength--; return; }
  if(urlque18 != "") {fireUrl(urlque18); urlque18=""; queLength--; return; }
  if(urlque19 != "") {fireUrl(urlque19); urlque19=""; queLength--; return; }
  if(urlque20 != "") {fireUrl(urlque20); urlque20=""; queLength--; return; }
  if(urlque21 != "") {fireUrl(urlque21); urlque21=""; queLength--; return; }
  if(urlque22 != "") {fireUrl(urlque22); urlque22=""; queLength--; return; }
  if(urlque23 != "") {fireUrl(urlque23); urlque23=""; queLength--; return; }
  if(urlque24 != "") {fireUrl(urlque24); urlque24=""; queLength--; return; }
  if(urlque25 != "") {fireUrl(urlque25); urlque25=""; queLength--; return; }
  if(urlque26 != "") {fireUrl(urlque26); urlque26=""; queLength--; return; }
  if(urlque27 != "") {fireUrl(urlque27); urlque27=""; queLength--; return; }
  if(urlque28 != "") {fireUrl(urlque28); urlque28=""; queLength--; return; }
  if(urlque29 != "") {fireUrl(urlque29); urlque29=""; queLength--; return; }
  if(urlque30 != "") {fireUrl(urlque30); urlque30=""; queLength--; return; }

}



/*

// http://10.0.1.77/judge?client=indoor1_entrance&zone=outdoor&device=door&func=toggle&push_duration=3000&pin=71777

#define URLQUE(x) (sizeof(x) /  sizeof(x[0]))

int8_t queLength = 0;

char emptyUrl[140]; // maximum length of a single url
char *urls[] = {
  "",
  "",
  "",
  ""
};

void addToUrlQue(String urlToAdd) {
  //char urlCopy[140];
  debug(" before addToUrlQue() len= " + String(queLength));
  debugQue();
  char *urlAsChar;
  for (int i = 0; i < URLQUE(urls); i++) {
    if(strcmp(urls[i], "") == 0) {
      urlToAdd.toCharArray(urlAsChar, 140);
      urls[i] = urlAsChar;
      queLength++;
      return;
    }
  }
}

void processUrlQue() {
  if(queLength < 1) {
    queLength = 0;
    return;  
  }
  debug(" before processUrlQue() len= " + String(queLength));
  debugQue();
  char *tempUrl;
  for (int i = 0; i < URLQUE(urls); i++) {
    if(strcmp(urls[i], "") != 0) {
      tempUrl = urls[i];
      urls[i][0] = '\0';
      queLength--;
      fireUrl(String(tempUrl));
      return;
    }
  }
  debug(" after processUrlQue() len= " + String(queLength));
  debugQue();
}

void debugQue() {
 Serial.println("----------------------------");
 for (int i = 0; i < URLQUE(urls); i++) {
   if(strcmp(urls[i], "") != 0) {
     Serial.println(urls[i]);
   }
 }
 Serial.println("----------------------------");
}


*/
