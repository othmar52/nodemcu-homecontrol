 
// tasmota url
String tasmotaUrl(uint8_t ZONE_NAME, uint8_t DEVICE_NAME, const char *FUNC_NAME) {
  return appendTimestampParam(
    String(HTTP_PREFIX) +
    ipForTasmota(ZONE_NAME, DEVICE_NAME) +
    String("/cm?cmnd=") +
    tasmotaFuncParam(FUNC_NAME) +
    tasmotaCredentialsParams()
  );
}
String tasmotaStatusUrl(uint8_t ZONE_NAME, uint8_t DEVICE_NAME) {
  return appendTimestampParam(
    String(HTTP_PREFIX) +
    ipForTasmota(ZONE_NAME, DEVICE_NAME) +
    String("/?m=1") +
    tasmotaCredentialsParams()
  );
}

String ipForTasmota(uint8_t ZONE_NAME, uint8_t DEVICE_NAME) {
  if(ZONE_NAME == OUTDOOR) {
    switch(DEVICE_NAME) {
      case LIGHT_MAIN:  return String((char *)IP_TASMOTA_01_OUTDOOR_LIGHT_TABLE);
      case LIGHT_MAIN2: return String((char *)IP_TASMOTA_02_OUTDOOR_LIGHT_DOORSPOT);
      case LIGHT_COLOR: return String((char *)IP_TASMOTA_03_OUTDOOR_LIGHT_LEDWALL);
      case SOUND_AMP:   return String((char *)IP_TASMOTA_04_OUTDOOR_SOUND_AMP);
      // door gets tasmota??? 
    }
  }
  
  if(ZONE_NAME == INDOOR1) {
    switch(DEVICE_NAME) {
      case LIGHT_MAIN:  return String((char *)IP_TASMOTA_05_INDOOR1_LIGHT_MAIN);
      case LIGHT_COLOR: return String((char *)IP_TASMOTA_06_INDOOR1_LIGHT_COLOR1);
      case LIGHT_COLOR2:return String((char *)IP_TASMOTA_07_INDOOR1_LIGHT_COLOR2);
      case SOUND_AMP:   return String((char *)IP_TASMOTA_08_INDOOR1_SOUND_AMP);
    }
  }
  
  if(ZONE_NAME == INDOOR2) {
    switch(DEVICE_NAME) {
      case LIGHT_MAIN:  return String((char *)IP_TASMOTA_09_INDOOR2_LIGHT_MAIN);
      case LIGHT_MAIN2: return String((char *)IP_TASMOTA_10_INDOOR2_LIGHT_MAIN2);
      case LIGHT_COLOR: return String((char *)IP_TASMOTA_11_INDOOR2_LIGHT_COLOR1);
      case LIGHT_COLOR2:return String((char *)IP_TASMOTA_12_INDOOR2_LIGHT_COLOR2);
      case SOUND_AMP:   return String((char *)IP_TASMOTA_13_INDOOR2_SOUND_AMP);
      case SOUND_MIXER: return String((char *)IP_TASMOTA_14_INDOOR2_SOUND_MIXER);
      case LAZER:       return String((char *)IP_TASMOTA_15_INDOOR2_LAZER);
      case FOGMACHINE:  return String((char *)IP_TASMOTA_16_INDOOR2_FOGMACHINE);
      case SOCCER:      return String((char *)IP_TASMOTA_17_INDOOR2_SOCCER);
      case DARTS:       return String((char *)IP_TASMOTA_18_INDOOR2_DARTS);
    }
  }

  debug("no match ipForTasmota()");
}

String tasmotaFuncParam(const char *FUNC_NAME) {
  if(strcmp(FUNC_NAME, POWERON) == 0) {     return String((char *)TASMOTA_FUNC_POWERON); }
  if(strcmp(FUNC_NAME, POWEROFF) == 0) {     return String((char *)TASMOTA_FUNC_POWEROFF); }
  return String((char *)TASMOTA_FUNC_POWERTOGGLE);
}

// tasmota has no support for basic auth...
String tasmotaCredentialsParams() {
  return String( "&user=" + String(http_username) + "&password=" + String(http_password));
}
