#include "../assets/fonts/fonts.h"
#include "SSD1306Wire.h"
#include <Wire.h>

SSD1306Wire display(0x3c, SDA, SCL); // ADDRESS, SDA, SCL
#include "fpsOverlay.h"

int currentX = ICON_SPACING;
int scrollCurrentX = 0;

struct Page {
  const unsigned char **icons;
  int iconCount;
};

// Define los íconos de cada página
const unsigned char *iconsPage1[] = {icon_back, icon_gear};
const unsigned char *iconsPage2[] = {icon_back, icon_drive,  icon_amp_fndr,
                                     icon_cab,  icon_reverb, icon_save};
const unsigned char *iconsPage3[] = {icon_back, icon_drive,  icon_amp_mrsh,
                                     icon_cab,  icon_reverb, icon_save};

// Crear páginas
Page pages[] = {
    {iconsPage1,
     sizeof(iconsPage1) / sizeof(iconsPage1[0])}, // Página 1 con 6 íconos
    {iconsPage2,
     sizeof(iconsPage2) / sizeof(iconsPage2[0])}, // Página 2 con 3 íconos
    {iconsPage3,
     sizeof(iconsPage3) / sizeof(iconsPage3[0])}, // Página 3 con 6 íconos
};

// Número total de páginas
int totalPages = sizeof(pages) / sizeof(pages[0]);

// Ease-in-out cubic function
float easeInOut(float t, float b, float c, float d) {
  t /= d / 2;
  if (t < 1)
    return c / 2 * t * t * t + b;
  t -= 2;
  return c / 2 * (t * t * t + 2) + b;
}

void setupDisplay() {
  display.init();
  display.flipScreenVertically();
}

void drawIcons(int page) {
  if (page < 0 || page >= totalPages)
    return; // Validar página

  const Page &currentPage = pages[page];   // Obtener página actual
  int iconsToDraw = currentPage.iconCount; // Número de íconos

  // Dibujar íconos
  for (int i = 0; i < VISIBLE_ICONS && i < iconsToDraw; i++) {
    int iconIndex = (firstVisibleItem + i) % iconsToDraw;
    display.drawXbm(3 + ITEM_WIDTH * i, 0, ICON_WIDTH, ICON_HEIGHT,
                    currentPage.icons[iconIndex]);
  }
}

void drawScrollBar() {
  display.drawXbm(0, 32 - SCROLL_BAR_HEIGHT, DISPLAY_WIDTH, SCROLL_BAR_HEIGHT,
                  uiAllArray[0]);
}

void drawSelection(int x, int scrollX) {
  display.drawXbm(x, 0, 32, 32, uiAllArray[2]); // Selection rectangle
  display.fillRect(scrollX, 32 - SCROLL_BAR_HEIGHT, SCROLL_BAR_WIDTH,
                   SCROLL_BAR_HEIGHT); // Scroll indicator
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
  drawIcons(currentPage); // Update based on the current page
  drawScrollBar();
  drawSelectionIndicator();
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
  animateBitmap(cat, 28, 16, 2, 30, 30, (DISPLAY_WIDTH - 30) / 2,
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
