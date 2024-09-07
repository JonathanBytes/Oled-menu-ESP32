
#include <Bounce2.h> // Assuming you're using the Bounce2 library

Bounce debouncerPrev = Bounce();
Bounce debouncerNext = Bounce();

void buttonsSetup() {
  pinMode(BUTTON_PREV_PIN, INPUT_PULLUP);
  pinMode(BUTTON_NEXT_PIN, INPUT_PULLUP);
  debouncerPrev.attach(BUTTON_PREV_PIN);
  debouncerPrev.interval(25); // debounce interval
  debouncerNext.attach(BUTTON_NEXT_PIN);
  debouncerNext.interval(25);
}

void handleButtonPresses(int totalIcons) {
  debouncerPrev.update();
  debouncerNext.update();

  if (debouncerPrev.fell()) {
    selectedItem = 0;
    currentPage = (currentPage == 0) ? 1 : 0; // toggle between pages
  }
  if (debouncerNext.fell()) {
    selectedItem = (selectedItem + 1) % totalIcons;
  }

  if (selectedItem >= firstVisibleItem + VISIBLE_ICONS) {
    firstVisibleItem = (firstVisibleItem + 1) % totalIcons;
  } else if (selectedItem < firstVisibleItem) {
    firstVisibleItem = (firstVisibleItem - 1 + totalIcons) % totalIcons;
  }
}
