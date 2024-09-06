#include <Bounce2.h>

// Constants
const int DISPLAY_WIDTH = 128;
const int DISPLAY_HEIGHT = 32;
const int ICON_WIDTH = 28;
const int ICON_HEIGHT = 28;
const int ITEM_WIDTH = 31;
const int SCROLL_BAR_WIDTH = 7;
const int SCROLL_BAR_HEIGHT = 3;
const int ICON_SPACING = 3;
const int VISIBLE_ICONS = DISPLAY_WIDTH / (ICON_SPACING + ICON_WIDTH) ; // in this case 4

// Button pins
const int BUTTON_PREV_PIN = 16;
const int BUTTON_NEXT_PIN = 4;

// Variables
int selectedItem = 0;
int firstVisibleItem = 0;

#include "assets/main.h"
#include "libs/display.h"

Bounce debouncerPrev = Bounce();
Bounce debouncerNext = Bounce();

TaskHandle_t DisplayTask0;

void setup() {
  xTaskCreatePinnedToCore(displayloop, "DisplayTask_0", 32768, NULL, 1, &DisplayTask0, 0);
  pinMode(BUTTON_PREV_PIN, INPUT_PULLUP);
  pinMode(BUTTON_NEXT_PIN, INPUT_PULLUP);
  debouncerPrev.attach(BUTTON_PREV_PIN);
  debouncerNext.attach(BUTTON_NEXT_PIN);
  debouncerPrev.interval(50);
  debouncerNext.interval(50);
}

void loop() {
  // Actualiza `totalIcons` según la página actual
  int totalIcons = (currentPage == 0) ? totalIconsPage1 : totalIconsPage2;

  // Update debouncers
  debouncerPrev.update();
  debouncerNext.update();

  // Check for button presses
  if (debouncerPrev.fell()) {
    // selectedItem = (selectedItem - 1 + totalIcons) % totalIcons; // previous item
    // change menu page
    selectedItem = 0;
    if (currentPage == 0){
      currentPage = 1;
    } else {
      currentPage = 0;
    }
  }
  if (debouncerNext.fell()) {
    selectedItem = (selectedItem + 1) % totalIcons;
  }

  // Update firstVisibleItem if necessary
  if (selectedItem >= firstVisibleItem + VISIBLE_ICONS) {
    firstVisibleItem = (firstVisibleItem + 1) % totalIcons;
  } else if (selectedItem < firstVisibleItem) {
    firstVisibleItem = (firstVisibleItem - 1 + totalIcons) % totalIcons;
  }
}

void displayloop(void * parameter){
  setupDisplay();
  bootAnimations();
  while (1) {
    updateDisplay();
  }
}
