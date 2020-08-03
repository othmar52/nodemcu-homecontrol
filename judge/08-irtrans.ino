 
// irtrans url
String irTransUrl(uint8_t ZONE_NAME, uint8_t DEVICE_NAME, const char *FUNC_NAME) {
  return String(
    String(HTTP_PREFIX) +
    ipForIrTrans(ZONE_NAME) +
    String("/") +
    deviceNameForIrTrans(DEVICE_NAME) +
    String("/") +
    irTransFuncChunk(FUNC_NAME)
  );
}

String ipForIrTrans(uint8_t ZONE_NAME) {
  if(ZONE_NAME == INDOOR2) {
    return String((char *)IP_IRTRANS_INDOOR);
  }
  if(ZONE_NAME == OUTDOOR) {
    return String((char *)IP_IRTRANS_OUTDOOR);
  }
  debug("no match ipForIrTrans()");
}

String deviceNameForIrTrans(uint8_t DEVICE_NAME){
  switch(DEVICE_NAME) {
    case BEAMER:      return String((char *)IRTRANS_DEVICENAME_BEAMER);
    case AIRCON:      return String((char *)IRTRANS_DEVICENAME_AIRCON);
    case TV:          return String((char *)IRTRANS_DEVICENAME_TV);
    case HDMI_SWITCH: return String((char *)IRTRANS_DEVICENAME_HDMI_SWITCH);
  }
  debug("no match deviceNameForIrTrans()");
}

String irTransFuncChunk(const char *FUNC_CHUNK) {
  if(strcmp(FUNC_CHUNK, POWERON) == 0) {  return String((char *)IRTRANS_FUNC_POWERON); }
  if(strcmp(FUNC_CHUNK, POWEROFF) == 0) { return String((char *)IRTRANS_FUNC_POWEROFF); }

  if(strcmp(FUNC_CHUNK, TEMP_UP) == 0) { return String((char *)IRTRANS_FUNC_TEMP_UP); }
  if(strcmp(FUNC_CHUNK, TEMP_DOWN) == 0) { return String((char *)IRTRANS_FUNC_TEMP_DOWN); }
  if(strcmp(FUNC_CHUNK, MODE) == 0) { return String((char *)IRTRANS_FUNC_MODE); }

  if(strcmp(FUNC_CHUNK, OUTA_OFF) == 0) { return String((char *)IRTRANS_FUNC_OUTA_OFF); }
  if(strcmp(FUNC_CHUNK, OUTA_IN1) == 0) { return String((char *)IRTRANS_FUNC_OUTA_IN1); }
  if(strcmp(FUNC_CHUNK, OUTA_IN2) == 0) { return String((char *)IRTRANS_FUNC_OUTA_IN2); }
  if(strcmp(FUNC_CHUNK, OUTA_IN3) == 0) { return String((char *)IRTRANS_FUNC_OUTA_IN3); }
  if(strcmp(FUNC_CHUNK, OUTA_IN4) == 0) { return String((char *)IRTRANS_FUNC_OUTA_IN4); }
  
  if(strcmp(FUNC_CHUNK, OUTB_OFF) == 0) { return String((char *)IRTRANS_FUNC_OUTB_OFF); }
  if(strcmp(FUNC_CHUNK, OUTB_IN1) == 0) { return String((char *)IRTRANS_FUNC_OUTB_IN1); }
  if(strcmp(FUNC_CHUNK, OUTB_IN2) == 0) { return String((char *)IRTRANS_FUNC_OUTB_IN2); }
  if(strcmp(FUNC_CHUNK, OUTB_IN3) == 0) { return String((char *)IRTRANS_FUNC_OUTB_IN3); }
  if(strcmp(FUNC_CHUNK, OUTB_IN4) == 0) { return String((char *)IRTRANS_FUNC_OUTB_IN4); }


  return String((char *)IRTRANS_FUNC_POWERTOGGLE);
}
