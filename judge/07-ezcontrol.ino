 
// ez-control XS 1 
String ezControlUrl(uint8_t ZONE_NAME, uint8_t DEVICE_NAME, const char *FUNC_NAME) {
  return appendTimestampParam(
    String(HTTP_PREFIX) +
    String(IP_EZCONTROL) +
    String("/control?callback=callback&cmd=set_state_actuator&number=") +
    ezControlActuator(ZONE_NAME, DEVICE_NAME) +
    String("&function=") +
    ezControlFuncParam(FUNC_NAME)
  );
}

String ezControlFuncParam(const char *FUNC_NAME) {
  if(strcmp(FUNC_NAME, POWERON) == 0) {     return String((char *)EZCONTROL_FUNC_ON); }
  if(strcmp(FUNC_NAME, POWEROFF) == 0) {     return String((char *)EZCONTROL_FUNC_OFF); }
  return String((char *)EZCONTROL_FUNC_TOGGLE);
}

String ezControlActuator(uint8_t ZONE_NAME, uint8_t DEVICE_NAME){
  if(ZONE_NAME == OUTDOOR && DEVICE_NAME == DOOR) {
    return EZCONTROL_ACTUATOR_ZONE_OUTDOOR_DOOR;
  }
  if(ZONE_NAME == INDOOR2 && DEVICE_NAME == SOCCER) {
    return EZCONTROL_ACTUATOR_ZONE_INDOOR2_LIGHT_SOCCER;
  }

  if(ZONE_NAME == INDOOR1 && DEVICE_NAME == LIGHT_MAIN) {
    return EZCONTROL_ACTUATOR_ZONE_INDOOR1_LIGHT_MAIN;
  }
  return String("invalid");
}
