 


#include "config.local.h"
#include "config.h"

char *clientIdentifier = strdup(CLIENT_IDENTIFIER_JUDGE);

void setup() {
  Serial.begin(19200);
  setupNetwork();
  setupApp();
  //echoUrls();
}

void loop() {
  loopNetwork();
  loopApp();
}

void debug(String msg) {
  Serial.println(msg);
}
