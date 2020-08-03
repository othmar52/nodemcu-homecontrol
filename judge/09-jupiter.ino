 
// jupiter url
String jupiterUrl(uint8_t ZONE_NAME, uint8_t DEVICE_NAME, const char *FUNC_NAME) {
  return appendTimestampParam(
    String(HTTP_PREFIX) +
    ipForJupiter(ZONE_NAME, DEVICE_NAME) +
    String("/cgi/mars_cgi?file=arcweb1&data=") +
    jupiterFuncParam(FUNC_NAME)
  );
}

String ipForJupiter(uint8_t ZONE_NAME, uint8_t DEVICE_NAME) {
  if(ZONE_NAME == INDOOR2 && DEVICE_NAME == JUPITER) {
    return String((char *)IP_JUPITER);
  }
  debug("no match ipForJupiter()");
}

String jupiterFuncParam(const char *FUNC_NAME) {
  if(strcmp(FUNC_NAME, VOLUME_UP) == 0) {   return String((char *)JUPITER_FUNC_VOLUME_UP); }
  if(strcmp(FUNC_NAME, VOLUME_DOWN) == 0) { return String((char *)JUPITER_FUNC_VOLUME_DOWN); }
  debug("no match jupiterFuncParam()");
}
