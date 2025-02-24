// At the very top of libs/menuVars.h
#include "../banks.h"      // For banks data (defines the banks json string)
#include "../constants.h"  // This should declare Channel_1 and Cable_1
#include "input/midi.h"    // This should declare the global 'midi' instance
#include <cstring>         // Ensure strcmp is available
#include "input/buttons.h" // For updateLeds()
// (Include ArduinoJson and any other headers as needed)
// You also need to have declared banksArray, doc, midi, etc.

typedef void (*IconAction)();

enum Mode
{
  ICONS_MODE,
  PARAMS_MODE
};
Mode currentMode = ICONS_MODE;

int selectedItem = 0;
int hoveredParam = -1;
int selectedParam = -1;
int firstVisibleItem = 0;
int currentBankIndex = 0;
int currentPresetIndex = 0;

struct Page
{
  const char *name;
  const unsigned char **icons;
  IconAction *actions;
  int iconCount;
};

// Declarations of functions and variables used later
Page *getPageByName(const char *name);
int getPageIndexByName(const char *name);
int currentPage = 0;

// Action functions
void actionHome()
{
  // Define what happens when the home icon is selected
}

void actionPresets()
{
  // Define what happens when the presets icon is selected
  currentPage = getPageIndexByName("preset");
  selectedItem = 1;
  firstVisibleItem = 1;
}

void actionLive()
{
  // Define what happens when the live icon is selected
  currentPage = getPageIndexByName("live");
  selectedItem = 0;
  firstVisibleItem = 0;
}

void actionKnob()
{
  // Define what happens when the knob icon is selected
  currentPage = getPageIndexByName("volume");
  selectedItem = 0;
  firstVisibleItem = 0;
}

void actionRestart()
{
  // Define what happens when the restart icon is selected
  ESP.restart();
}

void actionShutdown()
{
  // Define what happens when the shutdown icon is selected
}

void actionBack()
{
  // Define what happens when the back icon is selected
  currentPage = getPageIndexByName("home");
  selectedItem = 0;
  firstVisibleItem = 0;
}

// Helper functions to send MIDI messages from a preset
void sendPresetOnDeactivate(JsonObject preset)
{
  JsonArray onDeactivate = preset["onDeactivate"];
  for (JsonObject message : onDeactivate)
  {
    const char *type = message["type"];
    int address = message["address"];
    int value = message.containsKey("value") ? message["value"] : 0;
    if (strcmp(type, "control_change") == 0)
    {
      midi.sendCC({address, Channel_1}, value);
    }
    else if (strcmp(type, "program_change") == 0)
    {
      midi.sendPC({address, Channel_1, Cable_1});
    }
  }
}

void sendPresetOnActivate(JsonObject preset)
{
  JsonArray onActivate = preset["onActivate"];
  for (JsonObject message : onActivate)
  {
    const char *type = message["type"];
    int address = message["address"];
    int value = message.containsKey("value") ? message["value"] : 0;
    if (strcmp(type, "control_change") == 0)
    {
      midi.sendCC({address, Channel_1}, value);
    }
    else if (strcmp(type, "program_change") == 0)
    {
      delay(40);
      midi.sendPC({address, Channel_1, Cable_1});
    }
  }
}

// Modified bank change action functions
void actionBackwardBank()
{
  // First, send onDeactivate for the current preset
  banksArray = doc.as<JsonArray>();
  currentBank = banksArray[currentBankIndex];
  presets = currentBank["presets"];
  currentPreset = presets[currentPresetIndex];
  sendPresetOnDeactivate(currentPreset);

  // Change bank index backwards
  if (currentBankIndex > 0)
  {
    currentBankIndex--;
  }
  else
  {
    currentBankIndex = BANK_COUNT - 1; // Cycle to last bank
  }

  // Update bank and preset for the new bank
  currentBank = banksArray[currentBankIndex];
  currentPresetIndex = 0; // Reset preset to the first one in the new bank
  presets = currentBank["presets"];
  currentPreset = presets[currentPresetIndex];
  currentBankName = currentBank["name"].as<const char *>();
  currentPresetName = currentPreset["name"].as<const char *>();

  // Now send onActivate for the new preset
  sendPresetOnActivate(currentPreset);
  updateLeds();
}

void actionForwardBank()
{
  // First, send onDeactivate for the current preset
  banksArray = doc.as<JsonArray>();
  currentBank = banksArray[currentBankIndex];
  presets = currentBank["presets"];
  currentPreset = presets[currentPresetIndex];
  sendPresetOnDeactivate(currentPreset);

  // Change bank index forwards
  if (currentBankIndex < BANK_COUNT - 1)
  {
    currentBankIndex++;
  }
  else
  {
    currentBankIndex = 0; // Cycle to the first bank
  }

  // Update bank and preset for the new bank
  currentBank = banksArray[currentBankIndex];
  currentPresetIndex = 0; // Reset preset to the first one in the new bank
  presets = currentBank["presets"];
  currentPreset = presets[currentPresetIndex];
  currentBankName = currentBank["name"].as<const char *>();
  currentPresetName = currentPreset["name"].as<const char *>();

  // Now send onActivate for the new preset
  sendPresetOnActivate(currentPreset);
  updateLeds();
}

