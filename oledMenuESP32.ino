#include "assets/main.h"
#include "constants.h"
#include "libs/menuVars.h"
#include "libs/display.h"
#include "libs/input/main.h"

TaskHandle_t DisplayTask0;

void setup() {
  Serial.begin(115200);
  xTaskCreatePinnedToCore(displayloop, "DisplayTask_0", 32768, NULL, 1, &DisplayTask0, 0);
  hardwareSetup();
}

void loop() {
  int totalIcons = pages[currentPage].iconCount;
  handleHardware(totalIcons);
}

void displayloop(void *parameter) {
  Serial.println("DisplayTask_0 running on core " + String(xPortGetCoreID()));
  setupDisplay();
  bootAnimations();
  while (1) {
    updateDisplay();
    if (FRAME_CAP) { vTaskDelay(FRAME_DELAY/portTICK_PERIOD_MS); }
    // Consider adding a delay here if needed to prevent task starvation
  }
}
