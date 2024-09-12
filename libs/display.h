
#include <U8g2lib.h>

// U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0, /*
// reset=*/U8X8_PIN_NONE);
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE);

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
  u8g2.begin();
  u8g2.setBitmapMode(1);
}

void drawIcons(int page) {
  if (page < 0 || page >= totalPages)
    return; // Validar página

  const Page &currentPage = pages[page];   // Obtener página actual
  int iconsToDraw = currentPage.iconCount; // Número de íconos

  // Dibujar íconos
  for (int i = 0; i < VISIBLE_ICONS && i < iconsToDraw; i++) {
    int iconIndex = (firstVisibleItem + i) % iconsToDraw;
    u8g2.drawXBMP(3 + ITEM_WIDTH * i, 0, ICON_WIDTH, ICON_HEIGHT,
                  currentPage.icons[iconIndex]);
  }
}

void drawScrollBar() {
  u8g2.drawXBMP(0, 32 - SCROLL_BAR_HEIGHT, DISPLAY_WIDTH, SCROLL_BAR_HEIGHT,
                uiAllArray[0]);
}

void drawSelection(int x, int scrollX) {
  u8g2.drawXBMP(x, 0, 32, 32, uiAllArray[2]); // Selection rectangle
  u8g2.drawBox(scrollX, 32 - SCROLL_BAR_HEIGHT, SCROLL_BAR_WIDTH,
               SCROLL_BAR_HEIGHT); // Scroll indicator
}

void renderDisplay(int x, int scrollX) {
  u8g2.clearBuffer();
  drawIcons(currentPage); // Draw icons based on the current page
  drawScrollBar();
  drawSelection(x, scrollX);
  u8g2.sendBuffer();
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
    delay(10);
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
  u8g2.clearBuffer();
  drawIcons(currentPage); // Update based on the current page
  drawScrollBar();
  drawSelectionIndicator();
  u8g2.sendBuffer();
}

void animateBitmap(const unsigned char *bitmapArray[], int frames,
                   int frameDelay, int width, int height, int xPos, int yPos) {
  for (int i = 0; i < frames; i++) {
    u8g2.firstPage();
    do {
      u8g2.drawXBMP(xPos, yPos, width, height, bitmapArray[i]);
    } while (u8g2.nextPage());
    delay(frameDelay);
  }
}

void bootAnimations() {
  animateBitmap(cat, 28, 40, 30, 30, (DISPLAY_WIDTH - 30) / 2, 1);
  animateBitmap(skate, 28, 10, 32, 32, (DISPLAY_WIDTH - 32) / 2, 0);
}

void changePage(int direction) {
  currentPage += direction;
  if (currentPage < 0)
    currentPage = 1;
  if (currentPage >= 2)
    currentPage = 0;

  updateDisplay(); // Update display after page change
}
