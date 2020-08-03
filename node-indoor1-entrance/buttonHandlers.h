 
void handleButtonGoesDown(byte buttonPin) {
  BUTTON_EVENTPROCESSED[buttonPin] = false;
  switch(buttonPin) {
    case D1:
    case D2:
      buzzerStartMillisecond = millis();

      // unfortunately we have a problem when multiple buttons gets pushed within the same milisecond
      // maybe this is not a problem in real life. but its some kind of highly possible on D1 + D2
      // low budget solution : modify BUTTON_LASTDOWN by 1 millisecond
      // TODO: find a proper solution (maybe with url queue?)
      //if(BUTTON_LASTDOWN[D1] == BUTTON_LASTDOWN[D2]) {
      //  BUTTON_LASTDOWN[D1]-=2;
      //}
      return;
  }
}

void handleButtonRelease(byte buttonPin, int holdTime) { 
  BUTTON_EVENTPROCESSED[buttonPin] = true;
  switch(buttonPin) {
    case D1:
    case D2:
      // no message to judge (handeled by handleButtonDown() )
      // but stop buzzer in case the 2nd buzzer pin currently does not use buzzer
      if(BUTTON_ISPRESSED[(buttonPin == D2) ? D1 : D2] == false && millis() - BUTTON_LASTDOWN[buttonPin] < longPress) {
        buzzerStartMillisecond = 0;
        digitalWrite(buzzerPin, LOW);
      }
      return; 
    case D3:
    case D4:
    case D5:
    case D6:
      messageToJudge(buttonPin, holdTime);
      return; 
  }
  debug("invalid button index " + String(buttonPin));
}

void handleButtonHold(uint8_t buttonPin, int holdTime) {
  switch(buttonPin) {
    case D1:
    case D2:
      // stop buzzer in case the 2nd buzzer pin currently does not use buzzer
      if(holdTime < longPress) {
        return;
      }
      if(BUTTON_EVENTPROCESSED[buttonPin] == false) {
        BUTTON_EVENTPROCESSED[buttonPin] = true;
        messageToJudge(buttonPin, holdTime);
        digitalWrite(buzzerPin, HIGH);
      }
      //delay(1);
  }
  //debug("button hold " + String(buttonPin));
}
