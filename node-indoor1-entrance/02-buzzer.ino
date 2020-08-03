

unsigned long buzzerStartMillisecond = 0;

// in case something goes wrong ensure the buzzer shuts up
const uint16_t buzzerPanicInterval = 7; // [seconds]
byte lastBuzzerPanicState = LOW;
unsigned long lastBuzzerPanicCheck = 0;


void loopBuzzer() {
  // avoid unstoppable buzzer activity
  if(millis() - lastBuzzerPanicCheck > buzzerPanicInterval*1000) {
    const byte currentBuzzerState = digitalRead(buzzerPin);
    if(currentBuzzerState == HIGH && lastBuzzerPanicState == HIGH) {
      // mute buzzer
      digitalWrite(buzzerPin, LOW);
    }
    lastBuzzerPanicState = currentBuzzerState;
    lastBuzzerPanicCheck = millis();
  }

  if(buzzerStartMillisecond == 0) {
    return;  
  }
  const unsigned long countdown = millis() - buzzerStartMillisecond;
  const uint16_t beepduration = 100;
  const uint16_t pauseduration = 100;
  const uint16_t successduration = 600;
  const uint16_t sec1 = 1000;
  const uint16_t sec2 = 2000;
  const uint16_t sec3 = 3000;
  switch(countdown) {
    case 0:
    case beepduration + pauseduration:
    case beepduration*2 + pauseduration*2:
    case sec1:
    case sec1 + beepduration + pauseduration:
    case sec2:
    case sec3:
       digitalWrite(buzzerPin, HIGH);
       break;
    case beepduration:
    case beepduration * 2 + pauseduration:
    case beepduration * 3 + pauseduration * 2:
    case sec1 + beepduration:
    case sec1 + beepduration*2 + pauseduration:
    case sec2 + beepduration:
    case sec3 + successduration:
       digitalWrite(buzzerPin, LOW);
       break;
  }
  if(countdown > sec3 + successduration) {
    buzzerStartMillisecond = 0;
    digitalWrite(buzzerPin, LOW);
  }
}
