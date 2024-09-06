#include <Bounce2.h>

Bounce debouncerPrev = Bounce();
Bounce debouncerNext = Bounce();

void buttonsSetup() {
  pinMode(BUTTON_PREV_PIN, INPUT_PULLUP);
  pinMode(BUTTON_NEXT_PIN, INPUT_PULLUP);
  debouncerPrev.attach(BUTTON_PREV_PIN);
  debouncerNext.attach(BUTTON_NEXT_PIN);
  debouncerPrev.interval(50);
  debouncerNext.interval(50);
}