void actionGear()
{
  // Define what happens when the gear icon is selected
  currentPage = getPageIndexByName("settings");
  selectedItem = 1;
  firstVisibleItem = 1;
}

void actionBrightness()
{
  currentMode = PARAMS_MODE;
  hoveredParam = 0;
  // Define what happens when the brightness icon is selected
}

void actionShowFPS()
{
  // Define what happens when the show FPS icon is selected
  SHOW_FPS = !SHOW_FPS;
  // update value var
  if (SHOW_FPS)
  {
    iconParamsArray[6].paramValues[0] = 1;
  }
  else
  {
    iconParamsArray[6].paramValues[0] = 0;
  }
}

void actionFrameCap()
{
  // Define what happens when the frame cap icon is selected
  FRAME_CAP = !FRAME_CAP;
  // currentMode = PARAMS_MODE;
  // hoveredParam = 0;
}

void actionSave()
{
  // Define what happens when the save icon is selected
  saveEEPROM();
}

void actionEditPreset()
{
  currentPage = getPageIndexByName("editPreset");
  // Define what happens when the edit preset icon is selected
}

void actionDeletePreset()
{
  // Define what happens when the delete preset icon is selected
}

void actionDrive()
{
  // Define what happens when the drive icon is selected
  currentMode = PARAMS_MODE;
  hoveredParam = 0;
}

void actionAmpMrsh()
{
  // Define what happens when the amp_mrsh icon is selected
  currentMode = PARAMS_MODE;
  hoveredParam = 0;
}

void actionAmpFndr()
{
  // Define what happens when the amp_fndr icon is selected
  currentMode = PARAMS_MODE;
  hoveredParam = 0;
}

void actionCab()
{
  // Define what happens when the cab icon is selected
  currentMode = PARAMS_MODE;
  hoveredParam = 0;
}

void actionReverb()
{
  // Define what happens when the reverb icon is selected
  currentMode = PARAMS_MODE;
  hoveredParam = 0;
}

// Icons and Actions arrays
IconAction actionsHome[] = {actionLive, actionPresets, actionKnob,
                            actionGear, actionRestart, actionShutdown};
const unsigned char *iconsHome[] = {icon_live, icon_edit, icon_knob,
                                    icon_gear, icon_restart, icon_shutdown};

IconAction actionsPreset[] = {actionBack, actionDrive, actionAmpFndr,
                              actionCab, actionReverb, actionSave};
const unsigned char *iconsPreset[] = {icon_back, icon_drive, icon_amp_fndr,
                                      icon_cab, icon_reverb, icon_save};

IconAction actionsEditPreset[] = {actionBack, actionDrive, actionAmpMrsh,
                                  actionCab, actionReverb, actionSave};
const unsigned char *iconsEditPreset[] = {icon_back, icon_drive, icon_amp_mrsh,
                                          icon_cab, icon_reverb, icon_save};

IconAction actionsSettings[] = {actionBack, actionBrightness, actionShowFPS,
                                actionFrameCap, actionSave};
const unsigned char *iconsSettings[] = {
    icon_back, icon_brightness, icon_fps_overlay, icon_fps_lock, icon_save};

IconAction actionsVolume[] = {actionBack, actionKnob};
const unsigned char *iconsVolume[] = {icon_back, icon_knob};

IconAction actionsLive[] = {actionBackwardBank, actionForwardBank};
const unsigned char *iconsLive[] = {icon_back_arrow, icon_forward_arrow};

// Pages array
Page pages[] = {
    {"home", iconsHome, actionsHome, sizeof(iconsHome) / sizeof(iconsHome[0])},
    {"preset", iconsPreset, actionsPreset,
     sizeof(iconsPreset) / sizeof(iconsPreset[0])},
    {"editPreset", iconsEditPreset, actionsEditPreset,
     sizeof(iconsEditPreset) / sizeof(iconsEditPreset[0])},
    {"settings", iconsSettings, actionsSettings,
     sizeof(iconsSettings) / sizeof(iconsSettings[0])},
    {"volume", iconsVolume, actionsVolume,
     sizeof(iconsVolume) / sizeof(iconsVolume[0])},
    {"live", iconsLive, actionsLive, sizeof(iconsLive) / sizeof(iconsLive[0])}};

int totalPages = sizeof(pages) / sizeof(pages[0]);

// Helper functions
Page *getPageByName(const char *name)
{
  for (int i = 0; i < totalPages; i++)
  {
    if (strcmp(pages[i].name, name) == 0)
    {
      return &pages[i];
    }
  }
  return nullptr; // Return nullptr if the page is not found
}

int getPageIndexByName(const char *name)
{
  for (int i = 0; i < totalPages; i++)
  {
    if (strcmp(pages[i].name, name) == 0)
    {
      return i;
    }
  }
  return -1; // Return -1 if the page is not found
}

// Initialize currentPage after pages array is defined
// int currentPage = getPageIndexByName("home");
