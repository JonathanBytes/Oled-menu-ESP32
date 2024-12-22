#include "../../../assets/fonts/fonts.h"
#include "../../helpers/easeInOut.h"
#include "SSD1306Wire.h"
#include <Wire.h>

SSD1306Wire display(0x3c, 1, 2); // ADDRESS, SDA, SCL

int currentX = ICON_SPACING;
int scrollCurrentX = 0;
#include "fpsOverlay.h"
#include "knobDisplay.h"
#include "renderAnimations.h"
// #include "renderIcons.h"

// Snapshots names by index
String snapshotsNames[] = {"Clean", "Rythm", "Solo", "Rythm Big"};

void drawIcons(int currentPageIndex) {
  Page *currentPage = &pages[currentPageIndex];
  if (currentPage == nullptr)
    return; // Validate page

  int iconsToDraw = currentPage->iconCount; // Number of icons

  // Draw icons
  for (int i = 0; i < VISIBLE_ICONS && i < iconsToDraw; i++) {
    int iconIndex = (firstVisibleItem + i) % iconsToDraw;
    display.drawXbm(3 + ITEM_WIDTH * i, 0, ICON_WIDTH, ICON_HEIGHT,
                    currentPage->icons[iconIndex]);
  }
}

void drawParamSelection(int i, int x) {
  if (currentMode == PARAMS_MODE && hoveredParam == i) {
    // Highlight hoveredParam parameter
    display.drawXbm(x + 1, 55, 31, 4, uiAllArray[2]);
  }
  if (currentMode == PARAMS_MODE && selectedParam == i) {
    // Highlight selected parameter
    display.drawLine(x + 5, 53, x + 5 + 22, 53);
  }
}

void drawIconParameters(int selectedItem) {
  const unsigned char *selectedIcon = pages[currentPage].icons[selectedItem];
  for (const auto &iconParams : iconParamsArray) {
    if (iconParams.icon == selectedIcon) { // Match based on icon pointer
      for (int i = 0; i < getIconParamsCount(selectedIcon); i++) {
        if (iconParams.params[i] != nullptr) {
          int x = (i * DISPLAY_WIDTH) / 4;
          int y = DISPLAY_HEIGHT / 2;
          display.setFont(Pixels_16);
          int valueWidth =
              display.getStringWidth(String(iconParams.paramValues[i]) + "%");
          int paramWidth = display.getStringWidth(iconParams.params[i]);
          int offset = 16;
          int valuePosX = x - (valueWidth / 2) + offset;
          int paramPosX = x - (paramWidth / 2) + offset;
          display.drawString(valuePosX, y - 2,
                             String(iconParams.paramValues[i]) + "%");
          display.drawString(paramPosX, y + 6, iconParams.params[i]);
          drawParamSelection(i, x);
        }
      }
    }
  }
}

void drawScrollBar() {
  display.drawXbm(0, 64 - SCROLL_BAR_HEIGHT, DISPLAY_WIDTH, SCROLL_BAR_HEIGHT,
                  uiAllArray[0]);
}

void drawSelection(int x, int scrollX) {
  display.drawXbm(x, 0, 32, 32, uiAllArray[1]); // Selection indicator
  display.fillRect(scrollX, 64 - SCROLL_BAR_HEIGHT, SCROLL_BAR_WIDTH,
                   SCROLL_BAR_HEIGHT); // Scroll indicator
}

unsigned long animationStartTime = 0;
float currentTargetX = 0;
float scrollTargetX = 0;
const float ANIMATION_TOLERANCE = 0.5; // Tolerance to prevent small jumps

