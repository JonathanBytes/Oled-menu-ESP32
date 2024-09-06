#include <U8g2lib.h>

U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE);

void setupDisplay() {
  u8g2.begin();
  u8g2.setBitmapMode(1);
}

void drawIcons() {
  // Draw the icons on the display
  for (int i = 0; i < VISIBLE_ICONS; i++) {
    int iconIndex = (firstVisibleItem + i) % totalIcons;
    u8g2.drawXBMP(3 + ITEM_WIDTH * i, 0, ICON_WIDTH, ICON_HEIGHT,
                  iconAllArray[iconIndex]);
  }
}

void drawSelectionIndicator() {
  // Draw the selection indicator on the display
  int selectionPosX = 2 + (selectedItem - firstVisibleItem) * ITEM_WIDTH;
  u8g2.drawXBMP(selectionPosX, 0, ITEM_WIDTH, ICON_HEIGHT, uiAllArray[2]);
}

void drawScrollBar() {
  // Draw the scroll bar on the display
  int scrollPosX = (DISPLAY_WIDTH - SCROLL_BAR_WIDTH) *
                   ((float)selectedItem / (float)(totalIcons - 1));
  u8g2.drawBox(scrollPosX, DISPLAY_HEIGHT - SCROLL_BAR_HEIGHT, SCROLL_BAR_WIDTH,
               SCROLL_BAR_HEIGHT);
  u8g2.drawXBMP(0, DISPLAY_HEIGHT - SCROLL_BAR_HEIGHT, DISPLAY_WIDTH,
                SCROLL_BAR_HEIGHT, uiAllArray[0]);
}

void updateDisplay() {
  // Update the display
  u8g2.clearBuffer();
  drawIcons();
  drawSelectionIndicator();
  drawScrollBar();
  u8g2.sendBuffer();
}

void animateBitmap(const unsigned char *bitmapArray[], int frames,
                   int frameDelay, int FRAME_WIDTH, int FRAME_HEIGHT) {
  for (int i = 0; i < frames; i++) {
    u8g2.firstPage();
    do {
      u8g2.drawXBMP(56, 4, FRAME_WIDTH, FRAME_HEIGHT, bitmapArray[i]);
    } while (u8g2.nextPage());
    delay(frameDelay);
  }
}
