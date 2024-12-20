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

void actionHome() {
  // Define what happens when the home icon is selected
}

void actionPresets() {
  // Define what happens when the presets icon is selected
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
}

void actionGear() {
  // currentPage = getPageIndexByName("settings");
  // Define what happens when the gear icon is selected
}

void actionBrightness() {
  currentMode = PARAMS_MODE;
  hoveredParam = 0;
  // Define what happens when the brightness icon is selected
}

void actionSave() {
  // Define what happens when the save icon is selected
}

void actionEditPreset() {
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
}

void actionAmpFndr() {
  // Define what happens when the amp_fndr icon is selected
}

void actionCab() {
  // Define what happens when the cab icon is selected
}

void actionReverb() {
  // Define what happens when the reverb icon is selected
}

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

IconAction actionsSettings[] = {actionBack, actionBrightness};
const unsigned char *iconsSettings[] = {icon_back, icon_brightness};

Page pages[] = {
    {"home", iconsHome, actionsHome, sizeof(iconsHome) / sizeof(iconsHome[0])},
    {"preset", iconsPreset, actionsPreset,
     sizeof(iconsPreset) / sizeof(iconsPreset[0])},
    {"editPreset", iconsEditPreset, actionsEditPreset,
     sizeof(iconsEditPreset) / sizeof(iconsEditPreset[0])},
    {"settings", iconsSettings, actionsSettings,
     sizeof(iconsSettings) / sizeof(iconsSettings[0])}};

int totalPages = sizeof(pages) / sizeof(pages[0]);

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

int currentPage = getPageIndexByName("home");
