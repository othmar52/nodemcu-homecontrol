



const uint16_t longPress = 3000; // milliseconds

const uint8_t CLIENT_NODE_OUTDOOR_CONSOLE = 0;
const uint8_t CLIENT_NODE_OUTDOOR_IRTRANS = 1;
const uint8_t CLIENT_NODE_INDOOR1_ENTRANCE = 2;
const uint8_t CLIENT_NODE_INDOOR2_ENTRANCE = 3;
const uint8_t CLIENT_NODE_INDOOR2_CONSOLE = 4;
const uint8_t CLIENT_NODE_INDOOR2_RACK = 5;
const uint8_t CLIENT_NODE_OTHER = 6;

const char CLIENT_IDENTIFIER_JUDGE[6]                  = "judge";
const char CLIENT_IDENTIFIER_NODE_OUTDOOR_CONSOLE[16]  = "outdoor_console";
const char CLIENT_IDENTIFIER_NODE_OUTDOOR_IRTRANS[16]  = "outdoor_irtrans";
const char CLIENT_IDENTIFIER_NODE_INDOOR1_ENTRANCE[17] = "indoor1_entrance";
const char CLIENT_IDENTIFIER_NODE_INDOOR2_ENTRANCE[17] = "indoor2_entrance";
const char CLIENT_IDENTIFIER_NODE_INDOOR2_CONSOLE[16]  = "indoor1_console";
const char CLIENT_IDENTIFIER_NODE_INDOOR2_RACK[13]     = "indoor2_rack";



const char NODEMCU_DEVICENAME_DOOR[13] = "outdoor/door";
const char NODEMCU_FUNC_TOGGLE[7] = "toggle";


const char EZCONTROL_FUNC_ON[2] = "1";
const char EZCONTROL_FUNC_OFF[2] = "2";
const char EZCONTROL_FUNC_TOGGLE[2] = "3";

  
const char EZCONTROL_ACTUATOR_ZONE_INDOOR1_LIGHT_COLOR[2] = "1"; // halle vorne licht: seite
const char EZCONTROL_ACTUATOR_ZONE_INDOOR1_LIGHT_MAIN[2] = "2";  // halle vorne licht: mitte
const char EZCONTROL_ACTUATOR_ZONE_OUTDOOR_DOOR[2] = "3";        // halle tor
const char EZCONTROL_ACTUATOR_ZONE_INDOOR2_LIGHT_MAIN2[2] = "4"; // halle hinten licht: tisch
const char EZCONTROL_ACTUATOR_ZONE_INDOOR2_LIGHT_MAIN[2] = "5";  // halle hinten licht: werkbank
const char EZCONTROL_ACTUATOR_ZONE_INDOOR1_LIGHT_COLOR2[2] = "6";// halle vorne licht: bunt (hochregal)
const char EZCONTROL_ACTUATOR_ZONE_INDOOR2_LIGHT_SOCCER[2] = "7";// halle hinten licht: wuzzler
const char EZCONTROL_ACTUATOR_ZONE_INDOOR1_SOUNDAMP[2] = "8";    // halle vorne sound
const char EZCONTROL_ACTUATOR_ZONE_INDOOR2_LAZER[2] = "9";       // halle hinten lazer
const char EZCONTROL_ACTUATOR_ZONE_INDOOR2_FOG[3] = "10";        // halle hinten nebelmaschine
const char EZCONTROL_ACTUATOR_ZONE_INDOOR2_LIGHT_COLOR[3] = "11";// halle hinten ledwurst werkbank

const char IRTRANS_DEVICENAME_BEAMER[7] = "beamer";
const char IRTRANS_DEVICENAME_AIRCON[13] = "aircondition";
const char IRTRANS_DEVICENAME_TV[3] = "tv";
const char IRTRANS_DEVICENAME_HDMI_SWITCH[11] = "hdmiswitch";

const char IRTRANS_FUNC_POWERON[9] = "power/on";
const char IRTRANS_FUNC_POWEROFF[10] = "power/off";
const char IRTRANS_FUNC_POWERTOGGLE[13] = "power/toggle";
const char IRTRANS_FUNC_TEMP_UP[15] = "temperature/up";
const char IRTRANS_FUNC_TEMP_DOWN[17] = "temperature/down";
const char IRTRANS_FUNC_MODE[5] = "mode";
const char IRTRANS_FUNC_OUTA_OFF[10] = "out-a/off";
const char IRTRANS_FUNC_OUTA_IN1[10] = "out-a/in1";
const char IRTRANS_FUNC_OUTA_IN2[10] = "out-a/in2";
const char IRTRANS_FUNC_OUTA_IN3[10] = "out-a/in3";
const char IRTRANS_FUNC_OUTA_IN4[10] = "out-a/in4";
const char IRTRANS_FUNC_OUTB_OFF[10] = "out-b/off";
const char IRTRANS_FUNC_OUTB_IN1[10] = "out-b/in1";
const char IRTRANS_FUNC_OUTB_IN2[10] = "out-b/in2";
const char IRTRANS_FUNC_OUTB_IN3[10] = "out-b/in3";
const char IRTRANS_FUNC_OUTB_IN4[10] = "out-b/in4";


const char TASMOTA_FUNC_POWERON[11] = "Power%20ON";
const char TASMOTA_FUNC_POWEROFF[12] = "Power%20OFF";
const char TASMOTA_FUNC_POWERTOGGLE[15] = "Power%20TOGGLE";


const char HTTP_PREFIX[8] = "http://";

