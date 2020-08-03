 
// irtrans url
String nodeMcuUrl(uint8_t ZONE_NAME, uint8_t DEVICE_NAME, const char *FUNC_NAME) {
  return String(
    String(HTTP_PREFIX) +
    ipForNodeMcu(ZONE_NAME, DEVICE_NAME) +
    String("/") +
    deviceNameForNodeMcu(DEVICE_NAME) +
    String("/") +
    nodeMcuFuncChunk(FUNC_NAME)
  );
}

String ipForNodeMcu(uint8_t ZONE_NAME, uint8_t DEVICE_NAME) {
  if(ZONE_NAME == OUTDOOR && DEVICE_NAME == DOOR) {
    return String((char *)IP_NODEMCU_INDOOR1_ENTRANCE);
  }
  debug("no match ipForNodeMcu()");
  return "invalid";
}

String deviceNameForNodeMcu(uint8_t DEVICE_NAME){
  switch(DEVICE_NAME) {
    case DOOR: return String((char *)NODEMCU_DEVICENAME_DOOR);
  }
  debug("no match deviceNameForNodeMcu()");
  return "invalid";
}

String nodeMcuFuncChunk(const char *FUNC_CHUNK) {
  if(strcmp(FUNC_CHUNK, TOGGLE) == 0) { return String((char *)NODEMCU_FUNC_TOGGLE); }
  debug("no match nodeMcuFuncChunk()");
  return "invalid";
}
