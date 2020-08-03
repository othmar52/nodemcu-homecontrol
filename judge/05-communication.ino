 

// example url request for ez-control XS1
// http://10.0.1.118/control?callback=callback&cmd=set_state_actuator&number=7&function=1&nocache=1595754581419

// example url request for irtrans (NodeMCU)
// http://10.0.1.143/aircondition/power/on


// example shutdown outdoor pc
// http://10.0.1.146:8000/?shutdown=1



void fire(uint8_t ZONE_NAME, uint8_t DEVICE_NAME, const char *FUNC_NAME) {
  String url;

  // tasmotas
  if(
    (ZONE_NAME == OUTDOOR && DEVICE_NAME == LIGHT_MAIN) ||
    (ZONE_NAME == OUTDOOR && DEVICE_NAME == LIGHT_MAIN2) ||
    (ZONE_NAME == OUTDOOR && DEVICE_NAME == LIGHT_COLOR) ||
    (ZONE_NAME == OUTDOOR && DEVICE_NAME == SOUND_AMP) ||
    
    (ZONE_NAME == INDOOR1 && DEVICE_NAME == LIGHT_MAIN) ||
    (ZONE_NAME == INDOOR1 && DEVICE_NAME == LIGHT_COLOR) ||
    (ZONE_NAME == INDOOR1 && DEVICE_NAME == LIGHT_COLOR2) ||
    (ZONE_NAME == INDOOR1 && DEVICE_NAME == SOUND_AMP) ||
    
    (ZONE_NAME == INDOOR2 && DEVICE_NAME == LIGHT_MAIN) ||
    (ZONE_NAME == INDOOR2 && DEVICE_NAME == LIGHT_MAIN2) ||
    (ZONE_NAME == INDOOR2 && DEVICE_NAME == LIGHT_COLOR) ||
    (ZONE_NAME == INDOOR2 && DEVICE_NAME == LIGHT_COLOR2) ||
    (ZONE_NAME == INDOOR2 && DEVICE_NAME == SOUND_AMP) ||
    (ZONE_NAME == INDOOR2 && DEVICE_NAME == SOUND_MIXER) ||
    (ZONE_NAME == INDOOR2 && DEVICE_NAME == LAZER) ||
    (ZONE_NAME == INDOOR2 && DEVICE_NAME == FOGMACHINE) ||
    (ZONE_NAME == INDOOR2 && DEVICE_NAME == SOCCER) ||
    (ZONE_NAME == INDOOR2 && DEVICE_NAME == DARTS)
  ) {
    singleUrlCall( tasmotaStatusUrl(ZONE_NAME, DEVICE_NAME) );
    singleUrlCall( tasmotaUrl(ZONE_NAME, DEVICE_NAME, FUNC_NAME) ); return;
  }

  // nodemcu
  if(
    (ZONE_NAME == OUTDOOR && DEVICE_NAME == DOOR)
  ) {
    singleUrlCall( nodeMcuUrl(ZONE_NAME, DEVICE_NAME, FUNC_NAME) ); return;
  }

  // ezcontrol (will be removed)
  if(
    (ZONE_NAME == OUTDOOR && DEVICE_NAME == SOUND_AMP)
  ) {
    debug("ez control disabled");
    return;
    //singleUrlCall( ezControlUrl(ZONE_NAME, DEVICE_NAME, FUNC_NAME) ); return;
  }

  // irtrans single url
  if(
    (ZONE_NAME == INDOOR2 && DEVICE_NAME == AIRCON) ||
    (ZONE_NAME == INDOOR2 && DEVICE_NAME == HDMI_SWITCH) ||
    (ZONE_NAME == INDOOR2 && DEVICE_NAME == TV)
  ) {
    singleUrlCall( irTransUrl(ZONE_NAME, DEVICE_NAME, FUNC_NAME) ); return;
  }

  // irtrans double url
  if(
    (ZONE_NAME == OUTDOOR && DEVICE_NAME == BEAMER) ||
    (ZONE_NAME == INDOOR2 && DEVICE_NAME == BEAMER)
  ) {
    doubleUrlCall( irTransUrl(ZONE_NAME, DEVICE_NAME, FUNC_NAME), 4000 ); return;
  }

  // jupiter
  if(ZONE_NAME == INDOOR2 && DEVICE_NAME == JUPITER) {
    singleUrlCall( jupiterUrl(ZONE_NAME, DEVICE_NAME, FUNC_NAME) ); return;
  }

  // pc
  if(ZONE_NAME == OUTDOOR && DEVICE_NAME == PC) {
    if(FUNC_NAME == WAKEONLAN) {
      fireWakeOnLan(MAC_OUTDOOR_PC);
      return;
    }
    singleUrlCall( pcUrl(ZONE_NAME, DEVICE_NAME, FUNC_NAME) ); return;
  }
  
}

String appendTimestampParam(String inputUrl) {
  return inputUrl + String("&nocache=") + String(millis());
}

void singleUrlCall(String url) {
  debug(url);
  addToUrlQue(url);
}

void doubleUrlCall(String url, uint16_t duration) {
  addToUrlQue(url);
  addToUrlQue(url);
  //delay(duration);
  debug(url);
}
