 
// pc url (python script)
String pcUrl(uint8_t ZONE_NAME, uint8_t DEVICE_NAME, const char *FUNC_NAME) {
  return String(
    String(HTTP_PREFIX) +
    ipForPc(ZONE_NAME, DEVICE_NAME) +
    String("/?") +
    pcFuncParam(FUNC_NAME)
  );
}

String ipForPc(uint8_t ZONE_NAME, uint8_t DEVICE_NAME) {
  if(ZONE_NAME == OUTDOOR && DEVICE_NAME == PC) {
    return String((char *)IP_OUTDOOR_PC);
  }
  debug("no match ipForPc()");
}

String pcFuncParam(const char *FUNC_NAME) {
  if(strcmp(FUNC_NAME, VOLUME_UP) == 0) {     return String((char *)PC_FUNC_VOLUME_UP); }
  if(strcmp(FUNC_NAME, VOLUME_DOWN) == 0) {   return String((char *)PC_FUNC_VOLUME_DOWN); }
  if(strcmp(FUNC_NAME, SHUTDOWN) == 0) {     return String((char *)PC_FUNC_SHUTDOWN); }
  debug("no match jupiterFuncParam()");
}
