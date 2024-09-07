#include "assets/main.h"
#include "constants.h"
#include "libs/menuVars.h"
#include "libs/display.h"
#include "libs/input/buttons.h"

TaskHandle_t DisplayTask0;

void setup() {
  xTaskCreatePinnedToCore(displayloop, "DisplayTask_0", 32768, NULL, 1, &DisplayTask0, 0);
  buttonsSetup();
}

void loop() {
  int totalIcons = (currentPage == 0) ? totalIconsPage1 : totalIconsPage2;
  handleButtonPresses(totalIcons);
}

void displayloop(void *parameter) {
  setupDisplay();
  bootAnimations();
  while (1) {
    updateDisplay();
    // Consider adding a delay here if needed to prevent task starvation
  }
}
