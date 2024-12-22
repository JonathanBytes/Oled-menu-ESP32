#include "../assets/fonts/fonts.h"
#include "SSD1306Wire.h"
#include "helpers/easeInOut.h"
#include <Wire.h>

SSD1306Wire display(0x3c, 1, 2); // ADDRESS, SDA, SCL
#include "fpsOverlay.h"
#include "output/display/knobDisplay.h"

int currentX = ICON_SPACING;
int scrollCurrentX = 0;

void setupDisplay() {
  display.init();
  display.flipScreenVertically();
  display.setConstrast(50);
}

void drawIconParameters(const unsigned char *selectedIcon) {
  for (const auto &iconParams : iconParamsArray) {
    if (iconParams.icon == selectedIcon) { // Match based on icon pointer
      for (int i = 0; i < 4; i++) {
        if (iconParams.params[i] != nullptr) {
          int x = (i * DISPLAY_WIDTH) / 4;
          int y = DISPLAY_HEIGHT / 2;
          display.setFont(Pixel_Operator_16);
          int valueWidth =
              display.getStringWidth(String(iconParams.paramValues[i]) + "%");
          display.setFont(Pixels_16);
          int paramWidth = display.getStringWidth(iconParams.params[i]);
          int offset = 16;
          int valuePosX = x - (valueWidth / 2) + offset;
          int paramPosX = x - (paramWidth / 2) + offset;
          if (currentMode == PARAMS_MODE && hoveredParam == i) {
            display.setColor(BLACK); // Highlight selected parameter
          }
          display.setFont(Pixel_Operator_16);
          display.drawString(valuePosX, y,
                             String(iconParams.paramValues[i]) + "%");
          display.setFont(Pixels_16);
          display.drawString(paramPosX, y + 10, iconParams.params[i]);
          display.setColor(WHITE); // Reset color
        }
      }
      return; // Exit after drawing the parameters
    }
  }
}

void drawIcons(int page) {
  if (page < 0 || page >= totalPages)
    return; // Validate page

  const Page &currentPage = pages[page];   // Get current page
  int iconsToDraw = currentPage.iconCount; // Number of icons

  // Draw icons
  for (int i = 0; i < VISIBLE_ICONS && i < iconsToDraw; i++) {
    int iconIndex = (firstVisibleItem + i) % iconsToDraw;
    display.drawXbm(3 + ITEM_WIDTH * i, 0, ICON_WIDTH, ICON_HEIGHT,
                    currentPage.icons[iconIndex]);
  }
  // Draw parameters of the selected icon if it has parameters
  if (currentPage.icons[selectedItem] != nullptr) {
    const unsigned char *selectedIcon = currentPage.icons[selectedItem];
    drawIconParameters(selectedIcon);
  }
}

void drawScrollBar() {
  display.drawXbm(0, 64 - SCROLL_BAR_HEIGHT, DISPLAY_WIDTH, SCROLL_BAR_HEIGHT,
                  uiAllArray[0]);
}

void drawSelection(int x, int scrollX) {
  display.drawXbm(x, 0, 32, 32, uiAllArray[1]); // Selection rectangle
  if (currentMode == ICONS_MODE) {
    display.fillRect(scrollX, 64 - SCROLL_BAR_HEIGHT, SCROLL_BAR_WIDTH,
                     SCROLL_BAR_HEIGHT); // Scroll indicator
  }
}

void renderDisplay(int x, int scrollX) {
  display.clear();
  drawIcons(currentPage); // Draw icons based on the current page
  drawScrollBar();
  drawSelection(x, scrollX);
  if (SHOW_FPS) {
    updateFPS();
  }
  display.display();
}

void animateRectangle(int startX, int endX, int scrollStartX, int scrollEndX,
                      float duration = 250) {
  unsigned long startTime = millis();

  while (millis() - startTime < duration) {
    unsigned long currentTime = millis() - startTime;
    currentX = easeInOut(currentTime, startX, endX - startX, duration);
    scrollCurrentX = easeInOut(currentTime, scrollStartX,
                               scrollEndX - scrollStartX, duration);

    renderDisplay(currentX, scrollCurrentX);
    if (FRAME_CAP) {
      delay(FRAME_DELAY);
      delay(0); // Allow other tasks to run
    }
  }

  currentX = endX;
  scrollCurrentX = scrollEndX;
  renderDisplay(currentX, scrollCurrentX);
}

void drawSelectionIndicator() {
  int totalIcons = pages[currentPage].iconCount;
  int selectionPosX = 2 + (selectedItem - firstVisibleItem) * ITEM_WIDTH;
  int scrollPosX = (DISPLAY_WIDTH - SCROLL_BAR_WIDTH) *
                   ((float)selectedItem / (totalIcons - 1));

  if (selectionPosX != currentX || scrollPosX != scrollCurrentX) {
    animateRectangle(currentX, selectionPosX, scrollCurrentX, scrollPosX);
  }

  drawSelection(selectionPosX, scrollPosX);
}

void updateDisplay() {
  display.clear();
  if (!shouldDrawCircle()) {
    drawIcons(currentPage); // Update based on the current page
    drawScrollBar();
    drawSelectionIndicator();
    if (currentMode == PARAMS_MODE) {
      // drawParamSelectionIndicator(); // Draw selection indicator for
      // parameters
    }
  }
  // Draw the knob only for the potentiometer that was updated and within the
  // display timeout
  if (updatedPotIndex != -1 && shouldDrawCircle()) {
    drawKnob(potValues[updatedPotIndex],
             updatedPotIndex); // Draw the knob for the updated pot
  } else {
    // If the timeout has passed, reset the updatedPotIndex and clear the
    // display
    updatedPotIndex = -1;
  }

  if (SHOW_FPS) {
    updateFPS();
  }
  display.display();
}

// Function to animate a bitmap and update FPS
void animateBitmap(const unsigned char *bitmapArray[], int frames,
                   int frameDelay, int repetitions, int width, int height,
                   int xPos, int yPos) {
  for (int j = 0; j < repetitions; j++) {
    for (int i = 0; i < frames; i++) {
      display.clear();
      display.drawXbm(xPos, yPos, width, height, bitmapArray[i]);

      if (SHOW_FPS) {
        updateFPS();
      }
      display.display();
      if (FRAME_CAP) {
        delay(frameDelay); // delay for fixed framerate
      }
    }
  }
}

void bootAnimations() {
  animateBitmap(angryCat, 28, 16, 2, 30, 30, (DISPLAY_WIDTH - 30) / 2,
                (DISPLAY_HEIGHT - 30) / 2);
  animateBitmap(skate, 28, 16, 2, 32, 32, (DISPLAY_WIDTH - 32) / 2,
                (DISPLAY_HEIGHT - 30) / 2);
}

void changePage(int direction) {
  currentPage += direction;
  if (currentPage < 0)
    currentPage = 1;
  if (currentPage >= 2)
    currentPage = 0;

  updateDisplay(); // Update display after page change
}
