#include <AH/Hardware/MultiPurposeButton.hpp>

MultiPurposeButton btn1{BUTTON_PREV_PIN}, btn2{BUTTON_NEXT_PIN}, rotbtn{36};

int snapshots = 4;
int currentSnapshot = 0;

void updateLeds() {
  if (!fading) { // Solo permitimos cambiar LEDs si no está en fade
    LED_CHANGE = true;

    // Actualizar el estado de los LEDs según el snapshot actual
    if (currentPresetIndex == 0) {
      LED1_ON = true;
      LED2_ON = false;
      LED3_ON = false;
    } else if (currentPresetIndex == 1) {
      LED1_ON = false;
      LED2_ON = true;
      LED3_ON = false;
    } else if (currentPresetIndex == 2) {
      LED1_ON = false;
      LED2_ON = false;
      LED3_ON = true;
    } else if (currentPresetIndex == 3) {
      LED1_ON = true;
      LED2_ON = true;
      LED3_ON = true;
    }

    fading = true; // Marcar que estamos en un fade
  }
}

void configureButton(MultiPurposeButton &button) {
  button.setLongPressDelay(600);
  button.setMultiPressDelay(400);
  button.begin();
}

void buttonsSetup() {
  configureButton(btn1);
  configureButton(btn2);
  configureButton(rotbtn);
  updateLeds();
}

void handleButton(MultiPurposeButton &button, bool direction) {
  if (button.update() == button.ShortPressRelease) {
    banksArray = doc.as<JsonArray>();
    currentBank = banksArray[currentBankIndex];
    presets = currentBank["presets"];

    if (direction) {
      currentPresetIndex = (currentPresetIndex + 1) % presets.size();
    } else {
      currentPresetIndex = (currentPresetIndex - 1 + presets.size()) % presets.size();
    }

    JsonObject preset = presets[currentPresetIndex];
    currentPresetName = preset["name"].as<const char*>();

  midi.sendPC({currentPresetIndex, Channel_1, Cable_1});
  updateLeds();
  }
}

void handleRotaryButton(MultiPurposeButton &rotbtn) {
  switch (rotbtn.update()) {
  case rotbtn.None:
    break;
  case rotbtn.PressStart:
    break;
  case rotbtn.ShortPressRelease:
    // if (currentMode == ICONS_MODE && currentPage ==
    // getPageIndexByName("editPreset")) {
    //   currentMode = PARAMS_MODE;
    //   selectedParam = 0; // Start with the first parameter
    // } else if (currentMode == PARAMS_MODE) {
    //   if (selectedParam == -1) {
    //     selectedParam = 0; // Start with the first parameter
    //   } else {
    //     // Exit parameter editing mode
    //     selectedParam = -1;
    //   }
    // }

    // Do the function related to the selectedItem of the currentPage
    if (currentMode == ICONS_MODE) {
      // Change page
      pages[currentPage].actions[selectedItem]();
    } else if (currentMode == PARAMS_MODE && selectedParam == -1) {
      selectedParam = hoveredParam;
    } else if (currentMode == PARAMS_MODE && selectedParam != -1) {
      selectedParam = -1;
    }
    break;
  case rotbtn.LongPress:
    if (currentMode == ICONS_MODE) {
      // Change page
      selectedItem = 0;
      currentPage = (currentPage + 1) % totalPages; // toggle between pages
    } else if (currentMode == PARAMS_MODE) {
      // Switch back to icons mode
      currentMode = ICONS_MODE;
      hoveredParam = -1;
      selectedParam = -1;
    }
    break;
  }
}

void handleButtonPresses() {
  handleButton(btn1, false);
  handleButton(btn2, true);
  handleRotaryButton(rotbtn);
}
