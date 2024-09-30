#include "assets/main.h"
#include "constants.h"
#include "libs/menuVars.h"
#include "libs/output/leds.h"
#include "libs/input/main.h"
#include "libs/display.h"

TaskHandle_t DisplayTask0;
TaskHandle_t LedTask0;

void setup() {
  xTaskCreatePinnedToCore(displayloop, "DisplayTask_0", 2048, NULL, 1, &DisplayTask0, 0);
  xTaskCreatePinnedToCore(ledloop, "LedTask_0", 1024, NULL, 1, &LedTask0, 0);
  hardwareSetup();
}

void loop() {
  int totalIcons = pages[currentPage].iconCount;
  handleHardware(totalIcons);
}

void displayloop(void *parameter) {
  setupDisplay();
  bootAnimations();
  for (int i = 0; i < 180; i++) { 
     precalculated_x_radius_pixel[i] =  sin(radians(i-90)) * radius_pixel + center_x; 
     precalculated_y_radius_pixel[i] = -cos(radians(i-90)) * radius_pixel + center_y;      
  }
  while (1) {
    updateDisplay();
    if (FRAME_CAP) { vTaskDelay(FRAME_DELAY/portTICK_PERIOD_MS); }
  }
}

void ledloop(void *parameter) {
  setupLeds();
  while (1) {
    handleLeds();
    vTaskDelay(10/portTICK_PERIOD_MS);
  }
}