void drawSelectionIndicator() {
  int totalIcons = pages[currentPage].iconCount;
  const unsigned char *selectedIcon = pages[currentPage].icons[selectedItem];
  int totalParams = getIconParamsCount(selectedIcon);

  // Calculate target positions
  int selectionPosX = 2 + (selectedItem - firstVisibleItem) * ITEM_WIDTH;
  int scrollPosX;

  if (currentMode == PARAMS_MODE) {
    scrollPosX = (DISPLAY_WIDTH - SCROLL_BAR_WIDTH) *
                 ((float)hoveredParam / (totalParams - 1));
  } else if (currentMode == ICONS_MODE) {
    scrollPosX = (DISPLAY_WIDTH - SCROLL_BAR_WIDTH) *
                 ((float)selectedItem / (totalIcons - 1));
  }

  // Update target positions
  if (selectionPosX != currentTargetX || scrollPosX != scrollTargetX) {
    currentTargetX = selectionPosX;
    scrollTargetX = scrollPosX;
    animationStartTime = millis(); // Reset animation start
  }

  // Animate selection position
  currentX = animatePosition(currentX, currentTargetX, animationStartTime, 500);
  scrollCurrentX = animatePosition(scrollCurrentX, scrollTargetX, animationStartTime, 500);

  // Snap to target when within tolerance
  if (abs(currentX - currentTargetX) < ANIMATION_TOLERANCE) {
    currentX = currentTargetX;
  }
  if (abs(scrollCurrentX - scrollTargetX) < ANIMATION_TOLERANCE) {
    scrollCurrentX = scrollTargetX;
  }

  // Draw the selection at interpolated positions
  drawSelection(currentX, scrollCurrentX);
}

void drawCurrentPresetName() {
  display.setFont(Pixel_Operator_HB_16);
  int centered_x = (DISPLAY_WIDTH - display.getStringWidth(currentPresetName)) /
                   2; // Center text
  display.drawString(centered_x, 36, currentPresetName);
}

void drawCurrentBank() {
  display.setFont(Pixel_Operator_HB_16);
  int centered_x = (DISPLAY_WIDTH - display.getStringWidth(currentBankName)) /
                   2; // Center text
  display.drawString(centered_x, 5, currentBankName);
}

void drawUI() {
  
  if (currentPage == getPageIndexByName("live")) { // For Live page
    drawCurrentBank();
    drawCurrentPresetName();
  } else { // For all other pages
    drawIcons(currentPage);
    drawSelectionIndicator();
    drawScrollBar();
  }

  // If Preset page:
  // Icons
  // IconSelection
  // Parameters
  // ParametersSelection
  // Scrollbar
  // Scroll indicator
  if (currentPage == getPageIndexByName("preset")) {
    drawIconParameters(selectedItem);
  }

  // If EditPreset page:
  // Icons
  // IconSelection
  // Parameters
  // ParametersSelection
  // Scrollbar
  // Scroll indicator
  // Save button
  // Cancel button
  // Delete button
  if (currentPage == getPageIndexByName("editPreset")) {
    drawIconParameters(selectedItem);
  }

  // If Settings page:
  // Icons
  // IconSelection
  // Parameters
  // ParametersSelection
  // Scrollbar
  // Scroll indicator
  if (currentPage == getPageIndexByName("settings")) {
    drawIconParameters(selectedItem);
  }
}

void drawEditPreset(int x, int scroll) {
  drawIcons(currentPage);
  drawScrollBar();
  drawSelection(x, scroll);
}

void setupDisplay() {
  display.init();
  display.flipScreenVertically();
  display.setContrast(brightness);
}

void updateDisplay() {
  display.clear();
  // Check if changing brightness
  if (currentPage == getPageIndexByName("settings") && selectedItem == 1 &&
      currentMode == PARAMS_MODE && selectedParam == 0) {
    Serial.println("Changing brightness to: " +
                   String(iconParamsArray[5].paramValues[0]));
    brightness = iconParamsArray[5].paramValues[0];
    display.setContrast(map(brightness, 0, 100, 0, 255));
  }
  // display.setContrast(map(iconParamsArray[5].paramValues[0], 0, 100, 0,
  // 255));
  if (!shouldDrawCircle()) {
    drawUI();
  }

  if (updatedPotIndex != -1 && shouldDrawCircle()) {
    drawKnob(potValues[updatedPotIndex], updatedPotIndex);
  } else {
    updatedPotIndex = -1;
  }

  if (SHOW_FPS)
    updateFPS();
  display.display();
}

void changePage(const char *pageName) {
  Page *currentPage = getPageByName(pageName);
  if (currentPage == nullptr)
    return; // Validate page

  updateDisplay(); // Update display after page change
}
