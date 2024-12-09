#include "assets/main.h"
#include "constants.h"
#include "libs/vars.h"
#include "libs/input/main.h"
#include "libs/output/main.h"

TaskHandle_t DisplayTask0;
TaskHandle_t LedTask0;

void setup() {
  // xTaskCreatePinnedToCore(displayloop, "DisplayTask_0", 2048, NULL, 1, &DisplayTask0, 0);
  xTaskCreatePinnedToCore(
                    displayloop,   /* Task function. */
                    "DisplayTask_0",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &DisplayTask0,      /* Task handle to keep track of created task */
                    0);          /* pin task to core 0 */                  
  // xTaskCreatePinnedToCore(ledloop, "LedTask_0", 1024, NULL, 1, &LedTask0, 0);
  xTaskCreatePinnedToCore(
                    ledloop,   /* Task function. */
                    "LedTask_0",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &LedTask0,      /* Task handle to keep track of created task */
                    0);          /* pin task to core 1 */
  Serial.begin(115200);
  hardwareSetup();
}

void loop() {
  int totalIcons = pages[currentPage].iconCount;
  handleHardware(totalIcons);
  // Serial.println("SDA: " + String(SDA) + " SCL: " + String(SCL));
}

void displayloop(void *parameter) {
  setupDisplay();
  bootAnimations();
  for (int i = 0; i < 180; i++) { 
     precalculated_x_radius_pixel[i] =  sin(radians(i-90)) * radius_pixel + center_x; 
     precalculated_y_radius_pixel[i] = -cos(radians(i-90)) * radius_pixel + center_y;      
  }
  for(;;){
    updateDisplay();
    if (FRAME_CAP) { vTaskDelay(FRAME_DELAY/portTICK_PERIOD_MS); }
  }
}

void ledloop( void * pvParameters ){
  setupLeds();
  for(;;){
    handleLeds();
    vTaskDelay(10/portTICK_PERIOD_MS);
  }
}
