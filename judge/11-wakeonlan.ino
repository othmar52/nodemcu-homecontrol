 
#include "WakeOnLan.h"
 
void fireWakeOnLan(byte *macAddress) {
  IPAddress broadcastIp(255, 255, 255, 255);
  WakeOnLan::sendWOL(broadcastIp, UDP, macAddress, sizeof macAddress);
}
