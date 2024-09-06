#include <U8g2lib.h>

U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE);

int currentX = ICON_SPACING;
int scrollCurrentX = 0;
int currentPage = 1; // Variable to track the current menu page

// Define total icons for each page
const int totalIconsPage1 = sizeof(iconAllArray) / sizeof(iconAllArray[0]);
const int totalIconsPage2 = sizeof(uiIconsAllArray) / sizeof(uiIconsAllArray[0]);

int totalPages = 2;

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

void drawIcons(int page) {
  int iconsToDraw = 0;
  const unsigned char **iconArray = nullptr;

  // Select the correct array and icon count based on the page
  if (page == 0) {
    iconsToDraw = totalIconsPage1;
    iconArray = iconAllArray;
  } else if (page == 1) {
    iconsToDraw = totalIconsPage2;
    iconArray = uiIconsAllArray;
  }

  // Draw the icons for the current page
  for (int i = 0; i < VISIBLE_ICONS && i < iconsToDraw; i++) {
    int iconIndex = (firstVisibleItem + i) % iconsToDraw;
    u8g2.drawXBMP(3 + ITEM_WIDTH * i, 0, ICON_WIDTH, ICON_HEIGHT, iconArray[iconIndex]);
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
  drawIcons(currentPage); // Draw icons based on the current page
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
  int totalIcons = (currentPage == 0) ? totalIconsPage1 : totalIconsPage2;
  int selectionPosX = 2 + (selectedItem - firstVisibleItem) * ITEM_WIDTH;
  int scrollPosX = (DISPLAY_WIDTH - SCROLL_BAR_WIDTH) * ((float)selectedItem / (totalIcons - 1));

  if (selectionPosX != currentX || scrollPosX != scrollCurrentX) {
    animateRectangle(currentX, selectionPosX, scrollCurrentX, scrollPosX);
  }

  drawSelection(selectionPosX, scrollPosX);
}

void updateDisplay() {
  u8g2.clearBuffer();
  drawIcons(currentPage); // Update based on the current page
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
  animateBitmap(skate, 28, 10, 32, 32, 56, 0);
}

void changePage(int direction) {
  currentPage += direction;
  if (currentPage < 0)
    currentPage = 1;
  if (currentPage >= 2)
    currentPage = 0;

  updateDisplay(); // Update display after page change
}
