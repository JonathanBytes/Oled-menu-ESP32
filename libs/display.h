#include <U8g2lib.h>

U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE);

int currentX = ICON_SPACING;
int scrollCurrentX = 0;

// Ease-in-out cubic function
float easeInOut(float t, float b, float c, float d) {
  t /= d / 2;
  if (t < 1)
    return c / 2 * t * t * t + b;
  t -= 2;
  return c / 2 * (t * t * t + 2) + b;
}

void setupDisplay() {
  u8g2.begin();
  u8g2.setBitmapMode(1);
}

void drawIcons() {
  for (int i = 0; i < VISIBLE_ICONS; i++) {
    int iconIndex = (firstVisibleItem + i) % totalIcons;
    u8g2.drawXBMP(3 + ITEM_WIDTH * i, 0, ICON_WIDTH, ICON_HEIGHT, iconAllArray[iconIndex]);
  }
}

void drawScrollBar() {
  u8g2.drawXBMP(0, DISPLAY_HEIGHT - SCROLL_BAR_HEIGHT, DISPLAY_WIDTH, SCROLL_BAR_HEIGHT, uiAllArray[0]);
}

void drawSelection(int x, int scrollX) {
  u8g2.drawXBMP(x, 0, 32, 32, uiAllArray[2]); // Selection rectangle
  u8g2.drawBox(scrollX, DISPLAY_HEIGHT - SCROLL_BAR_HEIGHT, SCROLL_BAR_WIDTH, SCROLL_BAR_HEIGHT); // Scroll indicator
}

void renderDisplay(int x, int scrollX) {
  u8g2.clearBuffer();
  drawIcons();
  drawScrollBar();
  drawSelection(x, scrollX);
  u8g2.sendBuffer();
}

void animateRectangle(int startX, int endX, int scrollStartX, int scrollEndX, float duration = 250) {
  unsigned long startTime = millis();

  while (millis() - startTime < duration) {
    unsigned long currentTime = millis() - startTime;
    currentX = easeInOut(currentTime, startX, endX - startX, duration);
    scrollCurrentX = easeInOut(currentTime, scrollStartX, scrollEndX - scrollStartX, duration);

    renderDisplay(currentX, scrollCurrentX);
    delay(10);
  }

  currentX = endX;
  scrollCurrentX = scrollEndX;
  renderDisplay(currentX, scrollCurrentX);
}

void drawSelectionIndicator() {
  int selectionPosX = 2 + (selectedItem - firstVisibleItem) * ITEM_WIDTH;
  int scrollPosX = (DISPLAY_WIDTH - SCROLL_BAR_WIDTH) * ((float)selectedItem / (totalIcons - 1));

  if (selectionPosX != currentX || scrollPosX != scrollCurrentX) {
    animateRectangle(currentX, selectionPosX, scrollCurrentX, scrollPosX);
  }

  drawSelection(selectionPosX, scrollPosX);
}

void updateDisplay() {
  u8g2.clearBuffer();
  drawIcons();
  drawScrollBar();
  drawSelectionIndicator();
  u8g2.sendBuffer();
}

void animateBitmap(const unsigned char *bitmapArray[], int frames, int frameDelay, int width, int height, int xPos, int yPos) {
  for (int i = 0; i < frames; i++) {
    u8g2.firstPage();
    do {
      u8g2.drawXBMP(xPos, yPos, width, height, bitmapArray[i]);
    } while (u8g2.nextPage());
    delay(frameDelay);
  }
}

void bootAnimations() {
  animateBitmap(cat, 28, 40, 30, 30, 56, 4);
  // animateBitmap(code, 122, 10, 32, 32, 56, 0);
  animateBitmap(skate, 28, 10, 32, 32, 56, 0);
}
