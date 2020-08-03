/**
 * relais RY5W-K (bottom view)
 * 
 *        1         4    6    8
 *        |         |    |    |
 *       -----------------------
 *       |                     |
 *       |                     |
 *       |                     |
 *       |                     |
 *       -----------------------
 *        |         |    |    |
 *        16       13    11   9
 *        
 *        relais PIN -> target
 *           1  -> arduino pin D8
 *           16 -> arduino ground
 *           13 -> potential free circuit A pin 1
 *           9  -> potential free circuit A pin 2
 *           4  -> potential free circuit B pin 1
 *           8  -> potential free circuit B pin 2
 *        
 *  
 */

unsigned long releaseRelayAtMillisecond = 0;
uint16_t relayHoldDuration = 1000;

void triggerDoorRelay() {
  digitalWrite(doorRelaisPin, HIGH);
  releaseRelayAtMillisecond = millis() + relayHoldDuration;
}


void loopRelayHandling() {
  if(releaseRelayAtMillisecond == 0) {
    return;
  }
  if (millis() < releaseRelayAtMillisecond) {
    return;  
  }
  releaseRelayAtMillisecond = 0;
  digitalWrite(doorRelaisPin, LOW);
}
