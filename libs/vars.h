#include <EEPROM.h>
#define EEPROM_SIZE 3

bool FRAME_CAP = false;
bool SHOW_FPS = true;

void setupEEPROM() {
  EEPROM.begin(EEPROM_SIZE);
  FRAME_CAP = EEPROM.read(0);
  SHOW_FPS = EEPROM.read(1);
  brightness = EEPROM.read(2);
  iconParamsArray[5].paramValues[0] = brightness;
}

void saveEEPROM() {
  EEPROM.write(0, FRAME_CAP);
  EEPROM.write(1, SHOW_FPS);
  EEPROM.write(2, brightness);
  EEPROM.commit();
}

#define LED1_PIN 11
#define LED2_PIN 12
#define LED3_PIN 13

bool LED_CHANGE = false;
bool LED1_ON = false;
bool LED2_ON = false;
bool LED3_ON = false;
bool prevLED1_ON = false;
bool prevLED2_ON = false;
bool prevLED3_ON = false;

bool fading = false;

#include "menuVars.h"
