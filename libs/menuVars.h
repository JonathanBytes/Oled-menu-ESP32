#include <cstring> // Ensure strcmp is available

typedef void (*IconAction)();

enum Mode { ICONS_MODE, PARAMS_MODE };
Mode currentMode = ICONS_MODE;

int selectedItem = 0;
int hoveredParam = -1;
int selectedParam = -1;
int firstVisibleItem = 0;
int currentBankIndex = 0;
int currentPresetIndex = 0;

struct Page {
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
void actionHome() {
  // Define what happens when the home icon is selected
}

void actionPresets() {
  // Define what happens when the presets icon is selected
  currentPage = getPageIndexByName("preset");
}

void actionKnob() {
  // Define what happens when the knob icon is selected
}

void actionRestart() {
  // Define what happens when the restart icon is selected
}

void actionShutdown() {
  // Define what happens when the shutdown icon is selected
}

void actionBack() {
  // Define what happens when the back icon is selected
  currentPage = getPageIndexByName("home");
}

void actionGear() {
  // Define what happens when the gear icon is selected
  currentPage = getPageIndexByName("settings");
}

void actionBrightness() {
  currentMode = PARAMS_MODE;
  hoveredParam = 0;
  // Define what happens when the brightness icon is selected
}

void actionShowFPS() {
  // Define what happens when the show FPS icon is selected
  SHOW_FPS = !SHOW_FPS;
}

void actionFrameCap() {
  // Define what happens when the frame cap icon is selected
  FRAME_CAP = !FRAME_CAP;
}

void actionSave() {
  // Define what happens when the save icon is selected
  saveEEPROM();
}

void actionEditPreset() {
  currentPage = getPageIndexByName("editPreset");
  // Define what happens when the edit preset icon is selected
}

void actionDeletePreset() {
  // Define what happens when the delete preset icon is selected
}

void actionDrive() {
  // Define what happens when the drive icon is selected
  currentMode = PARAMS_MODE;
  hoveredParam = 0;
}

void actionAmpMrsh() {
  // Define what happens when the amp_mrsh icon is selected
  currentMode = PARAMS_MODE;
  hoveredParam = 0;
}

void actionAmpFndr() {
  // Define what happens when the amp_fndr icon is selected
  currentMode = PARAMS_MODE;
  hoveredParam = 0;
}

void actionCab() {
  // Define what happens when the cab icon is selected
  currentMode = PARAMS_MODE;
  hoveredParam = 0;
}

void actionReverb() {
  // Define what happens when the reverb icon is selected
  currentMode = PARAMS_MODE;
  hoveredParam = 0;
}

// Icons and Actions arrays
IconAction actionsHome[] = {actionPresets, actionKnob, actionGear,
                            actionRestart, actionShutdown};
const unsigned char *iconsHome[] = {icon_presets, icon_knob, icon_gear,
                                    icon_restart, icon_shutdown};

IconAction actionsPreset[] = {actionBack, actionDrive,  actionAmpFndr,
                              actionCab,  actionReverb, actionSave};
const unsigned char *iconsPreset[] = {icon_back, icon_drive,  icon_amp_fndr,
                                      icon_cab,  icon_reverb, icon_save};

IconAction actionsEditPreset[] = {actionBack, actionDrive,  actionAmpMrsh,
                                  actionCab,  actionReverb, actionSave};
const unsigned char *iconsEditPreset[] = {icon_back, icon_drive,  icon_amp_mrsh,
                                          icon_cab,  icon_reverb, icon_save};

IconAction actionsSettings[] = {actionBack, actionBrightness, actionShowFPS,
                                actionFrameCap, actionSave};
const unsigned char *iconsSettings[] = {icon_back, icon_brightness,
                                        icon_brightness, icon_drive, icon_save};

// Pages array
Page pages[] = {
    {"home", iconsHome, actionsHome, sizeof(iconsHome) / sizeof(iconsHome[0])},
    {"preset", iconsPreset, actionsPreset,
     sizeof(iconsPreset) / sizeof(iconsPreset[0])},
    {"editPreset", iconsEditPreset, actionsEditPreset,
     sizeof(iconsEditPreset) / sizeof(iconsEditPreset[0])},
    {"settings", iconsSettings, actionsSettings,
     sizeof(iconsSettings) / sizeof(iconsSettings[0])}};

int totalPages = sizeof(pages) / sizeof(pages[0]);

// Helper functions
Page *getPageByName(const char *name) {
  for (int i = 0; i < totalPages; i++) {
    if (strcmp(pages[i].name, name) == 0) {
      return &pages[i];
    }
  }
  return nullptr; // Return nullptr if the page is not found
}

int getPageIndexByName(const char *name) {
  for (int i = 0; i < totalPages; i++) {
    if (strcmp(pages[i].name, name) == 0) {
      return i;
    }
  }
  return -1; // Return -1 if the page is not found
}

// Initialize currentPage after pages array is defined
// int currentPage = getPageIndexByName("home");
