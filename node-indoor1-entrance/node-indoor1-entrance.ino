
#include "config.local.h"
#include "config.h"

char *clientIdentifier = strdup(CLIENT_IDENTIFIER_NODE_INDOOR1_ENTRANCE);

const int buzzerPin = D8;
const int doorRelaisPin = D7;

void setup() {
  Serial.begin(19200);
  setupNetwork();
  setupApp();
}

void loop() {
  loopNetwork();
  loopApp();
}

void debug(String msg) {
  Serial.println(msg);
}