const char IP_JUDGE[10]                 = "10.0.1.20";
const char IP_NODEMCU_INDOOR1_ENTRANCE[10] = "10.0.1.21";


const char IP_EZCONTROL[11] = "10.0.1.118";

const char IP_IRTRANS_INDOOR[11] = "10.0.1.143";
const char IP_IRTRANS_OUTDOOR[11] = "10.0.1.255";  // TODO: invalid IP

const char IP_TASMOTA_01_OUTDOOR_LIGHT_TABLE[11]    = "tasmota-01";
const char IP_TASMOTA_02_OUTDOOR_LIGHT_DOORSPOT[11] = "tasmota-02";
const char IP_TASMOTA_03_OUTDOOR_LIGHT_LEDWALL[11]  = "tasmota-03";
const char IP_TASMOTA_04_OUTDOOR_SOUND_AMP[11]      = "tasmota-24";
const char IP_TASMOTA_05_INDOOR1_LIGHT_MAIN[11]     = "tasmota-05";
const char IP_TASMOTA_06_INDOOR1_LIGHT_COLOR1[11]   = "tasmota-06";
const char IP_TASMOTA_07_INDOOR1_LIGHT_COLOR2[11]   = "tasmota-07";
const char IP_TASMOTA_08_INDOOR1_SOUND_AMP[11]      = "tasmota-08";
const char IP_TASMOTA_09_INDOOR2_LIGHT_MAIN[11]     = "tasmota-09";
const char IP_TASMOTA_10_INDOOR2_LIGHT_MAIN2[11]    = "tasmota-10";
const char IP_TASMOTA_11_INDOOR2_LIGHT_COLOR1[11]   = "tasmota-11";
const char IP_TASMOTA_12_INDOOR2_LIGHT_COLOR2[11]   = "tasmota-12";
const char IP_TASMOTA_13_INDOOR2_SOUND_AMP[11]      = "tasmota-13";
const char IP_TASMOTA_14_INDOOR2_SOUND_MIXER[11]    = "tasmota-14";
const char IP_TASMOTA_15_INDOOR2_LAZER[11]          = "tasmota-15";
const char IP_TASMOTA_16_INDOOR2_FOGMACHINE[11]     = "tasmota-16";
const char IP_TASMOTA_17_INDOOR2_SOCCER[11]         = "tasmota-17";
const char IP_TASMOTA_18_INDOOR2_DARTS[11]          = "tasmota-18";
const char IP_TASMOTA_24[11]                        = "tasmota-24";


const char IP_JUPITER[11] = "10.0.1.196";

const char JUPITER_FUNC_VOLUME_UP[5] = "up_0";
const char JUPITER_FUNC_VOLUME_DOWN[7] = "down_0";


const char IP_OUTDOOR_PC[16] = "10.0.1.146:8000";
byte MAC_OUTDOOR_PC[] = { 0x00, 0x1C, 0xC0, 0xDC, 0x5B, 0x5C };

const char PC_FUNC_VOLUME_UP[14] = "increasevol=1";
const char PC_FUNC_VOLUME_DOWN[14] = "decreasevol=1";
const char PC_FUNC_SHUTDOWN[11] = "shutdown=1";

const uint8_t OUTDOOR = 0;  // outdoor
const uint8_t INDOOR1 = 1;  // halle vorne
const uint8_t INDOOR2 = 2;  // halle hinten
const uint8_t COMBO = 3;    // undefined

const uint8_t LIGHT_MAIN = 0;
const uint8_t LIGHT_MAIN2 = 1;
const uint8_t LIGHT_COLOR = 2;
const uint8_t LIGHT_COLOR2 = 3;
const uint8_t LIGHT_COLOR3 = 4;
const uint8_t SOUND_AMP = 5;
const uint8_t SOUND_AMP2 = 6;
const uint8_t SOUND_MIXER = 7;
const uint8_t SUBWOOFER = 8;
const uint8_t DOOR = 9;
const uint8_t PC = 10;
const uint8_t LAZER = 11;
const uint8_t FOGMACHINE = 12;
const uint8_t AIRCON = 13;
const uint8_t BEAMER = 14;
const uint8_t TV = 15;
const uint8_t MIST = 16;
const uint8_t HDMI_SWITCH = 17;
const uint8_t JUPITER = 18;
const uint8_t SOCCER = 19;
const uint8_t DARTS = 20;

const uint8_t GROUP_INDOOR2_ALL = 21;
const uint8_t GROUP_INDOOR1_ALL = 22;
const uint8_t GROUP_OUTDOOR_ALL = 23;
const uint8_t GROUP_INDOOR_ALL = 24;
const uint8_t GROUP_ALL = 25;


const char POWERON[2] = "0";
const char POWEROFF[2] = "1";
const char POWERTOGGLE[2] = "2";
const char TEMP_UP[2] = "3";
const char TEMP_DOWN[2] = "4";
const char VOLUME_UP[2] = "5";
const char VOLUME_DOWN[2] = "6";
const char OUTA_OFF[2] = "7";
const char OUTA_IN1[2] = "8";
const char OUTA_IN2[2] = "9";
const char OUTA_IN3[3] = "10";
const char OUTA_IN4[3] = "11";
const char OUTB_OFF[3] = "12";
const char OUTB_IN1[3] = "13";
const char OUTB_IN2[3] = "14";
const char OUTB_IN3[3] = "15";
const char OUTB_IN4[3] = "16";

const char MODE[3] = "17";
const char SHUTDOWN[3] = "18";
const char WAKEONLAN[3] = "19";
const char TOGGLE[3] = "20";
